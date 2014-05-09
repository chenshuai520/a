package rapidminer;

import java.io.File;
import java.io.IOException;

import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import com.rapidminer.Process;
import com.rapidminer.RapidMiner;
import com.rapidminer.RapidMiner.ExecutionMode;
import com.rapidminer.tools.XMLException;

/**
 * RapidMiner�� ���μ����� �����ϱ� ���� ���� �Ӽ��� ����� ������ �߻� Ŭ����.
 */
public abstract class AbstractRapidMinerProcess implements Runnable
{
	public static void init()
	{
		if (initRapidminer_)
		{
			RapidMiner.setExecutionMode(ExecutionMode.EMBEDDED_WITHOUT_UI);
			System.setProperty("rapidminer.home", new File("D:/MyProgramFiles/Rapid-I/RapidMiner5").getAbsolutePath());
			
			// activate parallel plug-in.
			//com.rapidminer.ParallelPluginInit.initPlugin();
			//com.rapidminer.PluginInitWekaExtension.initPluginManager();
			
			RapidMiner.init();
			initRapidminer_ = false;
		}
	}
	
	/**
	 * RapidMiner ���μ����� �����ϴ� Ŭ������ �����Ѵ�.
	 * 
	 * @param processConfig ���μ��� ������ ���ǵ� ����.
	 */
	public AbstractRapidMinerProcess(String processConfig)
	{
		Logger logger = LogManager.getLogger(AbstractRapidMinerProcess.class);
		procConfigFile_ = new File(processConfig);
		
		if (initRapidminer_)
		{
			AbstractRapidMinerProcess.init();
		}
	
		if (procConfigFile_.exists())
		{
			try
			{
				proc_ = new Process(procConfigFile_);
			}
			catch (Exception e)
			{
				logger.error(e);
			}
		}
		else
		{
			logger.fatal("RapidMiner Process file " + procConfigFile_.getAbsolutePath() + " is not exist!!!");
			System.exit(-1);
		}
	}
	
	// Getter & Setter
	
	/**
	 * ���μ��� ���� ��θ� ����
	 * @return
	 */
	public String getProcessConfigureationFile()
	{
		return procConfigFile_.exists() ? procConfigFile_.getAbsolutePath() : null;
	}
	
	/**
	 * ���μ��� ������ �����Ѵ�
	 * @param procConfigFile_
	 */
	public void setProcessConfigureation(String processConfig)
	{
		procConfigFile_ = new File(processConfig);
		try
		{
			proc_ = new Process(procConfigFile_);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		catch (XMLException e)
		{
			e.printStackTrace();
		}
	}

	private static boolean initRapidminer_ = true;
	protected Process proc_;  // RapidMiner process.
	protected File procConfigFile_;  // a file in which a process is defined 
}
