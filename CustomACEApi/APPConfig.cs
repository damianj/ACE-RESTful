namespace CustomACEAPI
{
    public class APPConfig
    {
        public string ACEServer { get; set; }
        public int ACEPort { get; set; }
        public string ACEName { get; set; }
        public int ACECallbackPort { get; set; }
        public string APIServer { get; set; }
        public int APIPort { get; set; }
        public bool ThreadingEnabled { get; set; }
    }
}
