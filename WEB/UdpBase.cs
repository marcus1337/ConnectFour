using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

public struct ReceivedBytes
{
    public IPEndPoint Sender;
    public string senderAdress;
    public byte[] message;
    public PktType pktType;
    public string strMsg;
}

public abstract class UdpBase
{
    public UdpClient Client;

    ~UdpBase() 
    {
        if (Client != null)
            Client.Close();
    }

    protected UdpBase()
    {
        Client = new UdpClient();
    }

    public async Task<ReceivedBytes> ReceiveBytes()
    {
        var result = await Client.ReceiveAsync();
        ReceivedBytes receivedBytes = new ReceivedBytes();
        receivedBytes.message = result.Buffer.ToArray();
        receivedBytes.senderAdress = result.RemoteEndPoint.Address.ToString();
        receivedBytes.Sender = result.RemoteEndPoint;
        if(receivedBytes.message.Length > 2)
        {
            receivedBytes.pktType = IPUtils.extractPktType(receivedBytes.message);
            receivedBytes.message = IPUtils.extractData(receivedBytes.message);
        }
        else
        {
            receivedBytes.pktType = PktType.UNKNOWN;
        }
        if(receivedBytes.pktType == PktType.STRMSG)
        {
            receivedBytes.strMsg = Encoding.ASCII.GetString(receivedBytes.message);
        }

        return receivedBytes;
    }
}

public class UdpListener : UdpBase
{
    public IPEndPoint _listenOn;

    public UdpListener(int listenPort) : this(new IPEndPoint(IPAddress.Any, listenPort))
    {
    }

    public UdpListener(IPEndPoint endpoint)
    {
        _listenOn = endpoint;
        Client = new UdpClient(_listenOn);
    }

}

public class UdpUser : UdpBase
{
    private UdpUser() { }

    public static UdpUser ConnectTo(string hostname, int port)
    {
        var connection = new UdpUser();
        connection.Client.Connect(hostname, port);
        return connection;
    }

}