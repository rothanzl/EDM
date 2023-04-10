using EDM_Client.Command;

namespace EDM_Client;

public interface IEdmInterface : IDisposable
{
    event IncomingInfoMessageDelegate GetInfoMessage;
    void Connect();
    void Send(ICommand command);
}