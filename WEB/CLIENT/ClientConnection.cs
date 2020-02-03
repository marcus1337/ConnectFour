using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class ClientConnection
{
    private Client client;
    public ClientConnection(Client client)
    {
        this.client = client;
    }

    private void sendHellos(List<string> possibleIPs)
    {
        Console.WriteLine("Sending hello packets...\n");
        for (int i = 0; i < 10; i++)
            foreach (string ip in possibleIPs)
            {
                IPUtils.SendUdpOfType(PktType.STRMSG, IPUtils.helloSpamPort, ip, IPUtils.serverPort, Encoding.ASCII.GetBytes(IPUtils.helloClientToServer));
            }
    }

    private void handleHelloResponse(ReceivedBytes response)
    {
        if(response.pktType == PktType.STRMSG)
        {
            string responseTxt = response.strMsg;
            client.serverIP = response.senderAdress;
            Console.WriteLine("Received " + responseTxt);
            for (int i = 0; i < 10; i++)
                IPUtils.SendUdpOfType(PktType.STRMSG, IPUtils.helloSpamPort, client.serverIP, IPUtils.serverPort, Encoding.ASCII.GetBytes(IPUtils.helloClientToServerVerify));
        }
    }

    private void waitForResponse(Task<ReceivedBytes> receiveTask)
    {
        var timer = new Stopwatch();
        timer.Start();
        Console.WriteLine("Checking for response.....");
        while (!receiveTask.IsCompleted)
        {
            if (timer.ElapsedMilliseconds > 800)
                break;
        }
    }

    private bool wasResponseAcceptedThenReplyOk(Task<ReceivedBytes> receiveTask)
    {
        var pkt = receiveTask.Result;
        if (pkt.pktType == PktType.STRMSG && receiveTask.IsCompleted && pkt.strMsg == IPUtils.helloServerToClient)
        {
            handleHelloResponse(pkt);
            return true;
        }
        return false;
    }

    public bool foundServerAndConnected(List<string> possibleIPs)
    {
        var receiveTask = client.listener.ReceiveBytes();
        sendHellos(possibleIPs);
        waitForResponse(receiveTask);
        return wasResponseAcceptedThenReplyOk(receiveTask);
    }

    public void handleAlivePacket(ReceivedBytes received)
    {
        if (received.pktType == PktType.ALIVERESPONSE)
        {
            AlivePacket obj = (AlivePacket)IOStuff.Deserialize(received.message);
            obj.setRoundtripTime();
            Console.WriteLine("Time: " + obj.milliseecondsRoundtrip);
        }
    }

}

