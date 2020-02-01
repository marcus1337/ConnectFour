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
    /* private TcpClient socketConnection;
     private Thread clientReceiveThread;
     private Socket _socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
     private const int bufSize = 8 * 1024;
     private EndPoint epFrom = new IPEndPoint(IPAddress.Any, 0);
     private AsyncCallback recv = null;*/


    public string serverIP { get; set; }
    public UdpListener listener;
    private ClientConnection clientConnection;

    public Client()
    {
        listener = new UdpListener(IPUtils.helloClientPort);
        clientConnection = new ClientConnection(this);
    }


    public bool connectToLANServer(List<string> possibleIPs)
    {
        return clientConnection.foundServerAndConnected(possibleIPs);
    }

}
