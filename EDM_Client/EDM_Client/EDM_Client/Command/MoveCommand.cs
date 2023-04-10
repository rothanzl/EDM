namespace EDM_Client.Command;

public record MoveCommand(long TimeMs, MoveCommandDirection Direction) : ICommand
{
    public string ToMessage()
    {
        int dir = Direction switch
        {
            MoveCommandDirection.Left => 0,
            MoveCommandDirection.Right => 1,
            _ => throw new ArgumentOutOfRangeException(Direction.ToString())
        };
        
        return  $"move {TimeMs} 255 {dir} end";
    }
}