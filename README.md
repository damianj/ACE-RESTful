# [Adept ACE Custom API]

This is a C# RESTful API for the Adept ACE environment. This API was developed specifically to control a ViperS650 robot, but could be easily extended to control other robots.

  - Install a licensed version of Adept ACE 3.7 and start up Adept ACE
  - Connect to the robot within Adept ACE and make sure the robot is powered on
  - Build the project in Visual Studio and run the application
  - The application gui will pop-up and once you click 'START' it will start listening on `localhost:9001`
  - See the usage documentation for available API endpoints and how to use them
  - Aside from being well-commented there is an HTML documentation for the code (more technical than the usage documentation) accessible by navigating to the 'Help' folder of this repo and opening 'index.html' in your browser of choice.

### Testing

You can quickly test out API endpoints via the PowerShell by starting up Adept ACE, connecting to the robot, and starting the application and clicking 'START'. After these steps you can use the PowerShell command below as a template to test out your API endpoints.

```powershell
PS > Invoke-WebRequest -UseBasicParsing http://localhost:9001/api/move/cartesian -ContentType "application/json" -Method POST -Body "{ 'Accel': 100, 'Decel': 100, 'Speed': 10, 'StraightMotion': true, 'MotionEnd': 'Blend', 'SCurveProfile': 0, 'X': 10, 'Y': 10, 'Z': 0, 'Yaw': 0, 'Pitch': 0, 'Roll': 0}"
```

### Resources

* [Nancy] - Light-weight web framework for C#
* [Newtonsoft] - Popular high-performance JSON framework for .NET
* [Volkanpaksoy] - Tutorial to get started developing with Nancy

### Continuing Development
You will need to install some packages via the Package Manager Console in Visual Studio

```powershell
PM> Install-Package Newtonsoft.Json

PM> Install-Package Nancy

PM> Install-Package Nancy.Hosting.Self
```

Alternatively, you can enable the Package Restore function of NuGet within Visual Studio, and clean and build the project which should install the necessary packages automatically.

---
[![N|Solid](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f8/License_icon-mit-88x31-2.svg/2000px-License_icon-mit-88x31-2.svg.png)](https://opensource.org/licenses/MIT)
###### [Wikimedia] - MIT licenese image

[//]: # (Reference Links - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [Adept ACE Custom API]: <https://damianj.github.io/MARSLab_ACEAPI/>
   [Volkanpaksoy]: <http://volkanpaksoy.com/archive/2015/11/11/building-a-simple-http-server-with-nancy/>
   [Nancy]: <http://nancyfx.org/>
   [Newtonsoft]: <http://www.newtonsoft.com/json>
   [Wikimedia]: <https://upload.wikimedia.org/>
