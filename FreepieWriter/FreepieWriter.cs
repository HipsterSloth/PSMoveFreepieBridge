using System;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace FreepieWriter
{
    public class FreepieWriter
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct FreepieData
        {
            public float yaw;
            public float pitch;
            public float roll;

            public float x;
            public float y;
            public float z;
        }

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool SetDllDirectory(string lpPathName);

        [DllImport("freepie_io.dll")]
        private static extern int freepie_io_6dof_slots();

        [DllImport("freepie_io.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int freepie_io_6dof_write(int index, int length, FreepieData[] data);

        private static bool bInit = false;

        private static void init()
        {
            //Set freepie DLL path so we don't have to include it
            var path = Registry.GetValue(string.Format("{0}\\Software\\{1}", Registry.CurrentUser, "FreePIE"), "path", null) as string;
            SetDllDirectory(path);
            bInit = true;
        }

        public static void WriteData(FreepieData data, Int32 freepieIndex = 0)
        {
            if (!bInit)
            {
                init();
            }

            FreepieData[] toArray = new FreepieData[1];
            toArray[0] = data;
            int result = freepie_io_6dof_write(freepieIndex, 1, toArray);

            if (result != 0)
            {
                throw new Exception("FreepieWriter - Could not write pose to freepie index " + freepieIndex + ", Freepie result " + result);
            }
        }
    }
}
