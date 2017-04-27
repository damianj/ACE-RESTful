using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using Ace.Adept.Server.Controls;
using Ace.Adept.Server.Motion;
using Ace.Core.Server;
using Ace.Core.Server.Motion;
using Ace.Core.Util;
using Nancy;
using Nancy.Hosting.Self;
using Newtonsoft.Json;
using System.Threading;
using System.IO;
using System.Windows.Threading;

namespace CustomACEAPI
{
    /// <summary>The <see cref="CustomACEAPI"/> project implements a C# RESTful API for the Adept ACE server. 
    /// It allows robots to be controlled via a local HTTP server that is run on NancyFX (a light-weight 
    /// web framework), and allows Adept robots to be easily controlled via other mediums (e.g., LabView, 
    /// Python, or anything that can issue HTTP POST/GET requests).
    /// </summary>
    [System.Runtime.CompilerServices.CompilerGenerated]
    class NamespaceDoc
    {
    }

    /// <summary>Class that handles creating and maintaining an instance of the GUI as well as setting up the application for use.</summary>
    public partial class MainWindow : Window
    {
        private static Semaphore _SEMAPHORE = new Semaphore(1, 1);
        private const string _url = "http://localhost";
        private const int _port = 9001;
        private static NancyHost _nancy;
        private static AdeptAce adept_ace;
        private static Dispatcher gui_dispatcher;

        /// <summary>Initiates the GUI and preps everything needed to successfully start the NancyFX server and connect to the Adept ACE server </summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>void</c></returns>
        public MainWindow()
        {
            gui_dispatcher = Dispatcher;
            adept_ace = new AdeptAce();
            InitializeComponent();
            OutputText.Text = "";
            Console.SetOut(new MultiTextWriter(new TextBoxWriter(OutputText), Console.Out));

            // Create a URL reservation to allow the NancyFX server to start (i.e., prevent AutomaticUrlReservationCreationFailureException)
            var configuration = new HostConfiguration()
            {
                UrlReservations = new UrlReservations()
                {
                    CreateAutomatically = true
                }
            };

            // Prep the NancyFX server for use later on
            _nancy = new NancyHost(configuration, new Uri($"{_url}:{_port}/"));
            WriteOutput("App started successfully...\n---------------------------");
        }

        /// <summary>Starts the NancyFX server to allow it to start listening for requests on localhost:9001</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="sender">Object that triggered the call to this method</param>
        /// <param name="e">Event information of the routed event</param>
        /// <returns><c>void</c></returns>
        void Start_APP(object sender, RoutedEventArgs e)
        {
            // If we are already connected to the ACE server don't attempt to re-connect
            if(!adept_ace.Connected)
            {
                adept_ace.ConnectToServer();
            }
            
            // Start the HTTP server on localhost:9001
            _nancy.Start();
            WriteOutput($"Listening on: {_url}:{_port}/\n");
        }

        /// <summary>Stops the NancyFX server</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="sender">Object that triggered the call to this method</param>
        /// <param name="e">Event information of the routed event</param>
        /// <returns><c>void</c></returns>
        void Stop_APP(object sender, RoutedEventArgs e)
        {
            // Stop the HTTP Server
            _nancy.Stop();
            WriteOutput("Successfully stopped the HTTP server.\n------------------------------------\n");
        }

        /// <summary>Writes to the console and the GUI text-box. Necessary to re-route calls from different threads onto the thread the GUI is running on.</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="output_text">String to be written to the console and GUI text-box</param>
        /// <returns><c>void</c></returns>
        public static void WriteOutput(String output_text)
        {
            gui_dispatcher.Invoke(DispatcherPriority.Normal, new Action(() =>
            {
                Console.WriteLine(output_text);
            }));
        }

