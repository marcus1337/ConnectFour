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

[SerializableAttribute]
public class AlivePacket
{
    public long millisecondsAtClient;
    public long millisecondsAtServer;
    public long milliseecondsRoundtrip;

    private long timeInMillis()
    {
        return DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
    }

    public AlivePacket()
    {
        millisecondsAtClient = timeInMillis();
    }

    public void setServerTimeStamp()
    {
        millisecondsAtServer = timeInMillis();
    }

    public void setRoundtripTime()
    {
        milliseecondsRoundtrip = timeInMillis() - millisecondsAtClient;
    }
}

