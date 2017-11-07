using System.Net;

class Configuration
{
    public uint PolaritySwitch { get; set; } = 9500;
    
    public bool Reverse { get; set; } = false;

    public uint Steps { get; set; } = 19200;
}