#if defined(WIN32)
#include <vld/vld.h>
#endif
#include <iostream>


//----------------------------------------------------
// -. vld configuration file (vld.ini)�� executable file�� ������ directory�� �����Ͽ��� ��.
//	  �������� �ʴ� ��� �⺻ ������ �����.
// -. ������ ���� ����Ǵ� ��쿡 ����� ������.
// -. ����� ��� �� �����ϴ� memory leakage���� detection.
// -. vld.h�� library or executable project�� �ϳ��� file������ include �Ǹ� ��. (?)
// -. �������� ������ ���ؼ� vld_x86.dll & dbghelp.dll �ʿ�.


namespace {
namespace local {

}  // namespace local
}  // unnamed namespace

namespace my_vld {

void basic(const bool leakage);
void boost_thread(const bool leakage);

}  // namespace my_vld

int vld_main(int argc, char *argv[])
{
	const bool leakage = true;

	my_vld::basic(leakage);
	my_vld::boost_thread(leakage);

    return 0;
}
