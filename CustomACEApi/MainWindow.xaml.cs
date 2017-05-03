using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using Ace.Adept.Server.Motion;
using Ace.Core.Server;
using Ace.Core.Server.Motion;
using Nancy;
using Nancy.Hosting.Self;
using Newtonsoft.Json;
using System.Threading;
using System.IO;
using System.Windows.Threading;
using System.Collections.ObjectModel;
using System.Windows.Controls;

namespace CustomACEAPI
{
    /// <summary>Class that handles creating and maintaining an instance of the GUI as well as setting up the application for use.</summary>
    public partial class MainWindow : Window
    {
        private static Semaphore _SEMAPHORE = new Semaphore(1, 1);
        private static TextBlock _SYSTEM_STATUS_TEXT;
        private static bool _API_SERVER_ON = false;
        private static bool _ROBOT_BUSY = false;
        private static string _CURRENT_CONTROLLER;
        private static string _CURRENT_ROBOT;
        private static double[] _ROBOT_JOINTS;
        private static int _CARTESIAN_MOVES = 0;
        private static int _JOINT_MOVES = 0;
        private static int _GET_REQUESTS = 0;
        private static int _POST_REQUESTS = 0;
        private static int _CURRENT_MOVE_CMDS = 0;
        private static APPConfig app_config;
        private static NancyHost _nancy;
        private static AdeptAce adept_ace;
        private static Dispatcher gui_dispatcher;
        private static HostConfiguration configuration;
        private static ObservableCollection<string> controllers;
        private static ObservableCollection<string> robots;

        /// <summary>Initiates the GUI and preps everything needed to successfully start the NancyFX server and connect to the Adept ACE server </summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>void</c></returns>
        public MainWindow()
        {
            //IntelCamera camera = new IntelCamera();
            //camera.StartCamera(100);
            //camera.config_reader();
            //camera.process_frame();
            //camera.StopCamera();
            // Read the settings in the config file and store these for later use in setting up and connecting to the servers
            using (StreamReader reader = new StreamReader("../../../config.json"))
            {
                string json = reader.ReadToEnd();
                app_config = JsonConvert.DeserializeObject<APPConfig>(json);
            }

            // Initialize GUI elements and set up some things to get the interface ready
            gui_dispatcher = Dispatcher;
            InitializeComponent();
            _SYSTEM_STATUS_TEXT = SystemStatusBarText;
            OutputText.Text = "";

            // Instantiate an instance of AdeptAce which we will use to connect to the ACE server
            adept_ace = new AdeptAce();

            // Re-route STDOUT to the GUI text-box and the console as well
            Console.SetOut(new MultiTextWriter(new TextBoxWriter(OutputText), Console.Out));

            // Create a URL reservation to allow the NancyFX server to start (i.e., prevent AutomaticUrlReservationCreationFailureException)
            configuration = new HostConfiguration()
            {
                UrlReservations = new UrlReservations()
                {
                    CreateAutomatically = true
                }
            };

            // Update the status bar with the initial status
            UpdateStatusBar();

            // Configure the NancyFX server for later use
            _nancy = new NancyHost(configuration, new Uri($"{app_config.APIServer}:{app_config.APIPort}/"));
            WriteOutput("Application started successfully...\n-----------------------------------");
        }

