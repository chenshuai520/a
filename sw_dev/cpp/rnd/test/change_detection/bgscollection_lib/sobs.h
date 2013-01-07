// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SOBS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SOBS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
//#ifdef SOBS_EXPORTS
//#define SOBS_API __declspec(dllexport)
//#else
//#define SOBS_API __declspec(dllimport)
//#endif


#include "cxcore.h"

typedef struct BestMacth 
{
	int x;
	int y;
	float dist;
	bool isShadow;
}BestMacth;


// �����Ǵ� sobs.dll ������
//class SOBS_API SOBS {
class SOBS {
public:
	static const float COS[360];
	static const float SIN[360];

private:
	int   frameIndex; //Current frame index
	static const int N = 3; //The scale of the background mode
	static const float A[3][3]; //���¾���

	CvRect roi;
	//SOBSROI roi;
	int   K;  //ѧϰ֡��
	float e1; //ѵ���׶����ƥ������
	float e2; //���׶����ƥ������
	float c1; //ѵ���׶α���������
	float c2; //���׶α���������
	///��Ӱ������ز���
	float gama;
	float beta;
	float TS;
	float TH;

	int step;

	int iChannel;
	int iHeight;
	int iWidth;
	int iWidthSetp;

	IplImage* scaledImage; //���ź��ͼ��
	IplImage* foregroundMaskImage; //The object detection result, binary image

	CvMat* backgroundModle;
	CvMat* hsvImage;
	//CvMat* bkMode1; //Self-Organised Neural network background mode
	//CvMat* bkMode2;
	//CvMat* bkMode3;


	bool InitSOBS(IplImage* firstFrame);
	void InitBkMode(CvMat* image);
	BestMacth FindBestMacth(int y, int x, CvMat* image);
	void UpdateBkMode(BestMacth bestMatch, CvMat* image);
	bool restrictROI();
	//bool isShadow(int y, int x, IplImage* image);
public:
	//Constructor function
	SOBS(int pK, int pe1, int pe2, int pc1, int pc2,
		int pgama, int pbeta, int pTS, int pTH);

	bool setROI(CvRect rect);
	CvRect getROI();
	int ProcessFrame(IplImage* image, IplImage* pFrImg=NULL);
	IplImage* GetForegroundMaskImage();
	//IplImage* GetFgmaskImage();
	bool GetFgmaskImage(IplImage* maskImage);
};


