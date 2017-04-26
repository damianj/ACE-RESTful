# Adept ACE Custom API - MARS Lab (UT Arlington)

This is a C# RESTful style API for the Adept ACE environment. This API was developed specifically to control a ViperS650 robot, but could be extended to control other robots easily.

  - Install a licensed version of Adept ACE 3.7 and start up Adept ACE
  - Connect to the robot within Adept ACE and make sure the robot is powered on
  - Build the project in Visual Studio and run the application
  - The application will start listening on localhost:12345
  - See the documentation for available API endpoints and how to use them

### Resources

* [Nancy] - Light-weight web framework for C#
* [Newtonsoft] - Popular high-performance JSON framework for .NET
* [Volkanpaksoy] - Tutorial to get started developing with Nancy

### Continuing Development
You will need to install some packages via the Package Manager Console in Visual Studio

  - `PM> Install-Package Newtonsoft.Json`
  - `PM> Install-Package Nancy`
  - `PM> Install-Package Nancy.Hosting.Self`

---
[![N|Solid](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f8/License_icon-mit-88x31-2.svg/2000px-License_icon-mit-88x31-2.svg.png)](https://opensource.org/licenses/MIT)
###### [Wikimedia] - MIT licenese image

[//]: # (Reference Links - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [Volkanpaksoy]: <http://volkanpaksoy.com/archive/2015/11/11/building-a-simple-http-server-with-nancy/>
   [Nancy]: <http://nancyfx.org/>
   [Newtonsoft]: <http://www.newtonsoft.com/json>
   [Wikimedia]: <https://upload.wikimedia.org/>
