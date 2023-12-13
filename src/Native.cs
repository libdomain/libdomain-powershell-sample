using System;
using System.Runtime.InteropServices;

namespace LibDomain
{
    public class Native
    {

        [DllImport("libdomain_wrapper.so")]
        public static extern int get_root_dse();
    }
}