        /// <summary>Starts the NancyFX server to allow it to start listening for requests on the host:port specified in config.json</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="sender">Object that triggered the call to this method</param>
        /// <param name="e">Event information of the routed event</param>
        /// <returns><c>void</c></returns>
        void Start_APP(object sender, RoutedEventArgs e)
        {
            try
            {
                // Only do all this once, when we have just started the application
                if (!adept_ace.Connected)
                {
                    // Get the available Controllers and Robots by probing the server and list them in the GUI
                    ObservableCollection<string>[] controllers_and_robots;

                    controllers_and_robots = adept_ace.ConnectToServer(app_config.ACEServer, app_config.ACEPort, app_config.ACEName, app_config.ACECallbackPort);
                    controllers = controllers_and_robots[0];
                    robots = controllers_and_robots[1];

                    ControllerPathComboBox.ItemsSource = controllers;
                    RobotPathComboBox.ItemsSource = robots;
                }
                // If we are already connected let the user know and skip the previous step
                else
                {
                    WriteOutput($"Already connected to the ACE server on: {app_config.ACEServer}:{app_config.ACEPort}/\n");
                }

                // If the API server isn't already on then start it
                if (!_API_SERVER_ON)
                {
                    // Start the HTTP server on the host:port specified in config.json
                    _nancy.Start();
                    WriteOutput("Successfully started the HTTP server.\n------------------------------------\n");
                    WriteOutput($"Listening on: {app_config.APIServer}:{app_config.APIPort}/\n");
                    _API_SERVER_ON = true;
                }
                // Else let the user know and skip trying to turn on the API server
                else
                {
                    WriteOutput($"The API server is already on and listening on: {app_config.APIServer}:{app_config.APIPort}/\n");
                }

            }
            catch(Exception ex)
            {
                WriteOutput($"ERROR: Unable to connect to start the HTTP server.\n{ex.Message}\n");
            }
        }

        /// <summary>Stops the NancyFX server</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="sender">Object that triggered the call to this method</param>
        /// <param name="e">Event information of the routed event</param>
        /// <returns><c>void</c></returns>
        void Stop_APP(object sender, RoutedEventArgs e)
        {
            try
            {
                // If the API server is on then turn it off
                if(_API_SERVER_ON)
                {
                    _CARTESIAN_MOVES = 0;
                    _JOINT_MOVES = 0;
                    _GET_REQUESTS = 0;
                    _POST_REQUESTS = 0;
                    _CURRENT_MOVE_CMDS = 0;

                    // Stop the HTTP Server
                    _nancy.Stop();
                    WriteOutput("Successfully stopped the HTTP server.\n------------------------------------\n");
                    _API_SERVER_ON = false;
                }
                // Else if the API server is already off let the user know and skip doing so
                else
                {
                    WriteOutput("The API server is already turned off.\n");
                }
            }
            catch(Exception ex)
            {
                WriteOutput($"ERROR: Unable to stop the HTTP server properly, or it has not been started.\n{ex.Message}\n");
            }

        }

        /// <summary>Load the controller and robot currently selected in the combo-boxes</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="sender">Object that triggered the call to this method</param>
        /// <param name="e">Event information of the routed event</param>
        /// <returns><c>void</c></returns>
        void Load_ControllerAndRobot(object sender, RoutedEventArgs e)
        {
            // Load the Controller and Robot that are currently selected in the drop down menus of the GUI
            adept_ace.LoadControllerAndRobot(ControllerPathComboBox.Text, RobotPathComboBox.Text);
            _CURRENT_CONTROLLER = ControllerPathComboBox.Text;
            _CURRENT_ROBOT = RobotPathComboBox.Text;
        }

        /// <summary>Get's the robot's current joint positions and assigns it to the class variable _ROBOT_JOINTS</summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>void</c></returns>
        static void GetRobotJoints()
        {
            // Get the current joint positions of the robot
            gui_dispatcher.Invoke(DispatcherPriority.Normal, new Action(() =>
            {
                _ROBOT_JOINTS = adept_ace.GetJointPositions();
            }));
        }

