## Usage Guide

##### General
- Site
	* [MinGW32](http://www.mingw.org/)
	* [MinGW64](http://mingw-w64.org/)

	+ http://sourceforge.net/projects/mingw/files/MinGW/Base/
	+ http://sourceforge.net/projects/mingw/files/MinGW/Extension/
		- mingw-utils
		- peexports
		- reimp
	+ http://sourceforge.net/projects/mingw/files/MinGW/Contributed/

	- http://sourceforge.net/projects/mingw/files/MSYS/Base/
	- http://sourceforge.net/projects/mingw/files/MSYS/Extension/
		- wget
	- http://sourceforge.net/projects/mingw/files/MSYS/Contributed/

- Document
	- http://www.mingw.org/wiki
	- http://www.mingw.org/wiki/HOWTO
	- http://www.mingw.org/wiki/FAQ

	- http://www.mingw.org/wiki/MSVC_and_MinGW_DLLs
	- http://www.mingw.org/wiki/Interoperability_of_Libraries_Created_by_Different_Compiler_Brands
	- http://www.mingw.org/wiki/JNI_MinGW_DLL

 - Usage
	- Reference
    	- ${GDT_HOME}/sw_dev/cpp/rnd/src/probabilistic_graphical_model/mocapy/mocapy_build_guide.txt

##### Console
- Use Windows Command Prompt or Visual Studio Command Prompt
	- MSYS console�� ����ϴ� �ͺ��� ����.
	- ����ϱ� ���� ${MINGW_ROOT}/bin & ${MSYS_ROOT}/bin�� path�� ù �׸����� �����Ͽ��� ��.

		`set path=${MINGW_ROOT}/bin;%path%` <br />
		`set path=${MINGW_ROOT}/bin;${MSYS_ROOT}/bin;%path%` <br />
		`set path=${MINGW_ROOT}/bin;${CYGWIN_HOME}/bin;%path%` <br />
		`set path=${MINGW_ROOT}/bin;${GNUWIN32_HOME}/bin;%path%`
- Use MSYS console
	- ����ϱ� ���� ${MINGW_ROOT}/bin�� path�� ù �׸����� �����Ͽ��� ��.
		- `export PATH=${MINGW_ROOT}/bin:$PATH`
			- e.g.) `export PATH=/d/MyProgramFiles2/MinGW/bin:$PATH`

##### Package Management
- �Ʒ��� executable file�� �̿��ؼ� package management�� ����
	- `${MINGW_ROOT}/bin/mingw-get.exe`
	- e.g.)

		`mingw-get install lib-package-name` <br />
		`mingw-get update`

- mingw-get.exe���� ��ġ���� �ʴ� package�� ��� �Ʒ��� ����Ʈ���� ã�� �� ����.
	- http://sourceforge.net/projects/mingw/files/MSYS/Extension/
	- http://sourceforge.net/projects/mingw/files/MSYS/Base/
	- download ���� file�� ${MSYS_HOME}�� ������ �� ������ Ǯ�� ${MSYS_HOME}/bin�� �����.

## Software Building

##### Software building�� ���ؼ� ����� compiler & linker, etc
- ${MINGW_ROOT}/bin ������ file�� ���
- "mingw32-"�� ���� executable file�� ���
	- e.g.)
		- mingw32-gcc.exe (X) ==> gcc.exe (O)
		- mingw32-g++.exe (X) ==> g++.exe (O)
	- ��, make�� ��� mingw32-make.exe�� ���
		- make.exe (X) ==> mingw32-make.exe (O)

##### Use CMake
- In Visual Studio Command Prompt or Windows Command Prompt
	- [ref] http://icl.cs.utk.edu/lapack-for-windows/lapack/
	1. set the GNU runtime directory in PATH.

		`set path=${MINGW_ROOT}/bin;%path%`
		`set path=${MINGW_ROOT}/bin;${CYGWIN_HOME}/bin;%path%`
	2. run cmake-gui.
	3. specify 'MinGW Makefiles' as the generator.
		-  sh.exe ���� ������ �߻��ϸ� 'Configure' �����.
			- <error message> sh.exe was found in your PATH
			- 4�� ����.
		- Fortran compiler ���� ������ �߻��ϸ�
			- <error message> The Fortran compiler "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/ifc.exe" is not able to compile a simple test program.
			- 4�� ����.
	4. set options.
		- set the 'CMAKE_SH' option to ${MSYS_ROOT}/bin/sh.exe
		- set the 'CMAKE_Fortran_COMPILER' option to ${MINGW_ROOT}/bin/gfortran.exe
		- set the 'BUILD_SHARED_LIBS' option to ON.
			- �� option�� �������� ������ .a library file ����.
		- set the 'CMAKE_GNUtoMS' option to ON.
			- [ref] https://cmake.org/cmake/help/v3.0/prop_tgt/GNUtoMS.html
			- <warning message> Disabling CMAKE_GNUtoMS option because CMAKE_GNUtoMS_VCVARS is not set
			- set the 'CMAKE_GNUtoMS_VCVARS' option to 'C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/vcvars32.bat'
	5. configure and generate.
	6. cd cmake-build directory.
	7. run make.

		`mingw32-make` <br />
		`mingw32-make PREFIX=${INSTAL_PREFIX} install`
- In MSYS console (==> not working)
	1. set ${MINGW_ROOT}/bin path.

		`export PATH=${MINGW_ROOT}/bin:$PATH`
	2. run cmake-gui.
		- Windows�� software ��� ����.
	3. specify 'MSYS Makefiles' as the generator.

##### Installation Prefix Setting
- MinGW�� MSYS�� ��� /usr �̳� /usr/local directory�� ����
	- ����, software installation prefix�� �Ʒ��� directory�� ����Ͽ��� ��.

		`--prefix=${MINGW_ROOT}`
	- �׷��� �Ʒ��� directory�� installation file�� �߰�.
		- ${MINGW_ROOT}/include or ${MSYS_ROOT}/include
		- ${MINGW_ROOT}/lib or ${MSYS_ROOT}/lib
