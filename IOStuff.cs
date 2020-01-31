using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

public static class IOStuff
{
    public static readonly int port = 7755;

    public static byte[] Serialize(object anySerializableObject)
    {
        using (var memoryStream = new MemoryStream())
        {
            (new BinaryFormatter()).Serialize(memoryStream, anySerializableObject);
            return memoryStream.ToArray();
        }
    }

    public static object Deserialize(byte[] data)
    {
        using (var memoryStream = new MemoryStream(data))
            return (new BinaryFormatter()).Deserialize(memoryStream);
    }

}

