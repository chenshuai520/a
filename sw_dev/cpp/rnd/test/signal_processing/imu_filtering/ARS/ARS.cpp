//#include "stdafx.h"
#include "ARS.h"


void ARS::initialize()
{
	for (int i = 0; i < 3; ++i)
	{
		average_gyro_[i] = 0.0;
		adjust_rpy_[i] = 0.0;
	}

	average_gyro_count_ = 0;
}

void ARS::computeGyroAverage(double average_gyro[3], const double gyro[3], const std::size_t max_count, const double tolerance)
{
	// ������ ������ �ִ��� ���ӵ���(gyroscope)���� ���� ���� 0�� ���� ������ �ʴ´�.
	// ��κ� Ư���� ������ ���̾ �Ǿ��ִµ�, �� ���� 0���� �����ϱ� ���Ͽ�
	// ������ �������� ���� �� ���ӵ� ���� ����� ���Ѵ�.

	double d0 = gyro[0] - average_gyro[0];
	double d1 = gyro[1] - average_gyro[1];
	double d2 = gyro[2] - average_gyro[2];

	if (!average_gyro_count_ || ( 
		-tolerance < d0 && d0 < tolerance && 
		-tolerance < d1 && d1 < tolerance && 
		-tolerance < d2 && d2 < tolerance)
		)
	{
		average_gyro[0]  = (average_gyro[0]*average_gyro_count_ + gyro[0])/(average_gyro_count_+1);
		average_gyro[1]  = (average_gyro[1]*average_gyro_count_ + gyro[1])/(average_gyro_count_+1);
		average_gyro[2]  = (average_gyro[2]*average_gyro_count_ + gyro[2])/(average_gyro_count_+1);
	}

	if (average_gyro_count_ < max_count) ++average_gyro_count_;
}
