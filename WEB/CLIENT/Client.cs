using ConnectFour;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


public class Client
{
    public string serverIP { get; set; }
    public UdpListener listener;
    private ClientConnection clientConnection;
    private Player player;
    private Model model;
    private Stopwatch timer;

    public Client()
    {
        timer = new Stopwatch();
        listener = new UdpListener(IPUtils.clientPort);
        clientConnection = new ClientConnection(this);
    }

    public bool connectToLANServer(List<string> possibleIPs)
    {
        return clientConnection.foundServerAndConnected(possibleIPs);
    }

    public bool initializingGame()
    {
        if (player == null || model == null)
        {
            IPUtils.SendUdpOfType(PktType.REQUESTGAMEDATA, IPUtils.helloSpamPort, serverIP, IPUtils.serverPort, new byte[] { new byte() });
            Thread.Sleep(50);
            return true;
        }
        return false;
    }

    public void sendAlivePacket()
    {
        if (timer.ElapsedMilliseconds > 400)
        {
            IPUtils.SendUdpOfType(PktType.ALIVE, IPUtils.helloSpamPort, serverIP, IPUtils.serverPort, IOStuff.Serialize(new AlivePacket()));
            timer.Restart();
        }
    }

    public async Task listenForGameMessagesAsync()
    {
        while (IPUtils.webLoopFlag)
        {
            var receiveTask = await listener.ReceiveBytes();
            clientConnection.handleAlivePacket(receiveTask);

            if (receiveTask.pktType == PktType.MODEL)
            {
                model = (Model)IOStuff.Deserialize(receiveTask.message);
            }
            if (receiveTask.pktType == PktType.PLAYER)
            {
                player = (Player)IOStuff.Deserialize(receiveTask.message);
            }

        }
    }

    public async Task handleHumanInputs()
    {
        await Task.Run(() =>
        {
            while (IPUtils.webLoopFlag)
            {
                if (initializingGame())
                    continue;

                int keyPress = Console.ReadKey().KeyChar - '0';
                PlayerAction playerAction = new PlayerAction(player, keyPress);
                IPUtils.SendUdpOfType(PktType.PLAYERACTION, IPUtils.helloSpamPort, serverIP, IPUtils.serverPort, IOStuff.Serialize(playerAction));

                if (keyPress == 9)
                {
                    Console.Write(model.getBoardString());
                }
            }
        });
    }

    public async Task sendAutomaticGameData()
    {
        await Task.Run(() =>
        {
            while (IPUtils.webLoopFlag)
            {
                sendAlivePacket();
            }
        });
    }

    public void startGame()
    {
        var listenerTask = listenForGameMessagesAsync();
        var humanInputTask = handleHumanInputs();
        var sendAutomaticDataTask = sendAutomaticGameData();

    }

}
