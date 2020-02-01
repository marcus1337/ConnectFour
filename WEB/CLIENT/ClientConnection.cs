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
                IPUtils.SendUdp(IPUtils.helloSpamPort, ip, IPUtils.helloServerPort, Encoding.ASCII.GetBytes(IPUtils.helloClientToServer));
            }
    }

    private void handleHelloResponse(Received response)
    {
        client.serverIP = response.Sender.Address.ToString();
        Console.WriteLine("Received " + response.Message);
        for (int i = 0; i < 10; i++)
            IPUtils.SendUdp(IPUtils.helloSpamPort, client.serverIP, IPUtils.helloServerPort, Encoding.ASCII.GetBytes(IPUtils.helloClientToServerVerify));
    }

    private void waitForResponse(Task<Received> receiveTask)
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

    private bool wasResponseAcceptedThenReplyOk(Task<Received> receiveTask)
    {
        if (receiveTask.IsCompleted && receiveTask.Result.Message == IPUtils.helloServerToClient)
        {
            handleHelloResponse(receiveTask.Result);
            return true;
        }
        return false;
    }

    public bool foundServerAndConnected(List<string> possibleIPs)
    {
        var receiveTask = client.listener.Receive();
        sendHellos(possibleIPs);
        waitForResponse(receiveTask);
        return wasResponseAcceptedThenReplyOk(receiveTask);
    }

}

