﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

public class Lobby
{
    public enum SearchStatus
    {
        DONE, SEARCHING
    }
    public SearchStatus searchStatus
    {
        get
        {
            return LANIPFinderThread.IsCompleted ? SearchStatus.DONE : SearchStatus.SEARCHING;
        }
    }

    private List<string> LANIPs;
    private Task LANIPFinderThread;

    public void scanForIPs()
    {
        Action ipFindAction = () =>
        {
            LANIPs = new IPUtils().getLANIPs();
        };
        LANIPFinderThread = new Task(ipFindAction);
        LANIPFinderThread.Start();
    }

    public Lobby()
    {
        scanForIPs();

    }

    public void hostLAN()
    {

        Server server = new Server();
        Task.Run(() => {
            server.waitForPlayersAsync();
        });

    }

    public void waitForIPSearch()
    {
        while (searchStatus != SearchStatus.DONE)
        {
            Thread.Sleep(300);
        }
    }

    public void joinLAN()
    {
        waitForIPSearch();
        Client client = new Client();
        if (client.connectToLANServer(LANIPs))
        {
            Console.WriteLine("Success");
        }
        else
        {
            Console.WriteLine("Failure");
        }

    }

}

