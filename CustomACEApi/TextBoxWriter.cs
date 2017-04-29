using System.Text;
using System.Windows.Controls;
using System.IO;

namespace CustomACEAPI
{
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
            textbox.AppendText($"{value}");
            textbox.ScrollToEnd();
        }

        /// <summary>Override of the <c>Write</c> method, writes to each <c>TextWriter</c> in the list of <c>TextWriter</c>s</summary>
        /// <param name="value"><c>string</c> to be written</param>
        /// <returns><c>void</c></returns>
        /// <author>Damian Jimenez</author>
        public override void Write(string value)
        {
            textbox.AppendText(value);
            textbox.ScrollToEnd();
        }

        /// <summary>Override of the <c>Encoding</c> method, returns the <c>Encoding</c> of the <c>TextBox</c></summary>
        /// <returns><c>Encoding.ASCII</c></returns>
        /// <author>Damian Jimenez</author>
        public override Encoding Encoding
        {
            get { return Encoding.ASCII; }
        }
    }
}
