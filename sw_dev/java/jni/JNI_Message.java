class JNI_Message
{
	native String Message(String input);
   
  // ���̺귯�� ����(Load the library)  
	static
	{
		System.loadLibrary("Msg_DLL");
	}

	public static void main(String args[])
	{
		String buf;

		// Ŭ���� �ν��Ͻ� ����(Create class instance)
		JNI_Message myJNI = new JNI_Message();

		// ���� �޼ҵ忡 ���� �ְ� ����
		buf = myJNI.Message("Apple");

		System.out.print(buf); // ������ ���
	}
}
