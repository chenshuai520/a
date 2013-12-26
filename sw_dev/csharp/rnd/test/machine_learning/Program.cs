﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace machine_learning
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Console.WriteLine("numl library --------------------------------------------------------");
                numl.numl_Main.run(args);  // not yet implemented.
            }
            catch (Exception e)
            {
                Console.WriteLine("System.Exception occurred: {0}", e);
            }

            Console.WriteLine("press any key to exit ...");
            Console.ReadKey();
        }
    }
}
