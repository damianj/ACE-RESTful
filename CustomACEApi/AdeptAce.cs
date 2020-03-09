using System;
using Ace.Adept.Server.Controls;
using Ace.Adept.Server.Motion;
using Ace.Core.Server;
using Ace.Core.Util;
using System.Collections.ObjectModel;

namespace CustomACEAPI
{
    /// <summary>Class that wraps the Custom ACE API server and all of its associated classes and methods</summary>
    /// <author>Damian Jimenez</author>
    public class AdeptAce
    {
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
        /// <param name="remotingHost">URL on which the Adept ACE server is hosted on.</param>
        /// <param name="remotingPort">Port on which the Adept ACE server is listening on.</param>
        /// <param name="remotingName">Name of the Adept ACE server (typically just "ace").</param>
        /// <param name="callbackPort">Callback port for the Adept ACE server.</param>
        /// <returns><c>ObservableCollection&lt;string&gt;[]</c> an array of length 2 containing the controllers and robots that were found. Index 0 is the controllers and index 1 is the robots.</returns>
        public ObservableCollection<string>[] ConnectToServer(string remotingHost, int remotingPort, string remotingName, int callbackPort)
        {
            // Only connect to the server once, at the beginning
            if(!ACE_SERVER_ON)
            {
                try
                {
                    bool noMatches = true;
                    // Set up the server to allow remote connections and connect to the ACE server
                    RemotingUtil.InitializeRemotingSubsystem(true, callbackPort);
                    ace = (IAceServer)RemotingUtil.GetRemoteServerObject(typeof(IAceServer), remotingName, remotingHost, remotingPort);

                    // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
                    Console.WriteLine($"Connected to the Adept ACE server ({remotingName}) successfully on:\n\t{remotingHost}:{remotingPort}\n");

                    // Print out all the controllers that are found and available
                    Console.Write($"Controllers found:");
                    foreach (IAdeptController controller in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptController)), true))
                    {
                        // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
                        Console.WriteLine($"\n\t{controller.FullPath}");
                        controllers.Add(controller.FullPath);
                        noMatches = false;
                    }
                    if (noMatches)
                    {
                        Console.WriteLine($"\n\tNone");
                    }
                    Console.Write($"\n");

                    // Print out all the robots that are found connected to the workspace and available
                    Console.Write($"Robots found:");
                    foreach (IAdeptRobot robot in ace.Root.Filter(new ObjectTypeFilter(typeof(IAdeptRobot)), true))
                    {
                        // We don't use WriteOutput, because that method definition isn't available to this class and it isn't required for things to work.
                        Console.WriteLine($"\n\t{robot.FullPath}");
                        robots.Add(robot.FullPath);
                        noMatches = false;
                    }
                    if (noMatches)
                    {
                        Console.WriteLine($"\n\tNone");
                    }
                    Console.Write($"\n");

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
                Console.WriteLine("\nERROR: A valid controller and/or robot path was not selected. Please select them from the dropdown menus and try again.\n");
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
                        Console.WriteLine("\nERROR: The specified robot was not found, please make sure the spelling is correct and that it exists.\n");
                    }
                }
                // Else the controller wasn't found and the user should know that there is an issue
                else
                {
                    Console.WriteLine("\nERROR: The specified controller was not found, please make sure the spelling is correct and that it exists.\n");
                }
            }
        }


        /// <summary>Method that get's the current robot's joint positions at the time of the method call.</summary>
        /// <author>Damian Jimenez</author>
        /// <returns><c>double[]</c> An array containing the current joint positions of the robot.</returns>
        public double[] GetJointPositions()
        {
            try
            {
                return robot.JointPosition;
            }
            catch(Exception e)
            {
                Console.WriteLine($"ERROR: Unable to get the robot's joint position.\n{e.Message}\n");
                return null;
            }
            
        }
    }
}
