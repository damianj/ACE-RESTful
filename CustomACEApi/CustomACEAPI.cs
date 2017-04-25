using System;
using Ace.Adept.Server.Controls;
using Ace.Adept.Server.Motion;
using Ace.Core.Server;
using Ace.Core.Server.Motion;
using Ace.Core.Util;
using Nancy;
using Nancy.Hosting.Self;


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

        public class CartesianMove : Nancy.NancyModule
        {
            public CartesianMove()
            {
                Get["/CartesianMove"] = _ => "Received GET request";

                Post["/"] = _ => "Received POST request";
            }
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
