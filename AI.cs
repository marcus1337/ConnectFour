using ConnectFour;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


public class AI
{
    public AI()
    {

    }

    public int getPlayerMove(Model model, Model.COLOR aiColor)
    {
        var possibleMoves = model.rowIndexLocationsAvailable();
        int numberOfChoices = possibleMoves.Count();
        Random r = new Random();
        int rInt = r.Next(0, numberOfChoices);
        return possibleMoves[rInt];
    }

}

