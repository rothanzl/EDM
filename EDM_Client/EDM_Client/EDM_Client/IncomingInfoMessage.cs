namespace EDM_Client;

public record IncomingInfoMessage(double TimeSec, string RawMessage, string? Error = null);