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
        listener = new UdpListener(IPUtils.helloClientPort);
        clientConnection = new ClientConnection(this);
    }


    public bool connectToLANServer(List<string> possibleIPs)
    {
        return clientConnection.foundServerAndConnected(possibleIPs);
    }

}