        /// <summary>Class to handle CartesianMove API calls</summary>
        /// <author>Damian Jimenez</author>
        public class CartesianMoveAPI : NancyModule
        {
            /// <summary>API endpoint for the Cartesian Move command</summary>
            /// <author>Damian Jimenez</author>
            /// <returns><c>void</c></returns>
            public CartesianMoveAPI()
            {
                Get["/api/move/cartesian"] = _ =>
                {
                    return new Response()
                    {
                        StatusCode = HttpStatusCode.BadRequest,
                        ContentType = "application/json",
                        ReasonPhrase = "GET requests are not supported by this endpoint, use a POST request instead.",
                        Headers = new Dictionary<string, string>()
                        {
                            {
                                "Content-Type", "application/json"
                            }
                        },
                    };
                };

                Post["/api/move/cartesian"] = _ =>
                {
                    try
                    {
                        var id = Request.Body;
                        var length = Request.Body.Length;
                        var data = new byte[length];

                        id.Read(data, 0, (int)length);
                        var body = Encoding.Default.GetString(data);
                        var command = JsonConvert.DeserializeObject<CartesianMoveCommand>(body);

                        WriteOutput($"Received the following POST request:\n{body.ToString()}\n");
                        command.Execute(adept_ace.AceRobot, adept_ace.AceServer.CreateObject(typeof(CartesianMove)) as CartesianMove);

                        return HttpStatusCode.OK;
                    }
                    catch (Exception e)
                    {
                        WriteOutput($"ERROR:\n{e.Message}\n");
                        string jsonString = $"{{ status: \"failure\", error: \"{e.Message}\" }}";
                        byte[] jsonBytes = Encoding.UTF8.GetBytes(jsonString);


                        return new Response()
                        {
                            StatusCode = HttpStatusCode.BadRequest,
                            ContentType = "application/json",
                            ReasonPhrase = "Unable to successfully interpret the request.",
                            Headers = new Dictionary<string, string>()
                            {
                                {
                                    "Content-Type", "application/json"
                                },
                                {
                                    "X-Custom-Header", "Please check the error message below, make sure the JSON payload is properly formatted, and that the robot is initialized properly."
                                }
                            },
                            Contents = c => c.Write(jsonBytes, 0, jsonBytes.Length)
                        };
                    }
                };
            }
        }

        /// <summary>Class to handle setting up and executing a CartesianMove from Ace.Adept.Server.Motion</summary>
        /// <author>Damian Jimenez</author>
        public class CartesianMoveCommand
        {
            /// <summary>Mapping of all the possible values for <c>MotionEnd</c>, to be easily accessed with a <c>String</c> parsed from the JSON file in the HTTP POST request</summary>
            private static Dictionary<string, MotionEnd> MOTION_END = new Dictionary<string, MotionEnd>()
            {
                { "Blend", Ace.Adept.Server.Motion.MotionEnd.Blend },
                { "NoNull", Ace.Adept.Server.Motion.MotionEnd.NoNull },
                { "SettleCoarse", Ace.Adept.Server.Motion.MotionEnd.SettleCoarse },
                { "SettleFine", Ace.Adept.Server.Motion.MotionEnd.SettleFine },
            };

            /// <summary>The name of this type of motion, derived from the ACE command name.</summary>
            public string Name = "Cartesian Move";
            /// <summary>Maximum acceleration of the robot when it moves.</summary>
            public int Accel { get; set; }
            /// <summary>Maximum deceleration of the robot when it moves.</summary>
            public int Decel { get; set; }
            /// <summary>Maximum speed of the robot when it moves.</summary>
            public int Speed { get; set; }
            /// <summary>Determines whether the robot's motion should be straight or not (i.e., true: straight-line, false: motion will be joint-interpolated)</summary>
            public bool StraightMotion { get; set; }
            /// <summary>Determines how the motion should finish (i.e., Blend, NoNull, SettleCoarse, or SettleFine)</summary>
            public string MotionEnd { get; set; }
            /// <summary>Specifies the S-curve trajectory profile, from 0 (for trapezoidal) to 8, or -1 to leave unchanged.</summary>
            public int SCurveProfile { get; set; }
            /// <summary>Specifies the X coordinate of the motion</summary>
            public double X { get; set; }
            /// <summary>Specifies the Y coordinate of the motion</summary>
            public double Y { get; set; }
            /// <summary>Specifies the Z coordinate of the motion</summary>
            public double Z { get; set; }
            /// <summary>Specifies the Yaw coordinate of the motion</summary>
            public double Yaw { get; set; }
            /// <summary>Specifies the Pitch coordinate of the motion</summary>
            public double Pitch { get; set; }
            /// <summary>Specifies the Roll coordinate of the motion</summary>
            public double Roll { get; set; }

