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

namespace vld {

void basic(const bool leakage);
void boost_thread(const bool leakage);

}  // namespace vld

int vld_main(int argc, char *argv[])
{
	const bool leakage = true;

	vld::basic(leakage);
	vld::boost_thread(leakage);

    return 0;
}
