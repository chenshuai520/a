#include "../HelloJniClass.h"
#include <jni.h>
#include <iostream>


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_JNI_1Message_Message(JNIEnv *env, jobject jobj, jstring input)
{
	jboolean iscopy;
	static char outputbuf[20];

	const char *buf = env->GetStringUTFChars(input, &iscopy);  // �Է� String �о���� �Լ�
	std::cout << "\nDLL receive Data from JAVA : " << buf << std::endl;   // �Է¹��� ������ ���
	strcpy(outputbuf, "Delicious !!\n"); 
	const jstring js = env->NewStringUTF(outputbuf);  // ����� ������ java���ۿ� output���۰��� ����

	return js; // java���� ����
}

#ifdef __cplusplus
}
#endif