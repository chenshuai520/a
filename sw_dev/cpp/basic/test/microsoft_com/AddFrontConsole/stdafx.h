// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#ifndef _WIN32_WINNT		// Windows XP �̻󿡼��� ����� ����� �� �ֽ��ϴ�.                   
#define _WIN32_WINNT 0x0501	// �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif						

#include <stdio.h>
#include <tchar.h>

#define __USE_ADDBACK_DUAL 1
//#define __USE_ADDBACK_DISPATCH 1
//#define __USE_ADDBACK_BYATTRIB_DISPATCH 1

//#define _ATL_ATTRIBUTES 1
#include <afxdisp.h>
#if defined(__USE_ADDBACK_DUAL) || defined(__USE_ADDBACK_DISPATCH)
#import "progid:AddBackServer.AddBack.1" no_namespace named_guids
#elif defined(__USE_ADDBACK_BYATTRIB_DISPATCH)
#import "progid:AddBack_byAttrib.AddBack.1" no_namespace named_guids
#endif
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
