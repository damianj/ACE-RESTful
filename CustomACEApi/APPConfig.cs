namespace CustomACEAPI
{
    /// <summary>Class used to used to house the information parsed from config.json</summary>
    /// <author>Damian Jimenez</author>
    public class APPConfig
    {
        /// <summary>URL where the ACE server is hosted at.</summary>
        public string ACEServer { get; set; }
        /// <summary>Port on which the ACE server is listening on.</summary>
        public int ACEPort { get; set; }
        /// <summary>Name of the ACE server.</summary>
        public string ACEName { get; set; }
        /// <summary>Callback port for the ACE server.</summary>
        public int ACECallbackPort { get; set; }
        /// <summary>URL where the API server is to be hosted at.</summary>
        public string APIServer { get; set; }
        /// <summary>Port on which the API server should listen on.</summary>
        public int APIPort { get; set; }
        /// <summary>Determines whether threading protected threading is enabled for the endpoints that issue move commands to the robot.</summary>
        public bool ThreadingEnabled { get; set; }
    }
}
