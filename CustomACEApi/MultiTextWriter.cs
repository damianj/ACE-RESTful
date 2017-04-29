using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace CustomACEAPI
{
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
}
