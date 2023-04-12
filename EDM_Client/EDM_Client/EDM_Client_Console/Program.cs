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


while (console.ReadLine() is {} command)
{
    console.WriteLine($"Debug command: {command}");

    if (command.Equals("l"))
    {
        edmInterface.Send(new MoveCommand(10000, MoveCommandDirection.Left));
    }else if (command.Equals("r"))
    {
        edmInterface.Send(new MoveCommand(10000, MoveCommandDirection.Right));
    }else if (command.Equals("end"))
    {
        break;
    }
}
edmInterface.Dispose();
console.WriteLine("Closed");