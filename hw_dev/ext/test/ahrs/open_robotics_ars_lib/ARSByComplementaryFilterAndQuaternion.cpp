#include "ARSByComplementaryFilterAndQuaternion.h"
#include "mm.h"


// [ref]
//	http://blog.daum.net/pg365/81.
//	http://blog.daum.net/pg365/172.


void ARSByComplementaryFilterAndQuaternion::initialize()
{
	base_type::initialize();

	// ���� ���ʹϾ����� �ʱ�ȭ �Ѵ�.
	Q_.s_ = 1.;
	Q_.v_[0] = 0.;
	Q_.v_[1] = 0.;
	Q_.v_[2] = 0.;
}

dMatrix ARSByComplementaryFilterAndQuaternion::filter(const double gyro[3], const double accel[3], const double magn[3], const double &dt)
{
	computeGyroAverage(average_gyro_, gyro, 10000, 10.);

	// ���̷� ������ ���̾ ���� �����ϱ� ���� ���ӵ� ������ ���ӵ� ��հ��� ����.
	// �׸��� ������ ��ȭ���� 
	Quaternion dQ(
		_DEG2RAD*(gyro[0] - average_gyro_[0])*dt, 
		_DEG2RAD*(gyro[1] - average_gyro_[1])*dt, 
		_DEG2RAD*(gyro[2] - average_gyro_[2])*dt
	);
	
	// ���� ������ �ڼ��� ��Ÿ���� ���ʹϾ�(Q_)�� �ڼ� ��ȭ�� ���ʹϾ��� ���ؼ�
	// �ڼ��� ��ȭ�� ������Ʈ �Ѵ�.
	//Q_ = Q_ * dQ;

	// ������ �������� �ʴ� ��Ȳ���� �׻� �߷� ���ӵ��� �Ʒ� ����(-z)���� �ۿ��ϰ� �ֱ�
	// ������, ������ �������� ���� ���� ���ӵ� ����(g)�� �߷°� �����ϴ�. �׷���
	// ���ӵ� ������ �ڼ��κ��� ���� �ڼ� Q_�� roll�� pitch�� ������ �� �ִ�.
	dVector g0 = dVector3(0., 0., -1.);
	Quaternion Qa(0, accel[0], accel[1], accel[2]);

	// g�� ���� ��ǥ�踦 �������� �� �����̹Ƿ�, �̵��� ���� ��ǥ�� �������� ǥ���ϱ� 
	// ���ؼ��� Q_�� ���ؼ� ���� ��ǥ�� �������� ��ȯ�Ѵ�.
	Quaternion Qg = Q_ * Qa * Q_.i();

	// ���� ��ǥ�迡�� ���ӵ� ������ ������ �߷� ����(Qg)�� �̻����� �߷� ����(g0)�� �̷�� 
	// normal vector(ng)�� ���հ�(alpha)�� ���Ѵ�.
	dVector ng = Cross(Qg.v(), g0);
	double alpha = std::asin(Norm2(ng) / Norm2(Qg.v()));

	// �߷����� ã�� ������ ������ ������Ʈ �ϴ� ����(�̵�)�� ���Ѵ�. 
	// �߷� ������ ũ�Ⱑ 1.��ó�� �� �̵��� Ŀ���ϰ� 1.���� �־��� ���� �̵��� ����� �Ѵ�.
	double l = std::sqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]) - 1.;
	double sigma = 0.1;
	double Kg = 0.1 * std::exp(-l * l / (sigma * sigma));

	Q_ = Quaternion(Kg * alpha, ng) * Q_;

#if defined ADIS_16405
	{
		// ���ڱ�� �׻� ������ �������� �ۿ��ϰ� �ֱ� ������, ���ڱ� ������ ���ڱ� 
		// ����(m)�δ� yaw�� ������ �� �ִ�.
		Quaternion Qm(0, magn[0], magn[1], magn[2]);

		// m�� ���� ��ǥ�踦 �������� �� �����̹Ƿ�, �̵��� ���� ��ǥ�� �������� ǥ���ϱ� 
		// ���ؼ��� Q_�� ���ؼ� ���� ��ǥ�� �������� ��ȯ�Ѵ�.
		Qm = Q_ * Qm * Q_.i();

		dVector mn (0., 0., 1.);
		double alpha = -std::atan2(Qm.v()[1], Qm.v()[0]);
		const double Ka = 0.1;
		
		Q_ = Quaternion(Ka * alpha, mn) * Q_;
	}
#endif

	return Q_.RotationMatrix();
}