            /// <summary>Method that executes a command for an instance of the CartesianMoveCommand class</summary>
            /// <author>Damian Jimenez</author>
            /// <param name="robot">The robot that is to be controlled via the API call</param>
            /// <param name="cartesianMove">Cartesian move object to handle calculating the motion of the robot</param>
            /// <returns><c>void</c></returns>
            public void Execute(IAdeptRobot robot, CartesianMove cartesianMove)
            {
                // Get the current joint positions of the robot
                double[] jointPositions = robot.JointPosition;

                // Print out joint information for the user to see
                foreach(var joint in jointPositions.Select((value, i) => new { i, value }))
                {
                    WriteOutput($"joint[{joint.i}] = {joint.value}");
                }

                // Assign the cartesianMove the parameters that were passed via the API call
                cartesianMove.Param.Accel = Accel;
                cartesianMove.Param.Decel = Decel;
                cartesianMove.Param.Speed = Speed;
                cartesianMove.Param.Straight = StraightMotion;
                cartesianMove.Param.MotionEnd = MOTION_END[MotionEnd];
                cartesianMove.Param.SCurveProfile = SCurveProfile;

                // Transform the current joint position to a world location
                Transform3D loc = robot.JointToWorld(jointPositions);

                // Check if the current location is inrange           
                Transform3D currentPosition = robot.WorldLocationWithTool;
                int inRange = robot.InRange(currentPosition);
                WriteOutput($"[{currentPosition}], inrange check = {inRange}\n");

                // Get the current robot configuration
                IMoveConfiguration moveConfig = robot.GetMoveConfiguration(jointPositions);

                // Create a new Transform3D object specifying how the robot should move
                cartesianMove.MoveConfiguration = moveConfig;
                Transform3D transform = new Transform3D(X, Y, Z, Yaw, Pitch, Roll);

                // Calculate the new position of the robot based on the transform and the robots current position
                cartesianMove.WorldLocation = currentPosition * transform;

                // Issue the move and wait until it is done
                robot.Move(cartesianMove);
                robot.WaitMoveDone();

                // Force the robot to issue a DETACH
                robot.AutomaticControlActive = false;
            }
        }
    }

    /// <summary>Class to assist in re-routing <c>stdout</c> to the GUI text-box that is displayed</summary>
    /// <author>Damian Jimenez -- [http://stackoverflow.com/a/18727100]</author>
    public class TextBoxWriter : TextWriter
    {
        private TextBox textbox;

        /// <summary>Constructor method that instantiates the <c>TextBox</c> instance to the appropriate element in the GUI</summary>
        /// <param name="textbox"><c>TextBox</c> instance that is to be used to write to.</param>
        /// <author>Damian Jimenez</author>
        public TextBoxWriter(TextBox textbox)
        {
            this.textbox = textbox;
        }

        /// <summary>Override of the <c>Write</c> method</summary>
        /// <param name="value"><c>char</c> to be written</param>
        /// <returns><c>void</c></returns>
        /// <author>Damian Jimenez</author>
        public override void Write(char value)
        {
            textbox.Text += value;
        }

        /// <summary>Override of the <c>Write</c> method, writes to each <c>TextWriter</c> in the list of <c>TextWriter</c>s</summary>
        /// <param name="value"><c>string</c> to be written</param>
        /// <returns><c>void</c></returns>
        /// <author>Damian Jimenez</author>
        public override void Write(string value)
        {
            textbox.Text += value;
        }

        /// <summary>Override of the <c>Encoding</c> method, returns the <c>Encoding</c> of the <c>TextBox</c></summary>
        /// <returns><c>Encoding.ASCII</c></returns>
        /// <author>Damian Jimenez</author>
        public override Encoding Encoding
        {
            get { return Encoding.ASCII; }
        }
    }

    /// <summary>Class to assist in re-routing <c>stdout</c> to multiple outputs. In our case to re-route it to the text-box that is displayed and also to the console as well.</summary>
    /// <author>Damian Jimenez -- [http://stackoverflow.com/a/18727100]</author>
    public class MultiTextWriter : TextWriter
    {
        private IEnumerable<TextWriter> writers;

        /// <summary>Overload of the constructor method that takes an <c>IEnumerable</c> of type <c>TextWriter</c> to be converted to a list.</summary>
        /// <param name="writers"><c>IEnumerable</c> of <c>TextWriter</c> objects that are to be converted to a list, to be used to route <c>stdout</c> to.</param>
        /// <author>Damian Jimenez</author>
        public MultiTextWriter(IEnumerable<TextWriter> writers)
        {
            this.writers = writers.ToList();
        }

        /// <summary>Overload of the constructor method that takes a list of <c>TextWriter</c> objects.</summary>
        /// <param name="writers">List of <c>TextWriter</c> objects that are to be used to route <c>stdout</c> to.</param>
        /// <author>Damian Jimenez</author>
        public MultiTextWriter(params TextWriter[] writers)
        {
            this.writers = writers;
        }

        /// <summary>Override of the <c>Write</c> method</summary>
        /// <param name="value"><c>char</c> to be written</param>
        /// <returns><c>void</c></returns>
        /// <author>Damian Jimenez</author>
        public override void Write(char value)
        {
            foreach (var writer in writers)
                writer.Write(value);
        }

