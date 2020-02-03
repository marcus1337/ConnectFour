using System;
using System.Collections.Generic;
using System.Diagnostics;
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
    public List<string> clientAdresses;
    public UdpListener listener;
    public ServerConnect serverConnect;
    public WebGame webGame;
    private Stopwatch timer;

    public Server()
    {
        timer = new Stopwatch();
        webGame = new WebGame();
        serverConnect = new ServerConnect(this);
        awaitNewConnections = true;
        clientIPs = new HashSet<string>();
        listener = new UdpListener(IPUtils.serverPort);
    }

    public void handleGamePacket(ReceivedBytes received)
    {
        if (received.pktType == PktType.PLAYERACTION)
        {
            PlayerAction playerAction = (PlayerAction)IOStuff.Deserialize(received.message);
            webGame.tryPlace(playerAction.player, playerAction.rowNumber);
        }
        if(received.pktType == PktType.REQUESTGAMEDATA)
        {
            sendGameInfo();
        }
    }

    public void sendGameMessages()
    {
        if (webGame.wasUpdated || timer.ElapsedMilliseconds > 600)
        {
            IPUtils.SendUdpOfType(PktType.MODEL, IPUtils.serverSendPort, clientAdresses[0], IPUtils.clientPort, IOStuff.Serialize(webGame.controller.getModel()));
            webGame.wasUpdated = false;
            timer.Restart();
        }
        
    }

    public async Task listenForGameMessagesAsync()
    {
        while (IPUtils.webLoopFlag)
        {
            var receiveTask = await listener.ReceiveBytes();
            serverConnect.handleAlivePacket(receiveTask);
            handleGamePacket(receiveTask);
        }
    }

    public async Task handleHumanInputs()
    {
        await Task.Run(() =>
        {
            while (IPUtils.webLoopFlag)
            {
                int keyPress = Console.ReadKey().KeyChar - '0';
                webGame.tryPlace(webGame.player1, keyPress);
                Console.WriteLine("PRESS: " + keyPress);
            }
        });
    }

    void sendGameInfo()
    {
        IPUtils.SendUdpOfType(PktType.MODEL, IPUtils.serverSendPort, clientAdresses[0], IPUtils.clientPort, IOStuff.Serialize(webGame.controller.getModel()));
        IPUtils.SpamSendUdpOfType(PktType.PLAYER, IPUtils.serverSendPort, clientAdresses[0], IPUtils.clientPort, IOStuff.Serialize(webGame.player2));
    }

    public void startGame()
    {
        var listenerTask = listenForGameMessagesAsync();
        var humanInputsTask = handleHumanInputs();
        timer.Start();

        while (IPUtils.webLoopFlag)
        {
            sendGameMessages();
        }

    }
}
