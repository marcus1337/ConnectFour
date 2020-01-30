﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConnectFour2
{
    class Controller
    {
        private Model model;

        public Controller()
        {
            model = new Model();
        }

        public bool exitGame;

        bool handleGameOver()
        {
            printBoard();
            printStatusText();
            char playAgainOrNot = Console.ReadKey().KeyChar;
            if (playAgainOrNot == 'y' || playAgainOrNot == 'Y')
            {
                model.newGame();
                return true;
            }
            else if (playAgainOrNot == 'n' || playAgainOrNot == 'N')
            {
                exitGame = true;
                return true;
            }
            return false;
        }

        void handleGameOverAndAskRematch()
        {
            bool madeDecision = handleGameOver();
            Console.WriteLine();
            if (madeDecision && !exitGame)
            {
                printBoard();
            }
        }

        void handleGameTurn()
        {
            printStatusText();
            if (tryPlace())
            {
                if (!model.isGameOver())
                    model.nextTurn();
            }
            else
            {
                Console.WriteLine("Incorrect Input, pick 1 - 7");
            }
            printBoard();

        }

        public void handleInput()
        {
            if (model.isGameOver())
            {
                handleGameOverAndAskRematch();
            }
            else
            {
                handleGameTurn();
            }
        }

        public void printTurnInfo()
        {
            string playerStr = "";
            if (model.currentPlayer == Model.COLOR.BLUE)
                playerStr = "BLUE";
            else
                playerStr = "RED";
            Console.WriteLine(playerStr + " turn to place a brick.");
        }

        public bool tryPlace()
        {
            int rowNum = (Console.ReadKey().KeyChar - '0') -1;
            Console.WriteLine();
            if (rowNum > 6 || rowNum < 0)
                return false;
            model.placeBrick(rowNum);
            return true;
        }

        public void printBoard()
        {
            Console.Write(model.getBoardString() + "\n\n\n");
        }

        public void printGameOverText()
        {
            Console.WriteLine("Game Over:");
            if (model.isDraw())
            {
                Console.WriteLine("DRAW\n");
            }
            else
            {
                if (model.currentPlayer == Model.COLOR.BLUE)
                    Console.WriteLine("BLUE WON\n");
                if (model.currentPlayer == Model.COLOR.RED)
                    Console.WriteLine("RED WON\n");
            }
        }

        public void printStatusText()
        {
            if (model.isGameOver())
            {
                printGameOverText();
                Console.WriteLine("Play again? (Y/N)");
            }
            else
            {
                printTurnInfo();
            }
        }

        public void beforeStart()
        {
            Console.Write("Starting Connect Four Game...\n\n");
            controller.printBoard();
        }

    }
}
