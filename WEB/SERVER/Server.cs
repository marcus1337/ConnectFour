using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

public class Server
{

    public bool awaitNewConnections;
    public HashSet<string> clientIPs;

    UdpListener listener;
    public async Task waitForPlayersAsync()
    {
        var receiveTask = await listener.ReceiveBytes();
        
        if (receiveTask.pktType == PktType.STRMSG && receiveTask.strMsg == IPUtils.helloClientToServer)
        {
            IPUtils.SendUdpOfType(PktType.STRMSG, IPUtils.serverSendPort, receiveTask.Sender.Address.ToString(), IPUtils.clientPort, Encoding.ASCII.GetBytes(IPUtils.helloServerToClient));
        }
        if (receiveTask.pktType == PktType.STRMSG && receiveTask.strMsg == IPUtils.helloClientToServerVerify)
        {
            clientIPs.Add(receiveTask.senderAdress);
            if (clientIPs.Count == 1)
                awaitNewConnections = false;
            Console.WriteLine("SERVER IS READY");
        }
    }


    public Server()
    {
        awaitNewConnections = true;
        clientIPs = new HashSet<string>();
        listener = new UdpListener(IPUtils.serverPort);
    }

    public async Task listenForGameMessagesAsync()
    {
        while (true)
        {
            Console.WriteLine("BEFORE RECEIVE");
            var receiveTask = await listener.ReceiveBytes();
            Console.WriteLine("AFTER RECEIVE");
          /*  object obj = IOStuff.Deserialize(receiveTask.message.ToArray());
            if (obj is AlivePacket)
            {
                var content = obj as AlivePacket;
                Console.WriteLine("Time: " + content.milliseconds);
            }
            else
            {
                var content = Encoding.ASCII.GetString(receiveTask.message, 0, receiveTask.message.Length);
                Console.WriteLine("MSG: " + content);
            }*/

        }
    }

    public void startGame()
    {
        var listenerTask = listenForGameMessagesAsync();
        List<string> cIPs = clientIPs.ToList();

        while (true)
        {
            int keyPress = Console.ReadKey().KeyChar - '0';
            if (keyPress == 0)
            {
                IPUtils.SendUdpOfType(PktType.STRMSG, IPUtils.serverSendPort, cIPs[0], IPUtils.clientPort, Encoding.ASCII.GetBytes("HEY"));
            }
            else
            {
                Console.WriteLine("Unknown press");
            }
        }

    }
}
