//#include "stdafx.h"
#if defined(_WIN64) || defined(WIN64) || defined(_WIN32) || defined(WIN32)
#include <vld/vld.h>
#endif
#include <iostream>
#include <stdexcept>
#include <cstdlib>


int main(int argc, char *argv[])
{
	int bayespp_main(int argc, char *argv[]);
	int particleplusplus_main(int argc, char *argv[]);
	int condensation_main(int argc, char *argv[]);

	int retval = EXIT_SUCCESS;
	try
	{
		std::cout << "Bayes++ library ----------------------------------------------------" << std::endl;
		//	- Kalman filter (KF).
		//	- Extended Kalman filter (EKF).
		//	- Unscented Kalman filter (UKF).
		//	- Covariance intersection filter.
		//	- U*d*U' factorisation of covariance filter.
        //      A 'Square-root' linearised Kalman filter.
		//	- Covariance filter.
		//	- Information filter.
		//	- Information root filter.
		//	- Iterated covariance filter.
		//	- Sampling importance resampling (SIR) filter.
		//      Particle filter.
		//  - Simultaneous localization and mapping (SLAM).
		retval = bayespp_main(argc, argv);

		std::cout << "\nParticle++ library -------------------------------------------------" << std::endl;
		//	- Particle filter.
		//	- Sequential Monte Carlo (SMC) method.
		//retval = particleplusplus_main(argc, argv);

		std::cout << "\nCONDENATION (CONditional DENsity propagATION) algorithm -----------" << std::endl;
		//retval = condensation_main(argc, argv);
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
