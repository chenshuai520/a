package ml.rapidminer;

import java.io.File;
import java.io.IOException;

import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import com.rapidminer.Process;
import com.rapidminer.RapidMiner;
import com.rapidminer.RapidMiner.ExecutionMode;
import com.rapidminer.tools.XMLException;

/**
 * RapidMiner�� ���μ����� �����ϱ� ���� ���� �Ӽ��� ����� ������ �߻� Ŭ����
 */
public abstract class AbstractRapidMinerProcess
										implements Runnable {
	
	private static 	boolean			initRapidminer = true;
	protected 	Process				proc;						// RapidMiner ���μ���
	protected	File				procConfigFile;				// ���μ��� ������ ���ǵ� ����
	
	public static void init() {
		if(initRapidminer) {
			RapidMiner.setExecutionMode(ExecutionMode.EMBEDDED_WITHOUT_UI);
			System.setProperty("rapidminer.home", new File("res/rapidminer/home").getAbsolutePath());
			
			// �з��� �÷����� Ȱ��ȭ
			com.rapidminer.ParallelPluginInit.initPlugin();
			com.rapidminer.PluginInitWekaExtension.initPluginManager();
			
			RapidMiner.init();
			initRapidminer = false;
		}
	}
	
	/**
	 * RapidMiner ���μ����� �����ϴ� Ŭ������ �����Ѵ�
	 * 
	 * @param processConfig			���μ��� ������ ���ǵ� ����
	 */
	public AbstractRapidMinerProcess(String processConfig) {
		Logger logger = LogManager.getLogger(AbstractRapidMinerProcess.class);
		procConfigFile = new File(processConfig);
		
		if(initRapidminer) {
			AbstractRapidMinerProcess.init();
		}
	
		if(procConfigFile.exists()) {
			try {
				proc = new Process(procConfigFile);
			} catch (Exception e) {
				logger.error(e);
			}
		}
		else {
			logger.fatal("RapidMiner Process file " + procConfigFile.getAbsolutePath() + " is not exist!!!");
			System.exit(-1);
		}
	}
	
	// Getter & Setter
	
	/**
	 * ���μ��� ���� ��θ� ����
	 * @return
	 */
	public String getProcessConfigureationFile() {
		if(procConfigFile.exists()) { return procConfigFile.getAbsolutePath(); }
		return null;
	}
	
	/**
	 * ���μ��� ������ �����Ѵ�
	 * @param procConfigFile
	 */
	public void setProcessConfigureation(String processConfig) {
		procConfigFile = new File(processConfig);
		try {
			proc = new Process(procConfigFile);
		} catch (IOException e) {
			e.printStackTrace();
		} catch (XMLException e) {
			e.printStackTrace();
		}
	}
}
