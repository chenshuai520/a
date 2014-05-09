package rapidminer;

import java.util.ArrayList;
import java.util.List;
import java.io.File;
import java.io.IOException;

import com.rapidminer.example.Attribute;
import com.rapidminer.example.ExampleSet;
import com.rapidminer.example.table.AttributeFactory;
import com.rapidminer.example.table.DoubleArrayDataRow;
import com.rapidminer.example.table.MemoryExampleTable;
import com.rapidminer.gui.renderer.models.EigenvectorModelEigenvalueRenderer.EigenvalueTableModel;
import com.rapidminer.gui.renderer.models.EigenvectorModelEigenvectorRenderer.EigenvectorTableModel;
import com.rapidminer.operator.IOContainer;
import com.rapidminer.operator.OperatorException;
import com.rapidminer.operator.features.transformation.PCAModel;
import com.rapidminer.tools.Ontology;


/**
 * RapidMiner�� PCA ������ ������ ���� Ŭ����
 */
public class RapidMinerPCA extends AbstractRapidMinerProcess
{
	/**
	 * ����Ʈ ���μ����� PCA�� �����ϴ� ������Ʈ�� �����Ѵ�.
	 */
	public RapidMinerPCA()
	{
		super("data/machine_learning/rapidminer/proc_PCA.xml");
	}
	
	/**
	 * PCA�� �����ϴ� ������Ʈ�� �����Ѵ�.
	 * 
	 * @param processFile PCA ���μ����� ����� RapidMiner ���� ���.
	 */
	public RapidMinerPCA(String processFile)
	{
		super(processFile);
	}
	
	/**
	 */
	@Override
	public void run()
	{
		if (null == example_)
		{
			System.err.println("ExampleSet is null - loadData() before run()");
			return;
		}
		
		// ���μ���
		try
		{
			// �̸� �����Ǿ� �ִ� RapidMiner ������ �����Ѵ�
			IOContainer c = proc_.run(new IOContainer(example_));
			
			// PCA Model �� ��� �������Ϳ� �������� �ٸ� ���·� �����Ѵ� 
			//com.rapidminer.example.set.SimpleExampleSet exampleSet = (com.rapidminer.example.set.SimpleExampleSet)c.getElementAt(0);
			//com.rapidminer.example.set.SimpleExampleSet original = (com.rapidminer.example.set.SimpleExampleSet)c.getElementAt(1);
			PCAModel pcaModel = (PCAModel)c.getElementAt(2);
			
			// ������
			EigenvalueTableModel eigenValMat = pcaModel.getEigenvalueTableModel();			
			// ��������
			EigenvectorTableModel eigenVecMat = pcaModel.getEigenvectorTableModel();

			System.out.println("Eigen Values : " + eigenValMat.getRowCount() + " rows");
			System.out.println("Eigen Vectors : " + eigenVecMat.getColumnCount() + " x " + eigenVecMat.getRowCount() + " matrix");
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
	
	/**
	 */
	public void loadData()
	{
		String filepath = "./data/machine_learning/rapidminer/iris.csv";
		com.rapidminer.tools.LineParser parser = new com.rapidminer.tools.LineParser();
		try
		{
			parser.setSplitExpression(com.rapidminer.tools.LineParser.SPLIT_BY_COMMA_EXPRESSION);
		}
		catch (OperatorException e1)
		{
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		com.rapidminer.gui.tools.dialogs.wizards.dataimport.csv.CSVFileReader reader = new com.rapidminer.gui.tools.dialogs.wizards.dataimport.csv.CSVFileReader(new File(filepath), true, parser, java.text.NumberFormat.getInstance()); 

		try
		{
			example_ = reader.createExampleSet();
			com.rapidminer.example.Attributes attributes = example_.getAttributes();
			attributes.setLabel(attributes.get("label"));
			attributes.remove(attributes.get("id"));
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	// RapidMiner ������
	private ExampleSet example_ = null;
}
