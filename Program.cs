using System;
using System.Threading;

namespace ConnectFour
{
    public class Program
    {

        public Program()
        {

        }

        public void run()
        {
            /*Hotseat hotseat = new Hotseat();
            hotseat.runGame();*/
        
            Lobby lobby = new Lobby();
            Console.WriteLine("1: Server");
            Console.WriteLine("2: Client");
            int menuOption = Console.ReadKey().KeyChar - '0';

            if (menuOption == 2)
            {
                Console.Write("Starting client..............\n\n");
                lobby.joinLAN();
            }
            if (menuOption == 1)
            {
                Console.Write("Starting server..............\n\n");
                lobby.hostLAN();
            }

            Console.ReadKey();
        }

        /*static void Main(string[] args)
        {
            new Program().run();
        }*/
    }
}