        /// <summary>Updates the application status bar with how many Cartesian Moves, Joint Moves, GET requests, and POST requests have been issued to the server. This only includes requests to the API endpoints.</summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>void</c></returns>
        public static void UpdateStatusBar()
        {
            // Update the status bar with the current status
            gui_dispatcher.Invoke(DispatcherPriority.Normal, new Action(() =>
            {
                _SYSTEM_STATUS_TEXT.Text = $"Cartesian Moves: {_CARTESIAN_MOVES} | Joint Moves: {_JOINT_MOVES} | GETs: {_GET_REQUESTS} | POSTs: {_POST_REQUESTS}";
            }));
        }
        /// <summary>Writes to the console and the GUI text-box. Necessary to re-route calls from different threads onto the thread the GUI is running on.</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="output_text">String to be written to the console and GUI text-box</param>
        /// <returns><c>void</c></returns>
        public static void WriteOutput(string output_text)
        {
            gui_dispatcher.Invoke(DispatcherPriority.Normal, new Action(() =>
            {
                Console.WriteLine(output_text);
            }));
        }

        /// <summary>Class to handle landing page of the application serer</summary>
        /// <author>Damian Jimenez</author>
        public class IndexPage : NancyModule
        {
            /// <summary>Endpoint for the landing page</summary>
            /// <author>Damian Jimenez</author>
            /// <returns><c>void</c></returns>
            public IndexPage()
            {
                Get["/"] = _ => View["index"];

                Post["/"] = _ => View["index"];
            }
        }

        /// <summary>Class to handle System info GET requests</summary>
        /// <author>Damian Jimenez</author>
        public class InfoAPI : NancyModule
        {
            /// <summary>API endpoint to handle all GET requests aimed at getting information regarding the current status of the system.</summary>
            /// <author>Damian Jimenez</author>
            /// <returns><c>void</c></returns>
            public InfoAPI()
            {
                Get["/api/system/info"] = _ =>
                {
                    _GET_REQUESTS += 1;
                    UpdateStatusBar();

                    GetRobotJoints();
                    string is_robot_busy = _ROBOT_BUSY.ToString().ToLower();
                    string joint_string = String.Join(",", _ROBOT_JOINTS.Select(p => p.ToString()).ToArray());
                    string jsonString = $"{{ ace_server_url\": \"{app_config.ACEServer}\", " +
                                        $"\"ace_server_por\": {app_config.ACEPort}, " +
                                        $"\"api_server_url\": \"{app_config.APIServer}\", " +
                                        $"\"api_server_port\": {app_config.APIPort}, " +
                                        $"\"controller\": \"{_CURRENT_CONTROLLER}\", " +
                                        $"\"robot\": \"{_CURRENT_ROBOT}\", " +
                                        $"\"robot_busy\": {is_robot_busy}, " +
                                        $"\"robot_joints\": {joint_string} }}";

                    byte[] jsonBytes = Encoding.UTF8.GetBytes(jsonString);

                    return new Response()
                    {
                        StatusCode = HttpStatusCode.OK,
                        ContentType = "application/json",
                        ReasonPhrase = "POST requests are not supported by this endpoint, use a GET request instead.",
                        Headers = new Dictionary<string, string>()
                        {
                            {
                                "Content-Type", "application/json"
                            }
                        },
                        Contents = c => c.Write(jsonBytes, 0, jsonBytes.Length)
                    };
                };

                Get["/api/system/robot/busy"] = _ =>
                {
                    _GET_REQUESTS += 1;
                    UpdateStatusBar();

                    string is_robot_busy = _ROBOT_BUSY.ToString().ToLower();
                    //WriteOutput($"Robot busy?: {is_robot_busy}");
                    string jsonString = $"{{ \"robot_busy\": {is_robot_busy} }}";
                    byte[] jsonBytes = Encoding.UTF8.GetBytes(jsonString);

                    return new Response()
                    {
                        StatusCode = HttpStatusCode.OK,
                        ContentType = "application/json",
                        ReasonPhrase = "POST requests are not supported by this endpoint, use a GET request instead.",
                        Headers = new Dictionary<string, string>()
                        {
                            {
                                "Content-Type", "application/json"
                            }
                        },
                        Contents = c => c.Write(jsonBytes, 0, jsonBytes.Length)
                    };
                };

                Get["/api/system/robot/joints"] = _ =>
                {
                    _GET_REQUESTS += 1;
                    UpdateStatusBar();

                    GetRobotJoints();
                    string joint_string = String.Join(",", _ROBOT_JOINTS.Select(p => p.ToString()).ToArray());
                    //WriteOutput($"Current joint positions: {joint_string}");
                    string jsonString = $"{{ \"robot_joints\": [{joint_string}] }}";

                    byte[] jsonBytes = Encoding.UTF8.GetBytes(jsonString);

                    return new Response()
                    {
                        StatusCode = HttpStatusCode.OK,
                        ContentType = "application/json",
                        ReasonPhrase = "POST requests are not supported by this endpoint, use a GET request instead.",
                        Headers = new Dictionary<string, string>()
                        {
                            {
                                "Content-Type", "application/json"
                            }
                        },
                        Contents = c => c.Write(jsonBytes, 0, jsonBytes.Length)
                    };
                };

                Post[@"/api/system/.*"] = _ =>
                {
                    _POST_REQUESTS += 1;
                    UpdateStatusBar();

                    WriteOutput($"POST requests not supported by /api/info/\n");
                    return new Response()
                    {
                        StatusCode = HttpStatusCode.BadRequest,
                        ContentType = "application/json",
                        ReasonPhrase = "POST requests are not supported by this endpoint, use a GET request instead.",
                        Headers = new Dictionary<string, string>()
                        {
                            {
                                "Content-Type", "application/json"
                            }
                        },
                    };
                };
            }
        }

