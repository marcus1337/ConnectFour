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

    public Client()
    {
        listener = new UdpListener(IPUtils.clientPort);
        clientConnection = new ClientConnection(this);
    }


    public bool connectToLANServer(List<string> possibleIPs)
    {
        return clientConnection.foundServerAndConnected(possibleIPs);
    }



    public async Task listenForGameMessagesAsync()
    {
        while (true)
        {
            var receiveTask = await listener.ReceiveBytes();
            object obj = IOStuff.Deserialize(receiveTask.message);
            if (obj is AlivePacket)
            {
                var content = obj as AlivePacket;
                Console.WriteLine("Time: " + content.milliseconds);
            }else
            if (obj is string)
            {
                var content = obj as string;
                Console.WriteLine("MSG: " + content);
            }

        }
    }

    public void startGame()
    {
        var listenerTask = listenForGameMessagesAsync();

        while (true)
        {
            int keyPress = Console.ReadKey().KeyChar - '0';
            if (keyPress == 0)
            {
                var serializedPacket = IOStuff.Serialize(new AlivePacket());
                IPUtils.SendUdpOfType(PktType.ALIVE, IPUtils.helloSpamPort, serverIP, IPUtils.serverPort, serializedPacket);
            }
            else
            {
                Console.WriteLine("Unknown press");
            }
        }

    }

}
