#include <smctc/smctc.hh>
#include <iostream>
#include <cstdio> 
#include <cstdlib>
#include <cmath>


namespace {
namespace local {

}  // namespace local
}  // unnamed namespace

namespace my_smctc {

void pf_example();
void rare_events_example();

}  // namespace my_smctc

int smctc_main(int argc, char *argv[])
{
	try
	{
		my_smctc::pf_example();  // run-time error.
		//my_smctc::rare_events_example();  // run-time error.
	}
	catch (const smc::exception &e)
	{
		std::cout << "smc::exception caught: " << e.szMessage << std::endl;
		return e.lCode;
	}

	return 0;
}