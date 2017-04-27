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

/// <summary>
/// The following project implements a C# API for the Adept ACE server, it allows robots to be controlled via
/// a local server that is run on NancyFX (a light-weight web framework) and allows Adept robots to be easily
/// controlled via other methods (e.g., LabView, Python, or anything that can issue HTTP POST/GET requests).
/// </summary>
namespace CustomACEAPI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static Semaphore _SEMAPHORE = new Semaphore(1, 1);
        private const string _url = "http://localhost";
        private const int _port = 9001;
        private static NancyHost _nancy;
        private static AdeptAce adept_ace;

        /// <summary>
        /// Initiates the GUI and preps everything needed to successfully start the NancyFX server and connect to the Adept ACE server 
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        /// <returns>
        /// Noting
        /// </returns>
        public MainWindow()
        {
            adept_ace = new AdeptAce();
            InitializeComponent();
            OutputText.Text = "";
            Console.SetOut(new MultiTextWriter(new TextBoxWriter(OutputText), Console.Out));

            var configuration = new HostConfiguration()
            {
                UrlReservations = new UrlReservations()
                {
                    CreateAutomatically = true
                }
            };

            _nancy = new NancyHost(configuration, new Uri($"{_url}:{_port}/"));
            Console.WriteLine("App started successfully...\n---------------------------");
        }

        /// <summary>
        /// Starts the NancyFX server to allow it to start listening for requests on localhost:9001
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        /// <param name="sender">
        /// Object that triggered the call to this method
        /// </param>
        /// <param name="e">
        /// Event information of the routed event
        /// </param>
        /// <returns>
        /// Noting
        /// </returns>
        void Start_APP(object sender, RoutedEventArgs e)
        {
            if(!adept_ace.Connected)
            {
                adept_ace.ConnectToServer();
            }
            
            _nancy.Start();
            Console.WriteLine($"Listening on {_url}:{_port}/\n");
        }

        /// <summary>
        /// Stops the NancyFX server
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        /// <param name="sender">
        /// Object that triggered the call to this method
        /// </param>
        /// <param name="e">
        /// Event information of the routed event
        /// </param>
        /// <returns>
        /// Noting
        /// </returns>
        void Stop_APP(object sender, RoutedEventArgs e)
        {
            _nancy.Stop();
            Console.WriteLine("Successfuly stopped the HTTP server.\n------------------------------------\n");
        }


        /// <summary>
        /// Class to handle CartesianMove API calls
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        public class CartesianMoveAPI : NancyModule
        {
            /// <summary>
            /// API endpoint for the Cartesian Move command
            /// </summary>
            /// <author>
            /// Damian Jimenez
            /// </author>
            /// <returns>
            /// Nothing
            /// </returns>
            public CartesianMoveAPI()
            {
                /// <summary>
                /// GET request handler
                /// </summary>
                /// <author>
                /// Damian Jimenez
                /// </author>
                /// <returns>
                /// Response object specifying to the user that GET requests are not supported
                /// </returns>
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

                /// <summary>
                /// POST request handler. Takes the JSON payload and attempts to parse the commands and execute a CartesianMove using the Ace.Adept.Server.Motion
                /// </summary>
                /// <author>
                /// Damian Jimenez
                /// </author>
                /// <returns>
                /// HttpStatusCode.OK or a Response object detailing what went wrong
                /// </returns>
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

                        Console.WriteLine($"Recieved the following POST request:\n{body.ToString()}\n");
                        Thread command_thread = new Thread(() => command.Execute(adept_ace.AceRobot, adept_ace.AceServer.CreateObject(typeof(CartesianMove)) as CartesianMove));
                        command_thread.Start();

                        return HttpStatusCode.OK;
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine($"ERROR:\n{e.Message}\n");
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

        /// <summary>
        /// Class to handle setting up and executing a CartesianMove from Ace.Adept.Server.Motion
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        public class CartesianMoveCommand
        {
            private static Dictionary<string, MotionEnd> MOTION_END = new Dictionary<string, MotionEnd>()
            {
                { "Blend", Ace.Adept.Server.Motion.MotionEnd.Blend },
                { "NoNull", Ace.Adept.Server.Motion.MotionEnd.NoNull },
                { "SettleCoarse", Ace.Adept.Server.Motion.MotionEnd.SettleCoarse },
                { "SettleFine", Ace.Adept.Server.Motion.MotionEnd.SettleFine },
            };

            public string Name = "Cartesian Move";
            public int Accel { get; set; }
            public int Decel { get; set; }
            public int Speed { get; set; }
            public bool StraightMotion { get; set; }    // Get or set a flag indicating whether the motion should be straight-line. If false, motion will be joint-interpolated. 
            public string MotionEnd { get; set; }       // One of: Blend, NoNull, SettleCoarse, or SettleFine
            public int SCurveProfile { get; set; }      // Get or set the S-curve profile number, from 0 (for trapezoidal) to 8, or -1 to leave unchanged.
            public double X { get; set; }
            public double Y { get; set; }
            public double Z { get; set; }
            public double Yaw { get; set; }
            public double Pitch { get; set; }
            public double Roll { get; set; }

            /// <summary>
            /// Method that executes a command for an instance of the CartesianMoveCommand class
            /// </summary>
            /// <author>
            /// Damian Jimenez
            /// </author>
            /// <param name="robot">
            /// The robot that is to be controlled via the API call
            /// </param>
            /// <param name="cartesianMove">
            /// Cartesian move object to handle calculating the motion of the robot
            /// </param>
            /// <returns>
            /// Nothing
            /// </returns>
            public void Execute(IAdeptRobot robot, CartesianMove cartesianMove)
            {
                _SEMAPHORE.WaitOne();
                /**********************************************************************
                *** Protected block prevents this command from firing con-currently ***
                ********* and sending conflicting instructions to the robot. **********
                **********************************************************************/
                {
                    // Get the current joint positions of the robot
                    double[] jointPositions = robot.JointPosition;

                    // Print out joint information for the user to see
                    foreach(var joint in jointPositions.Select((value, i) => new { i, value }))
                    {
                        Console.WriteLine($"joint[{joint.i}] = {joint.value}");
                    }

                    // Assign the cartesianMove the parameteres that were passed via the API call
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
                    Console.WriteLine(currentPosition + " inrange check = " + inRange);

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
                /*********************************************************************
                *********************** End of protected block ***********************
                **********************************************************************
                *********************************************************************/
                _SEMAPHORE.Release();
            }
        }
    }

    /// <summary>
    /// Class to assist in re-routing stdout to the GUI textbox that is displayed
    /// </summary>
    /// <author>
    /// Damian Jimenez -- [http://stackoverflow.com/a/18727100]
    /// </author>
    public class TextBoxWriter : TextWriter
    {
        private TextBox textbox;

        public TextBoxWriter(TextBox textbox)
        {
            this.textbox = textbox;
        }

        public override void Write(char value)
        {
            textbox.Text += value;
        }

        public override void Write(string value)
        {
            textbox.Text += value;
        }

        public override Encoding Encoding
        {
            get { return Encoding.ASCII; }
        }
    }

    /// <summary>
    /// Class to assist in re-routing stdout to multiple outputs, in our case
    /// to re-route it to the textbox that is displayed and also display it on
    /// the console as well.
    /// </summary>
    /// <author>
    /// Damian Jimenez -- [http://stackoverflow.com/a/18727100]
    /// </author>
    public class MultiTextWriter : TextWriter
    {
        private IEnumerable<TextWriter> writers;
        public MultiTextWriter(IEnumerable<TextWriter> writers)
        {
            this.writers = writers.ToList();
        }
        public MultiTextWriter(params TextWriter[] writers)
        {
            this.writers = writers;
        }

        public override void Write(char value)
        {
            foreach (var writer in writers)
                writer.Write(value);
        }

        public override void Write(string value)
        {
            foreach (var writer in writers)
                writer.Write(value);
        }

        public override void Flush()
        {
            foreach (var writer in writers)
                writer.Flush();
        }

        public override void Close()
        {
            foreach (var writer in writers)
                writer.Close();
        }

        public override Encoding Encoding
        {
            get { return Encoding.ASCII; }
        }
    }

    /// <summary>
    /// Class that wraps the Custom ACE API server and all of its associated classes and methods
    /// </summary>
    /// <author>
    /// Damian Jimenez
    /// </author>
    public class AdeptAce
    {
        private const string REMOTING_NAME = "ace";
        private const string REMOTING_HOST = "localhost";
        private const int CALLBACK_PORT = 43431;
        private const int REMOTING_PORT = 43434;

        private static bool ACE_SERVER_ON = false;
        private static IAceServer ace;
        private static IAdeptRobot robot;

        /// <summary>
        /// Method that allows a user to check whether the connection to the ACE server has been started
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        /// <returns>
        /// bool specifying whether the connection to the ACE server is active or not
        /// </returns>
        public bool Connected
        {
            get
            {
                return ACE_SERVER_ON;
            }
        }

        /// <summary>
        /// Method that returns the class instance of IAceServer
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        /// <returns>
        /// IAceServer the ace server used to communicate with ACE and the robot
        /// </returns>
        public IAceServer AceServer
        {
            get
            {
                return ace;
            }
        }

        /// <summary>
        /// Method that returns the class instance of IAdeptRobot
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        /// <returns>
        /// IAdeptRobot the robot that is to be controlled
        /// </returns>
        public IAdeptRobot AceRobot
        {
            get
            {
                return robot;
            }
        }

        /// <summary>
        /// Method that connects to the Adept ACE server and sets up the robot for use
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        /// <param name="controllerPath">
        /// Specifies where the server should search for the controller, can be found by opening up a default workspace in Adept ACE and connecting to a desired robot.
        /// </param>
        /// <param name="robotPath">
        /// Specifies where the server should search for the robot, can be found by opening up a default workspace in Adept ACE and connecting to a desired robot.
        /// </param>
        /// <returns>
        /// Nothing
        /// </returns>
        public void ConnectToServer(String controllerPath = "/SmartController 9/SmartController 9", String robotPath = "/SmartController 9/R1 Viper650")
        {

            RemotingUtil.InitializeRemotingSubsystem(true, CALLBACK_PORT);
            ace = (IAceServer)RemotingUtil.GetRemoteServerObject(typeof(IAceServer), REMOTING_NAME, REMOTING_HOST, REMOTING_PORT);

            // Get a list of all the controllers in the system, and enable the appropriate one
            foreach (IAdeptController controller in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptController)), true))
            {
                // Print out all the controllers that are found and available
                Console.WriteLine($"Found controller: {controller.FullPath}");
                if(controllerPath.Equals(controller.FullPath))
                {
                    controller.Enabled = true;
                    controller.HighPower = true;
                    controller.Calibrate();
                    if (!controller.IsEVPlus)
                    {
                        controller.DryRun = true;
                        controller.DryRun = false;
                    }
                    AdeptControllerUtil.AddAllRobots(ace, controller, ace.Root);

                    // Print out all the robots that are found connected to the workspace and available
                    foreach (IAdeptController robot in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptRobot)), true))
                    {
                        Console.WriteLine($"Found robot: {robot}");
                    }

                    robot = ace.Root[robotPath] as IAdeptRobot;
                }
            }

            Console.WriteLine($"Connected to the Adept ACE server succesfully on: {REMOTING_HOST}:{REMOTING_PORT}/");
            ACE_SERVER_ON = true;
        }
    }
}
