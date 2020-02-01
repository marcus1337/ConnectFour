using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

[SerializableAttribute]
public class Model
{
    public enum COLOR : uint { RED = 1, BLUE = 2, NONE = 0 };

    int[,] board;
    int[] rowSpotsLeft;
    public COLOR currentPlayer;
    public bool havePlaced;
    Tuple<int, int> lastBrickPos;

    public void newGame()
    {
        lastBrickPos = new Tuple<int, int>(0, 0);
        rowSpotsLeft = new int[7] { 6, 6, 6, 6, 6, 6, 6 };
        havePlaced = false;
        currentPlayer = COLOR.RED;
        board = new int[7, 6];
    }

    List<List<Tuple<int,int>>> getWinBricks()
    {
        List<List<Tuple<int, int>>> result = new List<List<Tuple<int, int>>>();
        int x = lastBrickPos.Item1;
        int y = lastBrickPos.Item2;
        List<List<Tuple<int, int>>> allLines = new List<List<Tuple<int, int>>>();
        allLines.Add(getConnectedBrickPositionsInDirection(currentPlayer, x, y, 1, 0));
        allLines.Add(getConnectedBrickPositionsInDirection(currentPlayer, x, y, 0, 1));
        allLines.Add(getConnectedBrickPositionsInDirection(currentPlayer, x, y, 1, 1));
        allLines.Add(getConnectedBrickPositionsInDirection(currentPlayer, x, y, 1, -1));
        foreach(var line in allLines)
        {
            if (line.Count >= 4)
                result.Add(line);
        }

        return result;
    }

    int getFirstFreeColumnIndex(int rowIndex)
    {
        return Math.Abs(rowSpotsLeft[rowIndex] - 6);
    }

    public bool canPlaceBrick(int index)
    {
        return rowSpotsLeft[index] > 0;
    }

    public List<int> rowIndexLocationsAvailable()
    {
        List<int> result = new List<int>();
        for (int i = 0; i < 7; i++)
        {
            if (canPlaceBrick(i))
                result.Add(i);
        }
        return result;
    }

    public void placeBrick(int rowIndex)
    {
        if (canPlaceBrick(rowIndex) && !havePlaced)
        {
            havePlaced = true;
            int colIndex = getFirstFreeColumnIndex(rowIndex);
            board[rowIndex, colIndex] = (int)currentPlayer;
            lastBrickPos = new Tuple<int, int>(rowIndex, colIndex);
            rowSpotsLeft[rowIndex]--;
        }
    }

    public void nextTurn()
    {
        havePlaced = false;
        if (currentPlayer == COLOR.RED)
            currentPlayer = COLOR.BLUE;
        else if (currentPlayer == COLOR.BLUE)
            currentPlayer = COLOR.RED;
    }

    bool hasRowWin(COLOR playerColor, int x, int y)
    {
        return countConnectedBricksInDirection(playerColor, x, y, 1, 0) >= 4;
    }

    bool hasColWin(COLOR playerColor, int x, int y)
    {
        return countConnectedBricksInDirection(playerColor, x, y, 0, 1) >= 4;
    }

    bool hasDiagonalWinNWToSE(COLOR playerColor, int x, int y)
    {
        return countConnectedBricksInDirection(playerColor, x, y, 1, -1) >= 4;
    }
    bool hasDiagonalWinSWToNE(COLOR playerColor, int x, int y)
    {
        return countConnectedBricksInDirection(playerColor, x, y, 1, 1) >= 4;
    }

    bool isOnBoard(int x, int y)
    {
        return x >= 0 && y >= 0 && y < 6 && x < 7;
    }

    bool anySpotEmpty()
    {
        for (int i = 0; i < 7; i++)
            if (canPlaceBrick(i))
                return true;
        return false;
    }

    public bool isGameOver()
    {
        return isDraw() || hasCurrentPlayerWon();
    }

    public bool isDraw()
    {
        return !hasCurrentPlayerWon() && !anySpotEmpty();
    }

    List<Tuple<int, int>> getConnectedBrickPositionsInDirection(COLOR playerColor, int x, int y, int movX, int movY)
    {
        return getBrickPositionsInLine(playerColor, x + movX, y + movY, movX, movY).
            Union(getBrickPositionsInLine(playerColor, x, y, movX * -1, movY * -1)).ToList();
    }

    List<Tuple<int,int>> getBrickPositionsInLine(COLOR playerColor, int x, int y, int movX, int movY)
    {
        List<Tuple<int, int>> result = new List<Tuple<int, int>>();
        while (isOnBoard(x, y) && board[x, y] == (int)playerColor)
        {
            result.Add(new Tuple<int, int>(x, y));
            y += movY;
            x += movX;
        }
        return result;
    }

    int countBricksInLine(COLOR playerColor, int x, int y, int movX, int movY)
    {
        int res = 0;
        while (isOnBoard(x, y) && board[x, y] == (int)playerColor)
        {
            res++;
            y += movY;
            x += movX;
        }
        return res;
    }

    int countConnectedBricksInDirection(COLOR playerColor, int x, int y, int movX, int movY)
    {
        return countBricksInLine(playerColor, x + movX, y + movY, movX, movY)
        + countBricksInLine(playerColor, x, y, movX * -1, movY * -1);
    }

    public bool hasCurrentPlayerWon()
    {
        int x = lastBrickPos.Item1;
        int y = lastBrickPos.Item2;
        if (hasRowWin(currentPlayer, x, y))
            return true;
        if (hasColWin(currentPlayer, x, y))
            return true;
        if (hasDiagonalWinNWToSE(currentPlayer, x, y))
            return true;
        if (hasDiagonalWinSWToNE(currentPlayer, x, y))
            return true;
        return false;
    }

    public string getBoardString()
    {
        string res = "";
        for (int i = 5; i >= 0; i--)
        {
            for (int j = 0; j < 7; j++)
            {
                res += (board[j, i] + " ");
            }
            res += "\n";
        }
        return res;
    }

    public Model()
    {
        newGame();
    }

}