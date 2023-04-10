using System.Globalization;
using System.IO.Ports;

namespace EDM_Client_Console;

public class SerialPortSettingsHelper
{
    private readonly IConsoleInterface _console;

    public SerialPortSettingsHelper(IConsoleInterface console)
    {
        _console = console;
    }

    public string GetPortName()
    {
        var allNames = SerialPort.GetPortNames();

        if (allNames.Length == 1)
        {
            _console.WriteLine($"Available one serial port '{allNames[0]}'");
            return allNames[0];
        }
        if (allNames.Length == 0)
        {
            var errMessage = "Error. Missing any available serial port";
            _console.WriteLine(errMessage);
            throw new ArgumentException(errMessage);
        }
        if (allNames.Contains(Resource.PortName))
        {
            _console.WriteLine($"Selected port '{Resource.PortName}'");
            return Resource.PortName;
        }


        while(true)
        {
            _console.WriteLine($"Select serial port: " + string.Join(", ", allNames.Select((s, i) => $"[{i}] {s}")));
            var line = _console.ReadLine();

            if (!Int32.TryParse(line, NumberStyles.Any, CultureInfo.InvariantCulture, out int index))
            {
                _console.WriteLine($"Cannot parse '{line}' to number");
                continue;
            }

            if (index < 0 || index >= allNames.Length)
            {
                _console.WriteLine($"Index '{index}' is out of range");
                continue;
            }

            return allNames[index];
        }
    }
    
}