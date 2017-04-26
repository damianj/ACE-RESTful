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
using System.Threading;
using System.Threading.Tasks;

namespace CustomACEAPI
{
    public class APIServer
    {
        private static SemaphoreSlim _SEMAPHORE= new SemaphoreSlim(1, 1);
        private const string REMOTING_NAME = "ace";
        private const string REMOTING_HOST = "localhost";
        private const int CALLBACK_PORT = 43431;
        private const int REMOTING_PORT = 43434;

        private const string _url = "http://localhost";
        private const int _port = 12345;
        private static NancyHost _nancy;
        private static string _status = "Offline";
        private static IAceServer ace;
        private static IAdeptRobot robot;

        public APIServer()
        {
            var configuration = new HostConfiguration()
            {
                UrlReservations = new UrlReservations()
                {
                    CreateAutomatically = true
                }
            };

            _nancy = new NancyHost(configuration, new Uri($"{_url}:{_port}/"));
        }

        private void Start()
        {
            ConsoleKeyInfo cki;
            _nancy.Start();
            _status = $"Listennig on port {_port}";

            Console.WriteLine(_status);
            Console.WriteLine("Press ESC or Q/q to exit the application.");
            do
            {
                cki = Console.ReadKey();
            }
            while(cki.Key != ConsoleKey.Escape && cki.Key != ConsoleKey.Q);

            _nancy.Stop();
        }

        private class AdeptAce
        {
            public void ConnectToServer(String controllerPath="/SmartController 9/SmartController 9", String robotPath= "/SmartController 9/R1 Viper650")
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

                robot = ace.Root["/SmartController 9/R1 Viper650"] as IAdeptRobot;
            }
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
                        ReasonPhrase = "GET requests not supported, use a POST request instead.",
                        Headers = new Dictionary<string, string>()
                        {
                            {
                                "Content-Type", "application/json"
                            }
                        },
                    };
                };

                Post["/CartesianMove", runAsync: true] = async (_, token) =>
                {
                    await _SEMAPHORE.WaitAsync();
                    try
                    {
                        try
                        {
                            var id = this.Request.Body;
                            var length = this.Request.Body.Length;
                            var data = new byte[length];

                            id.Read(data, 0, (int)length);
                            var body = Encoding.Default.GetString(data);
                            var command = JsonConvert.DeserializeObject<CartesianMoveCommand>(body);

                            Console.WriteLine($"{command.Name}, {command.Accel}, {command.Decel}, {command.Speed}, {command.StraightMotion}, {command.MotionEnd}, {command.SCurveProfile}");

                            await Task.Run(() => { command.Execute(); });

                            return HttpStatusCode.OK;
                        }
                        catch(Exception e)
                        {
                            string jsonString = $"{{ status: \"failure\", error: \"{e.Message}\" }}";
                            byte[] jsonBytes = Encoding.UTF8.GetBytes(jsonString);

                            Console.WriteLine(e.Message);

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
                    }
                    finally
                    {
                        _SEMAPHORE.Release(1);
                    }
                };
            }
        }

        private class CartesianMoveCommand
        {
            public string Name = "Cartesian Move";
            public int Accel { get; set; }
            public int Decel { get; set; }
            public int Speed { get; set; }
            public bool StraightMotion { get; set; }
            public string MotionEnd { get; set; }
            public int SCurveProfile { get; set; }

            public void Execute()
            {
                Thread.Sleep(3000);
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

                // Issue the move and wait until it is done
                robot.Move(cartesianMove);
                robot.WaitMoveDone();

                // Force the robot to issue a DETACH
                robot.AutomaticControlActive = false;
            }
        }

        static void Main(string[] args)
        {
            var api_server = new APIServer();
            api_server.Start();
        }
    }
}
