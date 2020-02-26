using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace ConnectFour
{
    [SerializableAttribute]
    public class PlayerAction
    {
        public Player player;
        public int rowNumber;

        public PlayerAction(Player player, int rowNumber)
        {
            this.player = player;
            this.rowNumber = rowNumber;
        }

    }
}