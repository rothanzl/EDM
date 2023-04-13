namespace EDM_Client.Command;

public class AutomationCommand : ICommand
{
    private readonly bool _enable;
    public AutomationCommand(bool enable)
    {
        _enable = enable;
    }
    
    public string ToMessage()
    {
        return _enable ? "auto start end" : "auto stop end";
    }
}
