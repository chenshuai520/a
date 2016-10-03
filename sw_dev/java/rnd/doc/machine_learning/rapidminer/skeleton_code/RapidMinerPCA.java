package ml.rapidminer;

import java.util.ArrayList;
import java.util.List;

import ml.PrincipalComponentAnalysis;

import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import bin.util.opencv.MatUtil;

import com.googlecode.javacv.cpp.opencv_core.CvMat;
import static com.googlecode.javacv.cpp.opencv_core.*;

import com.rapidminer.example.Attribute;
import com.rapidminer.example.ExampleSet;
import com.rapidminer.example.table.AttributeFactory;
import com.rapidminer.example.table.DoubleArrayDataRow;
import com.rapidminer.example.table.MemoryExampleTable;
import com.rapidminer.gui.renderer.models.EigenvectorModelEigenvalueRenderer.EigenvalueTableModel;
import com.rapidminer.gui.renderer.models.EigenvectorModelEigenvectorRenderer.EigenvectorTableModel;
import com.rapidminer.operator.IOContainer;
import com.rapidminer.operator.features.transformation.PCAModel;
import com.rapidminer.tools.Ontology;


/**
 * RapidMiner�� PCA ������ ������ ���� Ŭ����
 */
public class RapidMinerPCA extends AbstractRapidMinerProcess implements PrincipalComponentAnalysis {
	
	private		Logger							log = LogManager.getLogger(RapidMinerPCA.class);	
	
	// RapidMiner ���μ���
	private 	CvMat							eigenValue = null;
	private 	CvMat							eigenVector = null;
	
	// RapidMiner ������
	private		ExampleSet					example = null;
	
	/**
	 * ����Ʈ ���μ����� PCA�� �����ϴ� ������Ʈ�� �����Ѵ�
	 */
	public RapidMinerPCA() {
		super("res/rapidminer/proc_pca.xml");
	}
	
	/**
	 * PCA�� �����ϴ� ������Ʈ�� �����Ѵ�
	 * 
	 * @param processFile				PCA ���μ����� ����� RapidMiner ���� ���
	 */
	public RapidMinerPCA(String processFile) {
		super(processFile);
	}
	
	/* (non-Javadoc)
	 * @see ml.rapidminer.PrincipalComponentAnalysis#run()
	 */
	@Override
	public void run() {
		
		// Pre-Condition üũ
		if(example == null) {
			log.error("ExampleSet is null - setData() before run()");
			return;
		}
		
		// ���μ���
		try {
			// �̸� �����Ǿ� �ִ� RapidMiner ������ �����Ѵ�
			IOContainer c = proc.run(new IOContainer(example));
			
			// PCA Model �� ��� �������Ϳ� �������� �ٸ� ���·� �����Ѵ� 
			PCAModel pcaModel = (PCAModel) c.getElementAt(1);
			
			// ������
			EigenvalueTableModel eigenValMat = pcaModel.getEigenvalueTableModel();			
			eigenValue = MatUtil.createMat(eigenValMat.getRowCount(), eigenValMat.getColumnCount() - 1, CV_32FC1);
			for(int i = 0; i < eigenValMat.getRowCount(); i++) {
				for(int j = 1; j < eigenValMat.getColumnCount(); j++) {
					try {
						eigenValue.put(i, j - 1, Float.parseFloat(eigenValMat.getValueAt(i, j).toString()));
					} catch (NumberFormatException nfe) {
						log.warn("EigenValue Number Format Exception at (" + i + ", " + j + ") : " + eigenValMat.getValueAt(i, j));
					}
				}
			}
			// ��������
			EigenvectorTableModel eigenVecMat = pcaModel.getEigenvectorTableModel();
			eigenVector = MatUtil.createMat(eigenVecMat.getRowCount(), eigenVecMat.getColumnCount() - 1, CV_32FC1);
			for(int i = 0; i < eigenVecMat.getRowCount(); i++) {
				for(int j = 1; j < eigenVecMat.getColumnCount(); j++) {
					try {
						eigenVector.put(i, j - 1, Float.parseFloat(eigenVecMat.getValueAt(i, j).toString()));
					} catch (NumberFormatException nfe) {
						eigenVector.put(i, j - 1, 0);
						log.warn("EigenVector Number Format Exception at (" + i + ", " + j + ") : " + eigenVecMat.getValueAt(i, j));
					}
				}
			}
			
			log.info("Eigen Values : " + eigenValue.rows()+ " rows");
			log.info("Eigen Vectors : " + eigenVector.cols() + " x " + eigenVector.rows()+ " matrix");
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/* (non-Javadoc)
	 * @see ml.rapidminer.PrincipalComponentAnalysis#setData(com.googlecode.javacv.cpp.opencv_core.CvMat)
	 */
	@Override
	public void setData(CvMat data) {
		// �Ű����� üũ
		if(data == null) {
			log.error("setData() - Argument is null");
			return;
		}
		if(data.cols() <= 0 || data.rows() <= 0){
			log.error("setData() - Invalid argument cols = " + data.cols() + ", rows = " + data.rows());
			return;
		}
		
		// Attribute ����� ����
		List<Attribute> attr = new ArrayList<Attribute>();
		for(int i = 0; i < data.cols(); i++) {
			attr.add(AttributeFactory.createAttribute("x" + i,  Ontology.NUMERICAL));
		}
		
		// ExampleSet�� ����
		MemoryExampleTable table = new MemoryExampleTable(attr);		
		for(int i = 0; i < data.rows(); i++) {						
			// Row �����͸� ä������
			double[] dataRow = new double[data.cols()];
			for(int j = 0; j < data.cols(); j++) {
				dataRow[j] = data.get(i, j);
			}
			table.addDataRow(new DoubleArrayDataRow(dataRow));
		}
		example = table.createExampleSet();
	}
	
	/* (non-Javadoc)
	 * @see ml.rapidminer.PrincipalComponentAnalysis#getEigenValue()
	 */
	@Override
	public CvMat getEigenValue() {
		return eigenValue;
	}
	
	/* (non-Javadoc)
	 * @see ml.rapidminer.PrincipalComponentAnalysis#getEigenVector()
	 */
	@Override
	public CvMat getEigenVector() {
		return eigenVector;
	}
}
