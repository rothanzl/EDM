using System.Globalization;

namespace EDM_Client_Console;

public class ConsoleInterface : IConsoleInterface
{
    public void WriteLine(string line)
    {
        // ReSharper disable once LocalizableElement
        Console.WriteLine($"{DateTime.Now.ToString(DateTimeFormatInfo.CurrentInfo)} {line}");
    }

    public string ReadLine()
    {
        return Console.ReadLine() ?? String.Empty;
    }

    public ConsoleKeyInfo ReadKey()
    {
        return Console.ReadKey();
    }
}