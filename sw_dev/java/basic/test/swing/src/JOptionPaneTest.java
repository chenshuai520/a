import javax.swing.*;

public class JOptionPaneTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final String kind = JOptionPane.showInputDialog("������ ������ �Է��ϼ���. (1:��, 2:�����, 3:����, 0:����)");
		String output;
		//if (kind.equals("1"))
		if (kind.equals("1"))
			output = "��";
		else if (kind.equals("2"))
			output = "�����";
		else if (kind.equals("3"))
			output = "����";
		else
			output = "�𸣴� ��";

		//JOptionPane.showMessageDialog(null, output);

		JTextArea showArea = new JTextArea();
	    showArea.setText(output);

		JOptionPane.showMessageDialog(null, showArea); 
	}

}
