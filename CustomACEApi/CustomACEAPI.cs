using System;
using Ace.Adept.Server.Controls;
using Ace.Adept.Server.Motion;
using Ace.Core.Server;
using Ace.Core.Server.Motion;
using Ace.Core.Util;
using Nancy;
using Nancy.Hosting.Self;
using Newtonsoft.Json;
using System.Collections.Generic;
using System.Text;

namespace CustomACEAPI
{
    public class APIServer
    {
        private const string _url = "http://localhost";
        private const int _port = 12345;
        private static NancyHost _nancy;
        private const string RemotingName = "ace";
        private const int CallbackPort = 43431;
        private const int RemotingPort = 43434;
        private static IAceServer ace;

        public APIServer()
        {
            var configuration = new HostConfiguration()
            {
                UrlReservations = new UrlReservations() { CreateAutomatically = true }
            };

            _nancy = new NancyHost(configuration, new Uri($"{_url}:{_port}/"));
        }

        private void Start()
        {
            _nancy.Start();
            Console.WriteLine($"Started listennig on port {_port}");
            Console.ReadKey();
            _nancy.Stop();
        }

        public class CartesianMoveAPI : NancyModule
        {
            public CartesianMoveAPI()
            {
                Get["/CartesianMove"] = _ => 
                {
                    return new Response()
                    {
                        StatusCode = HttpStatusCode.BadRequest,
                        ContentType = "application/json",
                        ReasonPhrase = "GET requests not supported by this API endpoint. Please send a POST request with the appropriate payload.",
                        Headers = new Dictionary<string, string>()
                        {
                            { "Content-Type", "application/json" },
                            { "X-Custom-Header", "" }
                        },
                    };
                };

                Post["/CartesianMove"] = _ =>
                {
                    try
                    {
                        var id = this.Request.Body;
                        var length = this.Request.Body.Length;
                        var data = new byte[length];

                        id.Read(data, 0, (int)length);
                        var body = Encoding.Default.GetString(data);
                        var request = JsonConvert.DeserializeObject<CartesianMove>(body);

                        Console.WriteLine($"{request.Name}, {request.Accel}, {request.Decel}, {request.Speed}, {request.StraightMotion}, {request.MotionEnd}, {request.SCurveProfile}");

                        return 200;
                    }
                    catch(Exception e)
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
                                { "Content-Type", "application/json" },
                                { "X-Custom-Header", "Please check the error message below, and make sure the JSON payload is properly formatted." }
                            },
                            Contents = c => c.Write(jsonBytes, 0, jsonBytes.Length)
                        };
                    }
                };
            }
        }

        private class CartesianMove
        {
            public string Name = "Cartesian Move";
            public int Accel { get; set; }
            public int Decel { get; set; }
            public int Speed { get; set; }
            public Boolean StraightMotion { get; set; }
            public String MotionEnd { get; set; }
            public int SCurveProfile { get; set; }
        }

        static void Main(string[] args)
        {
            var api_server = new APIServer();
            api_server.Start();
            /*
            // Initialize remoting infrastructure
            RemotingUtil.InitializeRemotingSubsystem(true, CallbackPort);

            // Connect to ACE.
            ace = (IAceServer) RemotingUtil.GetRemoteServerObject(typeof(IAceServer), RemotingName, "localhost", RemotingPort);

            Console.WriteLine(ace.ToString());
            foreach(IAdeptController cntrlr in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptController)), true))
            {
                Console.WriteLine("Found controller '{0}'", cntrlr);
                cntrlr.HighPower = true;
                cntrlr.Calibrate();
            }

            IAdeptController controller = ace.Root["/SmartController 9/SmartController 9"] as IAdeptController;
            controller.Enabled = true;
            AdeptControllerUtil.AddAllRobots(ace, controller, ace.Root);

            IAdeptRobot robot = ace.Root["/SmartController 9/R1 Viper650"] as IAdeptRobot;

            // Read various properties of the robot
            Console.WriteLine("Number of joints = " + robot.JointCount);

            double[] jointPositions = robot.JointPosition;
            for (int i = 0; i < robot.JointCount; i++)
            {
                Console.WriteLine("Joint " + i + " " + jointPositions);
            }

            // Transform the current joint position to a world location
            try
            {
                Transform3D loc = robot.JointToWorld(jointPositions);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            // Check if the current location is inrange           
            Transform3D currentPosition = robot.WorldLocationWithTool;
            int inRange = robot.InRange(currentPosition);
            Console.WriteLine(currentPosition + " inrange check = " + inRange);

            // Get the current robot configuration
            IMoveConfiguration moveConfig = robot.GetMoveConfiguration(jointPositions);

            // Create a motion object and command the robot to move
            CartesianMove cartesianMove = ace.CreateObject(typeof(CartesianMove)) as CartesianMove;
            cartesianMove.MoveConfiguration = moveConfig;
            Transform3D t1 = new Transform3D(10, 10, 0);
            t1 = -t1;
            cartesianMove.WorldLocation = currentPosition * t1;

            try
            {

                // Issue the move and wait until it is done
                robot.Move(cartesianMove);
                robot.WaitMoveDone();

                // Force the robot to issue a DETACH
                robot.AutomaticControlActive = false;

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            */
        }
    }
}
