using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

[SerializableAttribute]
public class Message
{
    public int choice;

    public Message()
    {
        choice = 0;
    }

}

[SerializableAttribute]
public class ConnectionSetupMessage
{
    public string message;

    public ConnectionSetupMessage()
    {
        message = "";
    }

}

