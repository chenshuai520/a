#include "ARSByComplementaryFilterAndRotationMatrix.h"
#include "mm.h"


// [ref]
//	http://blog.daum.net/pg365/79
//	http://blog.daum.net/pg365/170
//	http://blog.daum.net/pg365/171


void ARSByComplementaryFilterAndRotationMatrix::initialize()
{
	base_type::initialize();

	// ȸ������� ������ķ� �ʱ�ȭ �Ѵ�.
	R_.unit();
}

dMatrix ARSByComplementaryFilterAndRotationMatrix::filter(const double gyro[3], const double accel[3], const double magn[3], const double &dt)
{
	computeGyroAverage(average_gyro_, gyro, 10000, 10.);

	// ���̷� ������ ���̾ ���� �����ϱ� ���� ���ӵ� ������ ���ӵ� ��հ��� ����.
	// �׸��� ������ ��ȭ���� ȸ����ķ� ��ȯ�Ѵ�.
	dMatrix dR = RotationMatrix(
		_DEG2RAD*(gyro[0] - average_gyro_[0])*dt, 
		_DEG2RAD*(gyro[1] - average_gyro_[1])*dt, 
		_DEG2RAD*(gyro[2] - average_gyro_[2])*dt
	);

	// ȸ�� ����� ���� �� ������ ���ϴ� ȿ���� ������.
	// R*dR�� R��ŭ ȸ���� ��ǥ�踦 dR��ŭ �� ȸ���ϰ� �ȴ�.
	R_ = R_ * dR;

	dMatrix g = dMatrix(3, 1, accel);
	dMatrix m = dMatrix(3, 1, magn);

	// accel�� magn�� ���� ��ǥ�踦 �������� ������ ���̴�.
	// ������ �ڼ�(R)�� ���ؼ� ������ǥ�踦 �������� �� ������ �ٲ��ش�.
	g = R_ * g;
	m = R_ * m;

	// �߷°��ӵ� ���� 1��ó�� ���� �� �̵�(k1)�� ū ���� �������� �Ѵ�.
	double l = std::sqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]) - 1.;
	double sigma = 0.1;
	double k1 = 0.1 * std::exp(-l * l / (sigma * sigma));

#if defined ADIS_16405
	double k2 = 0.1;

	// ������ �������� ����Ѵ�.
	double dPhi   = g(2,0) ? std::atan(g(1,0) / g(2,0)) : 0.;
	double dTheta = (-1 < g(0,0) && g(0,0) < 1) ? std::asin(-g(0,0) / -1.) : 0.;
	double dPsi   = -std::atan2(m(1,0), m(0,0));
#else
	double k2 = 0.;

	// ������ �������� ����Ѵ�.
	double dPhi   = g(2,0) ? std::atan(g(1,0) / g(2,0)) : 0.;
	double dTheta = (-1 < g(0,0) && g(0,0) < 1) ? std::asin(-g(0,0) / -1.) : 0.;
	double dPsi   = 0.;
#endif

	adjust_rpy_[0] = dPhi;
	adjust_rpy_[1] = dTheta;
	adjust_rpy_[2] = dPsi;

	// ���Ϸ������� ����� �������� ȸ����ķ� ��ȯ�Ѵ�.
	dMatrix aR = RotationMatrix(k1 * dPhi, k1 * dTheta, k2 * dPsi);

	// ���� ������(aR)�� ������ǥ�踦 �������� ���� ���̴�.
	// �׷��Ƿ� R�� �տ��� aR�� ���ؾ� �Ѵ�.
	// R*aR �� ���� ���� �ʵ��� �����Ѵ�.
	R_ = aR * R_;

	return R_;
}