        /// <summary>Override of the <c>Write</c> method, writes to each <c>TextWriter</c> in the list of <c>TextWriter</c>s</summary>
        /// <param name="value"><c>string</c> to be written</param>
        /// <returns><c>void</c></returns>
        /// <author>Damian Jimenez</author>
        public override void Write(string value)
        {
            foreach (var writer in writers)
                writer.Write(value);
        }

        /// <summary>Override of the <c>Flush</c> method, flushes each <c>TextWriter</c> in the list of <c>TextWriter</c>s</summary>
        /// <returns><c>void</c></returns>
        /// <author>Damian Jimenez</author>
        public override void Flush()
        {
            foreach (var writer in writers)
                writer.Flush();
        }

        /// <summary>Override of the <c>Close</c> method, closes each <c>TextWriter</c> in the list of <c>TextWriter</c>s</summary>
        /// <returns><c>void</c></returns>
        /// <author>Damian Jimenez</author>
        public override void Close()
        {
            foreach (var writer in writers)
                writer.Close();
        }

        /// <summary>Override of the <c>Encoding</c> method, returns the <c>Encoding</c> of the <c>TextWriter</c>s</summary>
        /// <returns><c>Encoding.ASCII</c></returns>
        /// <author>Damian Jimenez</author>
        public override Encoding Encoding
        {
            get { return Encoding.ASCII; }
        }
    }

    /// <summary>Class that wraps the Custom ACE API server and all of its associated classes and methods</summary>
    /// <author>Damian Jimenez</author>
    public class AdeptAce
    {
        private const string REMOTING_NAME = "ace";
        private const string REMOTING_HOST = "localhost";
        private const int CALLBACK_PORT = 43431;
        private const int REMOTING_PORT = 43434;

        private static bool ACE_SERVER_ON = false;
        private static IAceServer ace;
        private static IAdeptRobot robot;

        /// <summary>Method that allows a user to check whether the connection to the ACE server has been started</summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>bool</c> specifying whether the connection to the ACE server is active or not</returns>
        public bool Connected
        {
            get
            {
                return ACE_SERVER_ON;
            }
        }

        /// <summary>Method that returns the class instance of IAceServer</summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>IAceServer</c> the ace server used to communicate with ACE and the robot</returns>
        public IAceServer AceServer
        {
            get
            {
                return ace;
            }
        }

        /// <summary>Method that returns the class instance of IAdeptRobot</summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>IAdeptRobot</c> the robot that is to be controlled</returns>
        public IAdeptRobot AceRobot
        {
            get
            {
                return robot;
            }
        }

        /// <summary>Method that connects to the Adept ACE server and sets up the robot for use</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="controllerPath">Specifies where the server should search for the controller, can be found by opening up a default workspace in Adept ACE and connecting to a desired robot.</param>
        /// <param name="robotPath">Specifies where the server should search for the robot, can be found by opening up a default workspace in Adept ACE and connecting to a desired robot.</param>
        /// <returns><c>void</c></returns>
        public void ConnectToServer(String controllerPath = "/SmartController 9/SmartController 9", String robotPath = "/SmartController 9/R1 Viper650")
        {
            // Set up the server to allow remote connections and connect to the ACE server
            RemotingUtil.InitializeRemotingSubsystem(true, CALLBACK_PORT);
            ace = (IAceServer)RemotingUtil.GetRemoteServerObject(typeof(IAceServer), REMOTING_NAME, REMOTING_HOST, REMOTING_PORT);

            // Get a list of all the controllers in the system, and enable the appropriate one
            foreach (IAdeptController controller in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptController)), true))
            {
                // Print out all the controllers that are found and available
                // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
                Console.WriteLine($"Found controller: {controller.FullPath}");
                if(controllerPath.Equals(controller.FullPath))
                {
                    // Set up the controller
                    controller.Enabled = true;
                    controller.HighPower = true;
                    controller.Calibrate();
                    if (!controller.IsEVPlus)
                    {
                        controller.DryRun = true;
                        controller.DryRun = false;
                    }

                    // Add any robots that are found associated with that controller
                    AdeptControllerUtil.AddAllRobots(ace, controller, ace.Root);

                    // Print out all the robots that are found connected to the workspace and available
                    foreach (IAdeptRobot available_robot in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptRobot)), true))
                    {
                        // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
                        Console.WriteLine($"Found robot: {available_robot.FullPath}");
                        if(robotPath.Equals(available_robot.FullPath))
                        {
                            robot = available_robot;
                        }
                    }
                }
            }

            // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
            Console.WriteLine($"Connected to the Adept ACE server successfully on: {REMOTING_HOST}:{REMOTING_PORT}/");
            ACE_SERVER_ON = true;
        }
    }
}
