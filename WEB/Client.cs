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
    private TcpClient socketConnection;
    private Thread clientReceiveThread;

    private Socket _socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
    private const int bufSize = 8 * 1024;
    private EndPoint epFrom = new IPEndPoint(IPAddress.Any, 0);
    private AsyncCallback recv = null;

    public Client()
    {

    }

    private void Receive()
    {

    }

    public bool connectToLANServer(List<string> possibleIPs)
    {
        UdpListener listener = new UdpListener(IPUtils.helloClientPort);
        var receiveTask = listener.Receive();

        Console.WriteLine("Sending hello packets...\n");
        for (int i = 0; i < 10; i++)
            foreach (string ip in possibleIPs)
            {
                IPUtils.SendUdp(IPUtils.helloSpamPort, ip, IPUtils.helloServerPort, Encoding.ASCII.GetBytes(IPUtils.helloClientToServer));
            }

        var timer = new Stopwatch();
        timer.Start();

        Console.WriteLine("Checking for response.....");
        while (!receiveTask.IsCompleted)
        {
            if (timer.ElapsedMilliseconds > 2000)
                break;
        }
        if (receiveTask.IsCompleted)
        {
            return true;
        }
        return false;
    }

}
