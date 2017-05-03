using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Intel.RealSense;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Windows.Media.Imaging;


namespace CustomACEAPI
{
    class cameraInst
    {
        public Session session;
        public SenseManager sm;
        public SampleReader reader;
        public int height;
        public CoordinateSystem cs;
        public Projection projection;
        public Device device;
        public CaptureManager cm;

        public void start_camera(int h)
        {
            session = Session.CreateInstance();
            sm = SenseManager.CreateInstance();
            height = h;
            Console.WriteLine("SDK Version {0}.{1}", session.Version.major, session.Version.minor);
            cs = session.CoordinateSystem;


        }

        public void config_reader()
        {
            reader = SampleReader.Activate(sm);
            reader.EnableStream(StreamType.STREAM_TYPE_DEPTH, 628, 468, 30);

        }

        public void process_frame()
        {
            sm.Init();

            cm = sm.CaptureManager;
            cm.LocateStreams();
            device = cm.Device;

            if (device != null)
            {
                projection = device.CreateProjection();
            }
            else
            {
                Console.WriteLine("device is null... :(");
            }

            if (sm.AcquireFrame(true).IsError())
            {
                Console.WriteLine("Failed to Acquire Frame");
            }
            else
            {

                Sample sample = reader.Sample;
                ImageData data = new ImageData();
                short[] buffer = { };
                Console.WriteLine("test");
                ImageInfo dinfo;

                if (sample == null)
                {
                    Console.WriteLine("Sample Access Failed");
                }
                if (sample != null)
                {
                    if (Status.STATUS_NO_ERROR == sample.Depth.AcquireAccess(ImageAccess.ACCESS_READ, out data))
                    {
                        data.format = Intel.RealSense.PixelFormat.PIXEL_FORMAT_DEPTH;
                        buffer = data.ToShortArray(0, 628 * 468);


                        /*Bitmap bitmap = data.ToBitmap(0, sample.Depth.Info.width, sample.Depth.Info.height);
                        Console.WriteLine(bitmap.Palette);
                        bitmap.Save("c:\\Users\\Senior Design\\Documents\\test1.bmp", ImageFormat.Bmp);*/

                    }
                }

                dinfo = sample.Depth.Info;
                Point3DF32[] vertices = new Point3DF32[sample.Depth.Info.width * sample.Depth.Info.height];
                Point3DF32[] world = new Point3DF32[sample.Depth.Info.width * sample.Depth.Info.height];
                Console.WriteLine("run");
                projection.QueryVertices(sample.Depth, vertices);
                sample.Depth.ReleaseAccess(data);
                projection.ProjectDepthToCamera(vertices, world);

                int h = sample.Depth.Info.height;
                int w = sample.Depth.Info.width;
                var bitmap = new Bitmap(w, h);
                int bufPos = 0;
                float max = 0;
                int negCount = 0;
                int range = 5000;
                for (int y = 0; y < h; y++)
                {
                    for (int x = 0; x < w; x++)
                    {
                        float val = world[bufPos].z;
                        if (val > max)
                        {
                            max = val;
                        }
                        float color = 0;
                        if (val < 0)
                        {

                            negCount++;
                        }
                        if (val > range)
                        {

                            color = 255;
                        }
                        else if (val == 0)
                        {
                            color = 0;
                        }
                        else if (val < -range)
                        {
                            color = 0;
                        }
                        else
                        {
                            if (val < 0)
                            {
                                Console.WriteLine(val);
                            }

                            color = (Math.Abs((val / range) * 255));
                        }

                        //Console.WriteLine(world[bufPos].z);
                        bitmap.SetPixel(x, y, Color.FromArgb(0, (int)color, (int)color, (int)color));
                        bufPos++;
                    }
                }
                Console.WriteLine("Number of negtive values: {0}", negCount);
                bitmap.Save("test1.bmp", ImageFormat.Bmp);
                Console.WriteLine("Image Aquired");
            }
        }
        public void end_camera()
        {
            session.Dispose();
            sm.Dispose();
        }
    }
}
