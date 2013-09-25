//#include "stdafx.h"
#if defined(WIN32)
#include <vld/vld.h>
#endif
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>


int main(int argc, char *argv[])
{
	int mrpt_main(int argc, char *argv[]);
	int player_stage_main(int argc, char *argv[]);

	int ompl_main(int argc, char *argv[]);

	int retval = EXIT_SUCCESS;
	try
	{
		std::srand((unsigned int)std::time(NULL));

		std::cout << "Mobile Robot Programming Toolkit (MRPT) library ---------------------" << std::endl;
		//retval = mrpt_main(argc, argv);  // compile-time error.
		std::cout << "\nPlayer/Stage library ------------------------------------------------" << std::endl;
		//retval = player_stage_main(argc, argv);

		std::cout << "\nOpen Motion Planning Library (OMPL) ---------------------------------" << std::endl;
		retval = ompl_main(argc, argv);  // not yet implemented.
	}
    catch (const std::bad_alloc &e)
	{
		std::cout << "std::bad_alloc caught: " << e.what() << std::endl;
		retval = EXIT_FAILURE;
	}
	catch (const std::exception &e)
	{
		std::cout << "std::exception caught: " << e.what() << std::endl;
		retval = EXIT_FAILURE;
	}
	catch (...)
	{
		std::cout << "unknown exception caught" << std::endl;
		retval = EXIT_FAILURE;
	}

	std::cout << "press any key to exit ..." << std::endl;
	std::cin.get();

	return retval;
}
