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
using System.Collections.ObjectModel;

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
        private static HostConfiguration configuration;
        private static ObservableCollection<string> controllers;
        private static ObservableCollection<string> robots;

        /// <summary>Initiates the GUI and preps everything needed to successfully start the NancyFX server and connect to the Adept ACE server </summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>void</c></returns>
        public MainWindow()
        {
            gui_dispatcher = Dispatcher;
            InitializeComponent();
            OutputText.Text = "";
            adept_ace = new AdeptAce();
            Console.SetOut(new MultiTextWriter(new TextBoxWriter(OutputText), Console.Out));

            // Create a URL reservation to allow the NancyFX server to start (i.e., prevent AutomaticUrlReservationCreationFailureException)
            configuration = new HostConfiguration()
            {
                UrlReservations = new UrlReservations()
                {
                    CreateAutomatically = true
                }
            };

            _nancy = new NancyHost(configuration, new Uri($"{_url}:{_port}/"));
            WriteOutput("Application started successfully...\n-----------------------------------");
        }

        /// <summary>Starts the NancyFX server to allow it to start listening for requests on localhost:9001</summary>
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
                    ObservableCollection<string>[] controllers_and_robots;

                    controllers_and_robots = adept_ace.ConnectToServer("localhost", 43434);
                    controllers = controllers_and_robots[0];
                    robots = controllers_and_robots[1];

                    ControllerPathComboBox.ItemsSource = controllers;
                    RobotPathComboBox.ItemsSource = robots;
                }

                // Start the HTTP server on localhost:9001
                _nancy.Start();
                WriteOutput("Successfully started the HTTP server.\n------------------------------------\n");
                WriteOutput($"Listening on: {_url}:{_port}/\n");
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
            // Stop the HTTP Server
            _nancy.Stop();
            WriteOutput("Successfully stopped the HTTP server.\n------------------------------------\n");
        }

        /// <summary>Load the controller and robot currently selected in the combo-boxes</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="sender">Object that triggered the call to this method</param>
        /// <param name="e">Event information of the routed event</param>
        /// <returns><c>void</c></returns>
        void Load_ControllerAndRobot(object sender, RoutedEventArgs e)
        {
            adept_ace.LoadControllerAndRobot(ControllerPathComboBox.Text, RobotPathComboBox.Text);
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
                    return "Hello world.";
                };

                Post[@"/api/camera/.*"] = _ =>
                {
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
                    try
                    {
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
                        WriteOutput($"POST request failed.\nERROR:\n{e.Message}\n");
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
                _SEMAPHORE.WaitOne();
                /*################################################################################
                ########################## BEGINNING OF PROTECTED BLOCK ##########################
                ################################################################################*/
                {
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

                        // Check if the current location is inrange           
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
                }
                /*################################################################################
                ############################# END OF PROTECTED BLOCK #############################
                ################################################################################*/
                _SEMAPHORE.Release();
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
                    try
                    {
                        var id = Request.Body;
                        var length = Request.Body.Length;
                        var data = new byte[length];

                        id.Read(data, 0, (int)length);
                        var body = Encoding.Default.GetString(data);
                        var command = JsonConvert.DeserializeObject<JointMoveCommand>(body);

                        WriteOutput($"Received the following POST request:\n{body.ToString()}\n");
                        command.Execute(adept_ace.AceRobot, adept_ace.AceServer.CreateObject(typeof(JointMove)) as JointMove);

                        return HttpStatusCode.OK;
                    }
                    catch (Exception e)
                    {
                        WriteOutput($"POST request failed.\nERROR:\n{e.Message}\n");
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
                _SEMAPHORE.WaitOne();
                /*################################################################################
                ########################## BEGINNING OF PROTECTED BLOCK ##########################
                ################################################################################*/
                {
                    if (JointPosition.Length != 6)
                    {
                        WriteOutput($"Invalid number of joints specified in the joint position array. The array should specify 6 floating point values.\nCurrently it is: {JointPosition.ToString()}\n");
                    }
                    else
                    {
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
                            jointMove.Go();

                            // Wait for the robot to finish moving
                            robot.WaitMoveDone();

                            // Force the robot to issue a DETACH
                            robot.AutomaticControlActive = false;
                        }
                        catch(Exception e)
                        {
                            WriteOutput($"Unable to move the robot.\nERROR: {e.Message}\n");
                        }
                    }
                }
                /*################################################################################
                ############################# END OF PROTECTED BLOCK #############################
                ################################################################################*/
                _SEMAPHORE.Release();
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
        private const int CALLBACK_PORT = 43431;

        private static bool ACE_SERVER_ON = false;
        private static IAceServer ace;
        private static IAdeptRobot robot = null;
        private static IAdeptController controller = null;
        private static ObservableCollection<string> controllers = new ObservableCollection<string>();
        private static ObservableCollection<string> robots = new ObservableCollection<string>();

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

        /// <summary>Method that connects to the Adept ACE server and gets all the available controllers and robots</summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>ObservableCollection&lt;string&gt;[]</c> an array of length 2 containing the controllers and robots that were found. Index 0 is the controllers and index 1 is the robots.</returns>
        public ObservableCollection<string>[] ConnectToServer(String remoting_host, int remoting_port)
        {
            // Only connect to the server once, at the beginning
            if(!ACE_SERVER_ON)
            {
                try
                {
                    // Set up the server to allow remote connections and connect to the ACE server
                    RemotingUtil.InitializeRemotingSubsystem(true, CALLBACK_PORT);
                    ace = (IAceServer)RemotingUtil.GetRemoteServerObject(typeof(IAceServer), REMOTING_NAME, remoting_host, remoting_port);

                    // Print out all the controllers that are found and available
                    foreach (IAdeptController controller in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptController)), true))
                    {
                        // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
                        Console.WriteLine($"Found controller: {controller.FullPath}");
                        controllers.Add(controller.FullPath);
                    }

                    // Print out all the robots that are found connected to the workspace and available
                    foreach (IAdeptRobot robot in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptRobot)), true))
                    {
                        // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
                        Console.WriteLine($"Found robot: {robot.FullPath}");
                        robots.Add(robot.FullPath);
                    }

                    // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
                    Console.WriteLine($"Connected to the Adept ACE server successfully on: {remoting_host}:{remoting_port}/\n");
                    ACE_SERVER_ON = true;
                }
                catch(Exception e)
                {
                    Console.WriteLine($"Unable to connect to the Adept ACE server properly.\nERROR: {e.Message}\n");
                }
            }

            ObservableCollection<string>[] res = {controllers, robots};
            return res;
        }

        /// <summary>Method that loads the controller and robot specified in the GUI combo-boxes</summary>
        /// <author>Damian Jimenez</author>
        /// <param name="controllerPath">Specifies where the server should search for the controller, can be found by opening up a default workspace in Adept ACE and connecting to a desired robot.</param>
        /// <param name="robotPath">Specifies where the server should search for the robot, can be found by opening up a default workspace in Adept ACE and connecting to a desired robot.</param>
        /// <returns><c>void</c></returns>
        public void LoadControllerAndRobot(String controllerPath, String robotPath)
        {
            // Trim any leading and trailing white-space from the input
            controllerPath = controllerPath.Trim();
            robotPath = robotPath.Trim();

            // If either paths are empty, then let the user know
            if(controllerPath == "" || robotPath == "")
            {
                Console.WriteLine("/nERROR: Unable to find a valid controller path and/or robot path to load.\n");
            }
            else
            {
                // If this is not the first time loading a controller, disable the current controller
                if(controller != null)
                {
                    controller.HighPower = false;
                    controller.Enabled = false;
                    controller = null;
                }

                // Load the new controller
                controller = ace.Root[controllerPath] as IAdeptController;

                // If the new controller was successfully loaded do the following
                if(controller != null)
                {
                    // Enable and calibrate the controller
                    controller.Enabled = true;
                    controller.HighPower = true;
                    controller.Calibrate();
                    if (!controller.IsEVPlus)
                    {
                        controller.DryRun = true;
                        controller.DryRun = false;
                    }
                    // Add all available robots to the controller
                    AdeptControllerUtil.AddAllRobots(ace, controller, ace.Root);

                    // Reset the current robot to null
                    robot = null;
                    // Assign the new robot as our current robot
                    robot = ace.Root[robotPath] as IAdeptRobot;

                    // If we loaded the robot successfully then let the user know
                    if(robot != null)
                    {
                        Console.WriteLine($"Successfully loaded:\n\tController: {controllerPath}\n\tRobot: {robotPath}\n");
                    }
                    // Else the robot wasn't found and the user should know that there is an issue
                    else
                    {
                        Console.WriteLine("/nERROR: The specified robot was not found, please make sure the spelling is correct and that it exists.\n");
                    }
                }
                // Else the controller wasn't found and the user should know that there is an issue
                else
                {
                    Console.WriteLine("/nERROR: The specified controller was not found, please make sure the spelling is correct and that it exists.\n");
                }
            }
        }
    }
}
