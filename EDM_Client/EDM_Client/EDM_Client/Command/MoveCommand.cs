namespace EDM_Client.Command;

public record MoveCommand(long TimeMs, MoveCommandDirection Direction, byte speed = 255) : ICommand
{
    public string ToMessage()
    {
        int dir = Direction switch
        {
            MoveCommandDirection.Up => 0,
            MoveCommandDirection.Down => 1,
            _ => throw new ArgumentOutOfRangeException(Direction.ToString())
        };
        
        return  $"move {TimeMs} {speed} {dir} end";
    }
}