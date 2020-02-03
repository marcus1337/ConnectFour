using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

/* ====================================================================================
                    C# IP address range finder helper class (C) Nahum Bazes
 * Free for private & commercial use - no restriction applied, please leave credits.
 *                              DO NOT REMOVE THIS COMMENT
 * ==================================================================================== */

public enum PktType:uint
{
    UNKNOWN = 0,
    STRMSG = 1,
    MODEL = 2,
    ALIVE = 3
}

public class IPUtils
{
    private List<string> LANIPs;
    private static object lockObj = new object();
    public static readonly int clientPort = 5643;
    public static readonly int serverPort = 5644;
    public static readonly int serverSendPort = 5648;   //send packet
    public static readonly int helloSpamPort = 5533;    //send packet
    public static readonly string helloClientToServer = "R U SERVER?";
    public static readonly string helloServerToClient = "Yep - added U if OK?";
    public static readonly string helloClientToServerVerify = "Okay add me to server!";

    public IPUtils()
    {

    }

    void p_PingCompleted(object sender, PingCompletedEventArgs e)
    {
        string ip = (string)e.UserState;
        if (e.Reply != null && e.Reply.Status == IPStatus.Success)
        {
            lock (lockObj)
            {
                LANIPs.Add(ip);
            }
        }
    }

    public List<string> getLANIPs(){
        LANIPs = new List<string>();
        IPUtils iputils = new IPUtils();
        IPAddress fromIP = IPAddress.Parse("192.168.1.1");
        IPAddress toIP = IPAddress.Parse("192.168.20.254");
        var ips = iputils.GetIPRange(fromIP, toIP);
        foreach (var ip in ips)
        {
            Ping p = new Ping();
            p.PingCompleted += new PingCompletedEventHandler(p_PingCompleted);
            p.SendAsync(ip, 150, ip);
        }
        return new List<string>(LANIPs); ;
    }

    public static void SendUdpOfType(PktType pktType, int srcPort, string dstIp, int dstPort, byte[] data)
    {
        byte b0 = (byte)(int)pktType;
        byte b1 = (byte)((int)pktType >> 8);
        byte[] pktTypeData = new byte[2] { b0, b1 };
        byte[] dataPacket = Combine(pktTypeData, data);
        SendUdp(srcPort, dstIp, dstPort, dataPacket);
    }

    public static PktType extractPktType(byte[] packet)
    {
        byte[] firstTwoBytesOfPacket = packet.Take(2).ToArray(); 
        return (PktType)BitConverter.ToInt16(firstTwoBytesOfPacket, 0);
    }

    public static byte[] extractData(byte[] packet)
    {
        return packet.Skip(2).ToArray();
    }

    public static void SendUdp(int srcPort, string dstIp, int dstPort, byte[] data)
    {
        using (UdpClient c = new UdpClient(srcPort))
            c.Send(data, data.Length, dstIp, dstPort);
    }


    public IEnumerable<string> GetIPRange(IPAddress startIP,
                                        IPAddress endIP)
    {
        uint sIP = ipToUint(startIP.GetAddressBytes());
        uint eIP = ipToUint(endIP.GetAddressBytes());
        while (sIP <= eIP)
        {
            yield return new IPAddress(reverseBytesArray(sIP)).ToString();
            sIP++;
        }
    }


    /* reverse byte order in array */
    protected uint reverseBytesArray(uint ip)
    {
        byte[] bytes = BitConverter.GetBytes(ip);
        bytes = bytes.Reverse().ToArray();
        return (uint)BitConverter.ToInt32(bytes, 0);
    }


    /* Convert bytes array to 32 bit long value */
    protected uint ipToUint(byte[] ipBytes)
    {
        ByteConverter bConvert = new ByteConverter();
        uint ipUint = 0;

        int shift = 24; // indicates number of bits left for shifting
        foreach (byte b in ipBytes)
        {
            if (ipUint == 0)
            {
                ipUint = (uint)bConvert.ConvertTo(b, typeof(uint)) << shift;
                shift -= 8;
                continue;
            }

            if (shift >= 8)
                ipUint += (uint)bConvert.ConvertTo(b, typeof(uint)) << shift;
            else
                ipUint += (uint)bConvert.ConvertTo(b, typeof(uint));

            shift -= 8;
        }

        return ipUint;
    }

    public static byte[] Combine(byte[] first, byte[] second)
    {
        byte[] ret = new byte[first.Length + second.Length];
        Buffer.BlockCopy(first, 0, ret, 0, first.Length);
        Buffer.BlockCopy(second, 0, ret, first.Length, second.Length);
        return ret;
    }

}
