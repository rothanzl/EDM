using System.Globalization;
using System.IO.Ports;
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
        _port.ReadTimeout = 100;
        _port.WriteTimeout = 100;
        _port.BaudRate = 9600;
        _port.DataBits = 8;
        _port.Parity = Parity.None;
        _port.StopBits = StopBits.One;
        
        _readThread = new Thread(Read);
    }

    public event IncomingInfoMessageDelegate? GetInfoMessage;
    
    public void Connect()
    {
        _port.Open();
        _port.DiscardInBuffer();

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
                string rawMessage = _port.ReadLine();
                IncomingInfoMessage message;
                
                try
                {
                    var splitMessage = rawMessage.Split(';');
                    var time = double.Parse(splitMessage[0].Split(' ')[0], NumberFormatInfo.InvariantInfo);
                    message = new IncomingInfoMessage(TimeSec: time, RawMessage: rawMessage);
                }
                catch(Exception e)
                {
                    message = new(0, rawMessage, Error: e.Message);
                    _port.DiscardInBuffer();
                }
                
                GetInfoMessage?.Invoke(message);
                
            }
            catch (TimeoutException)
            {
                //
            }
        }
    }
}