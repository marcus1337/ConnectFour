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

public class IPUtils
{
    private List<string> LANIPs;
    private static object lockObj = new object();
    public static readonly int helloClientPort = 5643;
    public static readonly int helloServerPort = 5644;
    public static readonly int helloSpamPort = 5533;
    public static readonly string helloClientToServer = "R U SERVER?";

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
        IPAddress toIP = IPAddress.Parse("192.168.255.254");
        var ips = iputils.GetIPRange(fromIP, toIP);
        foreach (var ip in ips)
        {
            Ping p = new Ping();
            p.PingCompleted += new PingCompletedEventHandler(p_PingCompleted);
            p.SendAsync(ip, 200, ip);
        }
        return new List<string>(LANIPs); ;
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

}
