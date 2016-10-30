#if defined(WIN32) || defined(_WIN32)
#include <vld/vld.h>
#endif
#include <iostream>
#include <stdexcept>
#include <cstdlib>


int main(int argc, char *argv[])
{
	int cppunit_main(int argc, char *argv[]);
	int gtest_main(int argc, char *argv[]);
	int gmock_main(int argc, char *argv[]);

	int retval = EXIT_SUCCESS;
	try
	{
		std::cout << "Boost Test library --------------------------------------------------" << std::endl;
		// REF [library] >> Boost library.

		std::cout << "\nCppUnit library -----------------------------------------------------" << std::endl;
		// REF [project] >> ${SWDT_C++_HOME}/ext/test/testing/cppunit_mfc
		//retval = cppunit_main(argc, argv);

		std::cout << "\nGoogle Test library -------------------------------------------------" << std::endl;
		//retval = gtest_main(argc, argv);

		std::cout << "\nGoogle Mock library -------------------------------------------------" << std::endl;
		retval = gmock_main(argc, argv);
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
		std::cout << "Unknown exception caught" << std::endl;
		retval = EXIT_FAILURE;
	}

	std::cout << "Press any key to exit ..." << std::endl;
	std::cin.get();

	return retval;
}