        /// <summary>Class to handle Camera API calls</summary>
        /// <author>Damian Jimenez</author>
        public class CameraAPI : NancyModule
        {
            /// <summary>API endpoint for the Camera commands</summary>
            /// <author>Damian Jimenez</author>
            /// <returns><c>void</c></returns>
            public CameraAPI()
            {
                Get["/api/camera/get/alldata"] = _ =>
                {
                    _GET_REQUESTS += 1;
                    UpdateStatusBar();

                    return "Hello world.";
                };

                Post[@"/api/camera/.*"] = _ =>
                {
                    _POST_REQUESTS += 1;
                    UpdateStatusBar();

                    WriteOutput($"POST requests not supported by /api/move/cartesian\n");
                    return new Response()
                    {
                        StatusCode = HttpStatusCode.BadRequest,
                        ContentType = "application/json",
                        ReasonPhrase = "POST requests are not supported by this endpoint, use a GET request instead.",
                        Headers = new Dictionary<string, string>()
                        {
                            {
                                "Content-Type", "application/json"
                            }
                        },
                    };
                };
            }
        }

        /// <summary>Class to handle CartesianMove API calls</summary>
        /// <author>Damian Jimenez</author>
        public class CartesianMoveAPI : NancyModule
        {
            /// <summary>API endpoint for the CartesianMove command</summary>
            /// <author>Damian Jimenez</author>
            /// <returns><c>void</c></returns>
            public CartesianMoveAPI()
            {
                Get["/api/move/cartesian"] = _ =>
                {
                    _GET_REQUESTS += 1;
                    UpdateStatusBar();

                    WriteOutput($"GET requests not supported by /api/move/cartesian\n");
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
                    _POST_REQUESTS += 1;

                    try
                    {
                        _CARTESIAN_MOVES += 1;
                        UpdateStatusBar();

                        var id = Request.Body;
                        var length = Request.Body.Length;
                        var data = new byte[length];

                        id.Read(data, 0, (int)length);
                        var body = Encoding.Default.GetString(data);
                        var command = JsonConvert.DeserializeObject<CartesianMoveCommand>(body);

                        WriteOutput($"Received the following POST request:\n{body.ToString()}\n");

                        Thread command_thread = new Thread(() => command.Execute(adept_ace.AceRobot, adept_ace.AceServer.CreateObject(typeof(CartesianMove)) as CartesianMove));
                        command_thread.Start();

                        return HttpStatusCode.OK;
                    }
                    catch (Exception e)
                    {
                        UpdateStatusBar();

                        WriteOutput($"POST request failed.\nERROR:\n{e.Message}\n");
                        string jsonString = $"{{ \"status\": \"failure\", \"error\": \"{e.Message}\" }}";
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
            /// <summary>Specifies the S-curve trajectory profile, from 0 (for trapezoidal) to 8, or -1 to leave unchanged. An S-curve can smooth the trajectory into an "S" shape by limiting the rate of change of acceleration. Robots with flexible links or drive trains can benefit from S-curves to reduce oscillation.</summary>
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
                if (app_config.ThreadingEnabled)
                {
                    _SEMAPHORE.WaitOne();
                }
                /*################################################################################
                ########################## BEGINNING OF PROTECTED BLOCK ##########################
                ################################################################################*/
                { 
                    _ROBOT_BUSY = true;
                    _CURRENT_MOVE_CMDS += 1;
                    try
                    {
                        // Get the current joint positions of the robot
                        double[] jointPositions = robot.JointPosition;

                        // Print out joint information for the user to see
                        WriteOutput("Current joint values:");
                        foreach (var joint in jointPositions.Select((value, i) => new { i, value }))
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

                        // Check if the current location is in-range           
                        Transform3D currentPosition = robot.WorldLocationWithTool;
                        bool inRange = robot.InRange(currentPosition) == 0 ? true: false;
                        WriteOutput($"[{currentPosition}]\nMotion in range: {inRange}\n");

                        // Get the current robot configuration
                        IMoveConfiguration moveConfig = robot.GetMoveConfiguration(jointPositions);

                        // Create a new Transform3D object specifying how the robot should move
                        cartesianMove.MoveConfiguration = moveConfig;
                        Transform3D transform = new Transform3D(X, Y, Z, Yaw, Pitch, Roll);

                        // Calculate the new position of the robot based on the transform and the robots current position
                        cartesianMove.WorldLocation = currentPosition * transform;

                        // Write out the CartesianMove that is to be executed to the console and GUI
                        WriteOutput(cartesianMove.Description);

                        // Issue the move and wait until it is done
                        robot.Move(cartesianMove);
                        robot.WaitMoveDone();

                        // Force the robot to issue a DETACH
                        robot.AutomaticControlActive = false;
                    }
                    catch(Exception e)
                    {
                        WriteOutput($"Unable to move the robot.\nERROR: {e.Message}\n");
                    }
                    _CURRENT_MOVE_CMDS -= 1;
                    _ROBOT_BUSY = (_CURRENT_MOVE_CMDS == 0 ? false : true);
                }
                /*################################################################################
                ############################# END OF PROTECTED BLOCK #############################
                ################################################################################*/
                if (app_config.ThreadingEnabled)
                {
                    _SEMAPHORE.Release();
                }
            }
        }

        /// <summary>Class to handle JointMove API calls</summary>
        /// <author>Damian Jimenez</author>
        public class JointMoveAPI : NancyModule
        {
            /// <summary>API endpoint for the JointMove command</summary>
            /// <author>Damian Jimenez</author>
            /// <returns><c>void</c></returns>
            public JointMoveAPI()
            {
                Get["/api/move/joints"] = _ =>
                {
                    _GET_REQUESTS += 1;
                    UpdateStatusBar();

                    WriteOutput($"GET requests not supported by /api/move/joints\n");
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

                Post["/api/move/joints"] = _ =>
                {
                    _POST_REQUESTS += 1;

                    try
                    {
                        _JOINT_MOVES += 1;
                        UpdateStatusBar();

                        var id = Request.Body;
                        var length = Request.Body.Length;
                        var data = new byte[length];

                        id.Read(data, 0, (int)length);
                        var body = Encoding.Default.GetString(data);
                        var command = JsonConvert.DeserializeObject<JointMoveCommand>(body);

                        WriteOutput($"Received the following POST request:\n{body.ToString()}\n");
                        Thread command_thread = new Thread(() => command.Execute(adept_ace.AceRobot, adept_ace.AceServer.CreateObject(typeof(JointMove)) as JointMove));
                        command_thread.Start();

                        return HttpStatusCode.OK;
                    }
                    catch (Exception e)
                    {
                        UpdateStatusBar();

                        WriteOutput($"POST request failed.\nERROR:\n{e.Message}\n");
                        string jsonString = $"{{ \"status\": \"failure\", \"error\": \"{e.Message}\" }}";
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

        /// <summary>Class to handle setting up and executing a JointMove from Ace.Adept.Server.Motion</summary>
        /// <author>Damian Jimenez</author>
        public class JointMoveCommand
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
            public string Name = "Joint Move";
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
            /// <summary>Specifies the S-curve trajectory profile, from 0 (for trapezoidal) to 8, or -1 to leave unchanged. An S-curve can smooth the trajectory into an "S" shape by limiting the rate of change of acceleration. Robots with flexible links or drive trains can benefit from S-curves to reduce oscillation.</summary>
            public int SCurveProfile { get; set; }
            /// <summary>Specifies the joint positions of the move that is to be executed.</summary>
            public Double[] JointPosition { get; set; }

            /// <summary>Method that executes a command for an instance of the JointMoveCommand class</summary>
            /// <author>Damian Jimenez</author>
            /// <param name="robot">The robot that is to be controlled via the API call</param>
            /// <param name="jointMove"><c>JointMove</c> object to handle calculating the motion of the joints of the robot</param>
            /// <returns><c>void</c></returns>
            public void Execute(IAdeptRobot robot, JointMove jointMove)
            {
                if (app_config.ThreadingEnabled)
                {
                    _SEMAPHORE.WaitOne();
                }
                /*################################################################################
                ########################## BEGINNING OF PROTECTED BLOCK ##########################
                ################################################################################*/
                {
                    _ROBOT_BUSY = true;
                    _CURRENT_MOVE_CMDS += 1;
                    try
                    {
                        jointMove.Initialize();
                        // Get the current joint positions of the robot
                        double[] jointPositions = robot.JointPosition;

                        // Print out joint information for the user to see
                        WriteOutput("Current joint values:");
                        foreach (var joint in jointPositions.Select((value, i) => new { i, value }))
                        {
                            WriteOutput($"joint[{joint.i}] = {joint.value}");
                        }

                        // Assign jointMove the parameters that were passed via the API call
                        jointMove.Param.Accel = Accel;
                        jointMove.Param.Decel = Decel;
                        jointMove.Param.Speed = Speed;
                        jointMove.Param.Straight = StraightMotion;
                        jointMove.Param.MotionEnd = MOTION_END[MotionEnd];
                        jointMove.Param.SCurveProfile = SCurveProfile;
                        jointMove.JointPosition = JointPosition;

                        // Assigning the robot that was passed as the one that will execute the move
                        jointMove.Robot = robot;

                        // Write out the JointMove that is to be executed to the console and GUI
                        WriteOutput(jointMove.Description);

                        // Execute the move
                        robot.Move(jointMove);

                        // Wait for the robot to finish moving
                        robot.WaitMoveDone();

                        // Force the robot to issue a DETACH
                        robot.AutomaticControlActive = false;
                    }
                    catch(Exception e)
                    {
                        WriteOutput($"Unable to move the robot.\nERROR: {e.Message}\n");
                    }
                _CURRENT_MOVE_CMDS -= 1;
                _ROBOT_BUSY = (_CURRENT_MOVE_CMDS == 0 ? false : true);
                }
                /*################################################################################
                ############################# END OF PROTECTED BLOCK #############################
                ################################################################################*/
                if (app_config.ThreadingEnabled)
                {
                    _SEMAPHORE.Release();
                }
            }
        }
    }
}
