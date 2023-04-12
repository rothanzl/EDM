using System.IO.Hashing;
using System.IO.Ports;
using System.Text;
using EDM_Client.Command;

namespace EDM_Client;

public class EdmInterface : IEdmInterface
{
    private readonly SerialPort _port;
    private readonly Thread _readThread;
    
    private bool Continue { get; set; }

    public EdmInterface(string portName)
    {

        _port = new SerialPort(portName);
        _port.ReadTimeout = 200;
        _port.WriteTimeout = 200;
        _port.BaudRate = 9600;
        _port.DataBits = 8;
        _port.Parity = Parity.Odd;
        _port.StopBits = StopBits.Two;

        _port.ErrorReceived += (sender, args) =>
        {

        };

        _port.PinChanged += (sender, args) =>
        {

        };

        _port.DataReceived += (sender, args) =>
        {

        };

        _readThread = new Thread(Read);
    }

    public event IncomingInfoMessageDelegate? GetInfoMessage;
    
    public void Connect()
    {
        _port.Open();
        

        Continue = true;
        _readThread.Start();
        
    }

    public void Send(ICommand command)
    {
        _port.WriteLine(command.ToMessage());
    }

    public void Dispose()
    {
        Continue = false;
        _readThread.Join();
        
        
        try
        {
            _port.Close();
        }
        catch { /**/ }
        _port.Dispose();
    }

    private void Read()
    {
        while (Continue)
        {
            try
            {

                Thread.Yield();
                string rawMessage = _port.ReadLine().RemoveWhitespace();


                string message;
                try
                {
                    Crc(rawMessage, out message);
                }
                catch (CrcException e)
                {
                    Console.WriteLine(e.Message);
                    continue;
                }
                
                Console.WriteLine(message);
                
                
                
                

                // IncomingInfoMessage message;
                //
                // try
                // {
                //     var splitMessage = rawMessage.Split(';');
                //     var time = double.Parse(splitMessage[0].Split(' ')[0], NumberFormatInfo.InvariantInfo);
                //     message = new IncomingInfoMessage(TimeSec: time, RawMessage: rawMessage);
                // }
                // catch(Exception e)
                // {
                //     message = new(0, rawMessage, Error: e.Message);
                //     _port.DiscardInBuffer();
                // }
                //
                // GetInfoMessage?.Invoke(message);
                
            }
            catch (TimeoutException)
            {
                //
            }
        }
    }

    private class CrcException : Exception
    {
        public CrcException(string message) : base(message){}
    }


    private void Crc(string wholeMessage, out string messageWithoutCrc)
    {
        var splitMessage = wholeMessage.Split(";crc");
        
        if (splitMessage.Length != 2)
            throw new CrcException($"Message '{wholeMessage}' has not ';crc' phrase");

        messageWithoutCrc = splitMessage[0];
        
        byte[] bytes = Encoding.ASCII.GetBytes(splitMessage[0]);
        Crc32 crcProcessor = new Crc32();
        crcProcessor.Append(bytes);
        byte[] crcCalc = crcProcessor.GetCurrentHash();

        byte[] crcReceived;
        try
        {
            crcReceived = splitMessage[1]
                .Split(" ")
                .Select(s => Convert.ToByte(s.Trim(), 16))
                .ToArray();
        }
        catch (Exception e)
        {
            throw new CrcException($"Parse '{splitMessage[1]}' exception: " + e.Message);
        }

        if (crcReceived.Length != 4)
            throw new CrcException($"Received crc has {crcReceived.Length} bytes");

        for (int i = 0; i < crcCalc.Length; i++)
        {
            if (crcCalc[i] != crcReceived[i])
                throw new CrcException($"Invalid crc byte: received {splitMessage[1]} calc {crcCalc[0]:X} {crcCalc[1]:X} {crcCalc[2]:X} {crcCalc[3]:X} in message '{splitMessage[0]}'");
        }

    }
    
}

public static class StringExtensions
{
    public static string RemoveWhitespace(this string input)
    {
        return new string(input.ToCharArray()
            .Where(c => !(Char.IsWhiteSpace(c) && c != ' '))
            .ToArray());
    }
}