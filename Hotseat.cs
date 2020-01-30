using ConnectFour2;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class Hotseat
{

    public Hotseat()
    {

    }

    public void runGame()
    {
        Controller controller = new Controller();
        controller.PlayVsAI = true;

        controller.beforeStart();
        while (!controller.exitGame)
        {
            controller.handleInput();
        }
    }

}
