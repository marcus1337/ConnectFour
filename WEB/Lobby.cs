using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

public class Lobby
{
    public enum SearchStatus
    {
        DONE, SEARCHING
    }
    public SearchStatus searchStatus
    {
        get
        {
            return LANIPFinderThread.IsCompleted ? SearchStatus.DONE : SearchStatus.SEARCHING;
        }
    }

    private List<string> LANIPs;
    private Task LANIPFinderThread;

    public void scanForIPs()
    {
        Action ipFindAction = () =>
        {
            LANIPs = new IPUtils().getLANIPs();
        };
        LANIPFinderThread = new Task(ipFindAction);
        LANIPFinderThread.Start();
    }

    public Lobby()
    {
        scanForIPs();

    }

    public async Task fillServerLobby(Server server)
    {
        while (server.awaitNewConnections)
        {
            await server.serverConnect.waitForPlayersAsync();
        }
        Console.WriteLine("END WHILE");
    }

    public async Task<bool> connectToServer(Client client)
    {
        waitForIPSearch();
        if (LANIPs.Count == 0)
            return false;
        return await Task.Run(() => client.connectToLANServer(LANIPs));
    }

    public void waitForIPSearch()
    {
        while (searchStatus != SearchStatus.DONE)
        {
            Thread.Sleep(300);
        }
    }

    public void hostLAN()
    {
        Server server = new Server();
        var serverWaitForPlayersTask = fillServerLobby(server);

        while (!serverWaitForPlayersTask.IsCompleted)
        {
            Thread.Sleep(200);
        }
        server.startGame();
    }

    public void joinLAN()
    {
        Client client = new Client();
        var connectionTask = connectToServer(client);

        while (!connectionTask.IsCompleted)
        {
            //Console.WriteLine("connecting...");
            Thread.Sleep(200);
        }

        client.startGame();
    }

}

