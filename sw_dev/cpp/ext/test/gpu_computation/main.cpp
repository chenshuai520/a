//#include "stdafx.h"
#if defined(WIN32)
#include <vld/vld.h>
#endif
#include <iostream>


int main(int argc, char *argv[])
{
	int cuda_main(int argc, char *argv[]);
	int thrust_main(int argc, char *argv[]);

	try
	{
		cuda_main(argc, argv);

		//thrust_main(argc, argv);  // not yet implemented
	}
	catch (const std::exception &e)
	{
		std::cout << "std::exception occurred !!!: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "unknown exception occurred !!!" << std::endl;
	}

	std::cout << "press any key to exit ..." << std::endl;
	std::cin.get();

    return 0;
}