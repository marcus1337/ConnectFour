using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class ServerConnect
{
    public Server server;

    public ServerConnect(Server server)
    {
        this.server = server;
    }

    public async Task waitForPlayersAsync()
    {
        var receiveTask = await server.listener.ReceiveBytes();

        if (receiveTask.pktType == PktType.STRMSG && receiveTask.strMsg == IPUtils.helloClientToServer)
        {
            IPUtils.SendUdpOfType(PktType.STRMSG, IPUtils.serverSendPort, receiveTask.Sender.Address.ToString(), IPUtils.clientPort, Encoding.ASCII.GetBytes(IPUtils.helloServerToClient));
        }
        if (receiveTask.pktType == PktType.STRMSG && receiveTask.strMsg == IPUtils.helloClientToServerVerify)
        {
            server.clientIPs.Add(receiveTask.senderAdress);
            if (server.clientIPs.Count == 1)
                server.awaitNewConnections = false;
            Console.WriteLine("SERVER IS READY");
        }
    }

    public void handleAlivePacket(ReceivedBytes received)
    {
        if (received.pktType == PktType.ALIVE)
        {
            AlivePacket obj = (AlivePacket)IOStuff.Deserialize(received.message);
            obj.setServerTimeStamp();
            byte[] objData = IOStuff.Serialize(obj);
            IPUtils.SendUdpOfType(PktType.ALIVERESPONSE, IPUtils.serverSendPort, received.senderAdress, IPUtils.clientPort, objData);
        }
    }


}
