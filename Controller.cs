using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConnectFour
{
    public class Controller
    {
        private Model model;
        private AI ai;
        public bool PlayVsAI { get; set; }
        public Model.COLOR AIColor { get; set; }
        public bool exitGame;

        public Controller()
        {
            model = new Model();
            ai = new AI();
            AIColor = Model.COLOR.RED;
        }

        public Model getModel()
        {
            return model;
        }

        public Model getModelCopy()
        {
            return model.Clone();
        }

        public void nextTurn()
        {
            if (!model.isGameOver())
                model.nextTurn();
        }

        void printWinningBricks()
        {
            Console.WriteLine("\n");
            var winBricks = model.getWinBricks();
            foreach (var b in winBricks)
            {
                foreach (var br in b)
                {
                    Console.Write("(" + br.Item1 + "," + br.Item2 + ")");
                }
                Console.WriteLine();
            }
            Console.WriteLine("\n");
        }

        bool wantToPlayAgain()
        {
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

        bool handleGameOver()
        {
            printBoard();
            printStatusText();
            printWinningBricks();
            return wantToPlayAgain();
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

        int getPlayerVsAIMove()
        {
            if (model.currentPlayer != AIColor)
                return (Console.ReadKey().KeyChar - '0') - 1;
            else
                return ai.getPlayerMove(model, AIColor);
        }

        int getHotseatMove()
        {
            return (Console.ReadKey().KeyChar - '0') - 1;
        }

        public int getPlayerMove()
        {
            if (PlayVsAI)
            {
                return getPlayerVsAIMove();
            }
            else
            {
                return getHotseatMove();
            }
        }

        public int getAIMove()
        {
            return ai.getPlayerMove(model, AIColor);
        }

        public bool tryPlace(Model.COLOR playerColor, int rowNum)
        {
            if (rowNum > 6 || rowNum < 0 || playerColor != model.currentPlayer)
                return false;
            model.placeBrick(rowNum);
            return model.havePlaced;
        }

        public bool tryPlace()
        {
            int rowNum = getPlayerMove();
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
            printBoard();
        }

    }
}
