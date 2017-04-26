using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using Ace.Adept.Server.Controls;
using Ace.Adept.Server.Motion;
using Ace.Core.Server;
using Ace.Core.Server.Motion;
using Ace.Core.Util;
using Nancy;
using Nancy.Hosting.Self;
using Newtonsoft.Json;
using System.Threading;

namespace CustomACEAPI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private const string _url = "http://localhost";
        private const int _port = 9001;
        private static NancyHost _nancy;
        private static AdeptAce adept_ace;

        public MainWindow()
        {
            adept_ace = new AdeptAce();
            InitializeComponent();
            OutputText.Document.Blocks.Clear();

            var configuration = new HostConfiguration()
            {
                UrlReservations = new UrlReservations()
                {
                    CreateAutomatically = true
                }
            };

            _nancy = new NancyHost(configuration, new Uri($"{_url}:{_port}/"));
        }

        private void RichTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        /// <summary>
        /// Starts the NancyFX server to allow it to start listening for requests on localhost:12345
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        void Start_APP(object sender, RoutedEventArgs e)
        {
            adept_ace.ConnectToServer();
            _nancy.Start();
            OutputText.Document.Blocks.Add(new Paragraph(new Run($"Listening on {_url}:{_port}/")));
        }

        /// <summary>
        /// Stops the NancyFX server
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        void Stop_APP(object sender, RoutedEventArgs e)
        {
            adept_ace.DisconnectFromServer();
            _nancy.Stop();
            OutputText.Document.Blocks.Add(new Paragraph(new Run("Successfuly stopped the HTTP server.")));
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

                        command.Execute(adept_ace.AceRobot, adept_ace.AceServer.CreateObject(typeof(CartesianMove)) as CartesianMove);

                        return HttpStatusCode.OK;
                    }
                    catch (Exception e)
                    {
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

        private static IAceServer ace;
        private static IAdeptRobot robot;
   
        public IAceServer AceServer
        {
            get
            {
                return ace;
            }
        }

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
                Console.WriteLine(controller.FullPath);
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

                    robot = ace.Root[robotPath] as IAdeptRobot;
                }
            }
        }

        public void DisconnectFromServer()
        {
            ace.Dispose();
            robot.Dispose();
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
        public bool StraightMotion { get; set; } // Get or set a flag indicating whether the motion should be straight-line. If false, motion will be joint-interpolated. 
        public string MotionEnd { get; set; } // One of: Blend, NoNull, SettleCoarse, or SettleFine
        public int SCurveProfile { get; set; } // Get or set the S-curve profile number, from 0 (for trapezoidal) to 8, or -1 to leave unchanged.
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
        /// <returns>
        /// Nothing
        /// </returns>
        public void Execute(IAdeptRobot robot, CartesianMove cartesianMove)
        {
            double[] jointPositions = robot.JointPosition;

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
            //output.Document.Blocks.Add(new Paragraph(new Run(currentPosition + " inrange check = " + inRange)));

            // Get the current robot configuration
            IMoveConfiguration moveConfig = robot.GetMoveConfiguration(jointPositions);

            // Create a motion object and command the robot to move
            cartesianMove.MoveConfiguration = moveConfig;
            Transform3D transform = new Transform3D(X, Y, Z, Yaw, Pitch, Roll);

            // t1 = -t1;
            cartesianMove.WorldLocation = currentPosition * transform;

            // Issue the move and wait until it is done
            robot.Move(cartesianMove);
            robot.WaitMoveDone();

            // Force the robot to issue a DETACH
            robot.AutomaticControlActive = false;
        }
    }
}
