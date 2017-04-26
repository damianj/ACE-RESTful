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
        private const int _port = 12345;
        private static NancyHost _nancy;
        private static APIServer api_server;

        public MainWindow()
        {
            api_server = new APIServer();
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

                        
                        command.Execute(api_server.AceRobot, api_server.AceServer.CreateObject(typeof(CartesianMove)) as CartesianMove);

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
    public class APIServer
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
        /// Class to handle setting up the connection to the Adept ACE server
        /// </summary>
        /// <author>
        /// Damian Jimenez
        /// </author>
        private class AdeptAce
        {
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

                IAdeptController controller = ace.Root[controllerPath] as IAdeptController;
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

    /// <summary>
    /// Class to handle setting up and executing a CartesianMove from Ace.Adept.Server.Motion
    /// </summary>
    /// <author>
    /// Damian Jimenez
    /// </author>
    public class CartesianMoveCommand
    {
        public string Name = "Cartesian Move";
        public int Accel { get; set; }
        public int Decel { get; set; }
        public int Speed { get; set; }
        public bool StraightMotion { get; set; }
        public string MotionEnd { get; set; }
        public int SCurveProfile { get; set; }

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
            Transform3D t1 = new Transform3D(10, 10, 0);

            t1 = -t1;
            cartesianMove.WorldLocation = currentPosition * t1;

            // Issue the move and wait until it is done
            robot.Move(cartesianMove);
            robot.WaitMoveDone();

            // Force the robot to issue a DETACH
            robot.AutomaticControlActive = false;
        }
    }
}
