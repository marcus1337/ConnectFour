using ConnectFour;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class WebGame
{

    public Controller controller;
    public Player player1;
    public Player player2;

    public WebGame()
    {
        controller = new Controller();
        player1 = new Player();
        player2 = new Player();
        player1.playerColor = Model.COLOR.RED;
        player2.playerColor = Model.COLOR.BLUE;
    }

    public bool wasUpdated { get; set; }

    public void tryPlace(Player player, int rowNumber)
    {
        wasUpdated = controller.tryPlace(player.playerColor, rowNumber);
        Console.Write("Was updated? " + wasUpdated);
        controller.printBoard();
        if (wasUpdated)
            controller.nextTurn();
    }
}
