#include <vld/vld.h>
#include <iostream>


//----------------------------------------------------
// -. vld configuration file (vld.ini)�� executable file�� ������ directory�� �����Ͽ��� ��.
//	  �������� �ʴ� ��� �⺻ ������ �����.
// -. ������ ���� ����Ǵ� ��쿡 ����� ������.
// -. ����� ��� �� �����ϴ� memory leakage���� detection.
// -. vld.h�� library or executable project�� �ϳ��� file������ include �Ǹ� ��. (?)
// -. �������� ������ ���ؼ� vld_x86.dll & dbghelp.dll �ʿ�.


#if defined(_UNICODE) || defined(UNICODE)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	void basic(const bool leakage);
	void boost_thread(const bool leakage);

	try
	{
		const bool leakage = true;

		basic(leakage);
		boost_thread(leakage);
	}
	catch (const std::exception &e)
	{
		std::cout << "std::exception occurred: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "unknown exception occurred" << std::endl;
	}

	std::cout << "press any key to exit ..." << std::flush;
	std::cin.get();

    return 0;
}
