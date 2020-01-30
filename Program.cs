using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConnectFour2
{
    class Program
    {
        static void Main(string[] args)
        {
            Controller controller = new Controller();

            controller.beforeStart();
            while (!controller.exitGame)
            {
                controller.handleInput();
            }

            Console.ReadKey();

        }
    }
}
