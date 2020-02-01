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
    /*private TcpListener tcpListener;
    private Thread tcpListenerThread;
    private TcpClient connectedTcpClient;*/

    public bool awaitNewConnections;
    public HashSet<string> clientIPs;

    /* tcpListenerThread = new Thread(new ThreadStart(ListenForIncommingRequests));
     tcpListenerThread.IsBackground = true;
     tcpListenerThread.Start();*/

    /*
    void readClientPacket(byte[] byteStorage)
    {
        using (NetworkStream stream = connectedTcpClient.GetStream())
        {
            int length;
            while ((length = stream.Read(byteStorage, 0, byteStorage.Length)) != 0)
            {
                var incommingData = new byte[length];
                Array.Copy(byteStorage, 0, incommingData, 0, length);
                object obj = IOStuff.Deserialize(incommingData);
                if (obj is Message)
                {
                    processClientMessage(obj as Message);
                }
            }
        }
    }*/
    /*
    void readClientPacket(byte[] byteStorage)
    {
        using (NetworkStream stream = connectedTcpClient.GetStream())
        {
            int length;
            while ((length = stream.Read(byteStorage, 0, byteStorage.Length)) != 0)
            {
                var incommingData = new byte[length];
                Array.Copy(byteStorage, 0, incommingData, 0, length);
                object obj = IOStuff.Deserialize(incommingData);
                if (obj is Message)
                {
                    processClientMessage(obj as Message);
                }
            }
        }
    }*/
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

    /* private void ListenForIncommingRequests()
     {
         try
         {
             tcpListener = new TcpListener(IPAddress.Parse("127.0.0.1"), IOStuff.port);
             tcpListener.Start();
             Console.WriteLine("Server is listening");
             byte[] bytes = new byte[1024];
             while (true)
             {
                 using (connectedTcpClient = tcpListener.AcceptTcpClient())
                 {
                     readClientPacket(bytes);
                 }
             }
         }
         catch (SocketException socketException)
         {
             Console.WriteLine("SocketException " + socketException.ToString());
         }
     }*/

    /*  private void sendModel(Model model)
      {
          NetworkStream stream = connectedTcpClient.GetStream();
          if (stream.CanWrite)
          {
              byte[] serverMessageAsByteArray = IOStuff.Serialize(model);
              stream.Write(serverMessageAsByteArray, 0, serverMessageAsByteArray.Length);
              Console.WriteLine("Server sent his message - should be received by client");
          }
      }

      public void SendMessage(Model model)
      {
          try
          {
              sendModel(model);
          }
          catch (SocketException socketException)
          {
              Console.WriteLine("Socket exception: " + socketException);
          }
      }*/

    /* public void processClientMessage(Message message)
     {

     }*/

    public Server()
    {
        awaitNewConnections = true;
        clientIPs = new HashSet<string>();
        listener = new UdpListener(IPUtils.helloServerPort);
    }
}
