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
        var receiveTask = await listener.Receive();
        if (receiveTask.Message == IPUtils.helloClientToServer)
        {
            IPUtils.SendUdp(IPUtils.serverSendPort, receiveTask.Sender.Address.ToString(), IPUtils.helloClientPort, Encoding.ASCII.GetBytes(IPUtils.helloServerToClient));
        }
        if (receiveTask.Message == IPUtils.helloClientToServerVerify)
        {
            clientIPs.Add(receiveTask.Sender.ToString());
            if (clientIPs.Count == 1)
                awaitNewConnections = false;
            Console.WriteLine("SERVER IS READY");
        }
    }


    public Server()
    {
        awaitNewConnections = true;
        clientIPs = new HashSet<string>();
        listener = new UdpListener(IPUtils.helloServerPort);
    }
}
