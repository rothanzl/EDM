// See https://aka.ms/new-console-template for more information

using EDM_Client;
using EDM_Client_Console;
using EDM_Client.Command;

IConsoleInterface console = new ConsoleInterface();


var portName = new SerialPortSettingsHelper(console).GetPortName();
console.WriteLine($"Selected '{portName}' port");
IEdmInterface edmInterface = new EdmInterface(portName);

edmInterface.GetInfoMessage += message =>
{
    if (message.Error is not null)
    {
        console.WriteLine($"Info: error '{message.Error}' of message '{message.RawMessage}'");
        return;
    }
    
    console.WriteLine($"Info: {message.RawMessage}");
};

edmInterface.Connect();

bool runLoop = true;
while (runLoop && console.ReadKey() is {} command)
{
    console.WriteLine($"Debug command: {command}");

    switch (command.Key)
    {
        case ConsoleKey.Escape:
            runLoop = false;
            break;
        case ConsoleKey.A:
            edmInterface.Send(new AutomationCommand(true));
            break;
        case ConsoleKey.S:
            edmInterface.Send(new AutomationCommand(false));
            break;
        case ConsoleKey.UpArrow:
            edmInterface.Send(new MoveCommand(1000, MoveCommandDirection.Up));
            break;
        case ConsoleKey.DownArrow:
            edmInterface.Send(new MoveCommand(1000, MoveCommandDirection.Down));
            break;
        case ConsoleKey.D1:
            edmInterface.Send(new MoveCommand(100, MoveCommandDirection.Down, 20));
            break;
        case ConsoleKey.D2:
            edmInterface.Send(new MoveCommand(100, MoveCommandDirection.Down, 30));
            break;
        case ConsoleKey.D3:
            edmInterface.Send(new MoveCommand(100, MoveCommandDirection.Down, 40));
            break;
        case ConsoleKey.D4:
            edmInterface.Send(new MoveCommand(100, MoveCommandDirection.Down, 50));
            break;
        case ConsoleKey.D5:
            edmInterface.Send(new MoveCommand(100, MoveCommandDirection.Down, 60));
            break;
        case ConsoleKey.D6:
            edmInterface.Send(new MoveCommand(100, MoveCommandDirection.Down, 70));
            break;
        
    }
}

edmInterface.Dispose();
console.WriteLine("Closed");