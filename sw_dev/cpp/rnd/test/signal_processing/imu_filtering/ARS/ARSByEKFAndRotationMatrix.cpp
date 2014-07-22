//#include "StdAfx.h"
#include "ARSByEKFAndRotationMatrix.h"
#include "mm.h"


// [ref]
//	http://blog.daum.net/pg365/78.
//	http://blog.daum.net/pg365/170
//	http://blog.daum.net/pg365/171


void ARSByEKFAndRotationMatrix::initialize()
{
	base_type::initialize();

	// EKF�� ���� ���Ϳ� ���л� ����� �ʱ�ȭ �Ѵ�.
	x_.null();  // ���º��ʹ� 0���� �ʱ�ȭ
	P_.unit();  // ���л� ����� ������ķ� �ʱ�ȭ
}

dMatrix ARSByEKFAndRotationMatrix::getCInv(const double &phi, const double &theta) const
{
	// ���Ϸ��� ��ȭ���� ���ӵ����� ���踦 ǥ���ϴ� ����� ����Ѵ�.

	double sin_phi = sin(phi),		cos_phi = cos(phi);
	double sin_tht = sin(theta),	cos_tht = cos(theta),	tan_tht = tan(theta);

	dMatrix C(3,3);

	C(0,0) = 1;		C(0,1) = sin_phi*tan_tht;	C(0,2) = cos_phi*tan_tht;
	C(1,0) = 0;		C(1,1) = cos_phi;			C(1,2) = -sin_phi;
	C(2,0) = 0;		C(2,1) = sin_phi/cos_tht;	C(2,2) = cos_phi/cos_tht;

	return C;
}

dMatrix ARSByEKFAndRotationMatrix::getStateTransitionMatrix(const double &phi, const double &theta, const double &wy, const double &wz) const
{
	// �ý��� �� f�� ���ں���� ����Ѵ�.

	double sin_phi = sin(phi),		cos_phi = cos(phi);
	double sin_tht = sin(theta),	cos_tht = cos(theta),	tan_tht = tan(theta);

	dMatrix F(3,3);

	F(0,0) = 1 + wy*cos_phi*tan_tht - wz*sin_phi*tan_tht;		
	F(0,1) = 0 + wy*sin_phi/(cos_tht*cos_tht) + wz*cos_phi/(cos_tht*cos_tht);
	F(0,2) = 0;
	F(1,0) = 0 - wy*sin_phi - wz*cos_phi;
	F(1,1) = 1;
	F(1,2) = 0;
	F(2,0) = 0 + wy*cos_phi/cos_tht - wz*sin_phi/cos_tht;		
	F(2,1) = 0 + wy*sin_phi/cos_tht*tan_tht + wz*cos_phi/cos_tht*tan_tht;
	F(2,2) = 1;

	return F;
}

dMatrix ARSByEKFAndRotationMatrix::filter(const double gyro[3], const double accel[3], const double magn[3], const double &dt)
{
	computeGyroAverage(average_gyro_, gyro, 10000, 100.);

	// ���̷� ������ ���̾ ���� �����ϱ� ���� ���ӵ� ������ ���ӵ� ��հ��� ����.
	dMatrix w = MakeMatrix(dVector3(
		_DEG2RAD*(gyro[0] - average_gyro_[0])*dt, 
		_DEG2RAD*(gyro[1] - average_gyro_[1])*dt, 
		_DEG2RAD*(gyro[2] - average_gyro_[2])*dt)
	);

	/////////////////////////////////////////////////////////////////////////
	// Predict ����

	// ���ӵ��� ���Ϸ��� ��ȭ���� ��ȯ�ϴ� ���
	dMatrix Cinv = getCInv(x_(0,0), x_(1,0));

	// state transition matrix
	dMatrix F = getStateTransitionMatrix(x_(0,0), x_(1,0), w(1,0), w(2,0));
	
	const double _q[3][3] = { 
		{0.001, 0, 0},
		{0, 0.001, 0},
		{0, 0, 0.001}
	};

	// Covariance matrix of porcess noises
	const dMatrix Q(3, 3, &_q[0][0]);

	// Predicted state estimate
	x_ = x_ + Cinv * w;
	// Predicted estimate covariance
	P_ = F* P_ * ~F + Q;

	/////////////////////////////////////////////////////////////////////////
	// Update ����

	// �߷°��ӵ� ���� 1��ó�� ���� �� �̵�(k1)�� ū ���� �������� �Ѵ�.
	double v = std::sqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]) - 1.;
	double sigma = 1.;
	double s = std::max(1e-5, std::exp(-v * v / (sigma * sigma)));

	double _r[2][2] = { 
		{1/s, 0},
		{0, 1/s}
	};

	// Covariance matrix of observation noises
	dMatrix R(2, 2, &_r[0][0]);

	// measurement value
	dMatrix z(2, 1);
	z(0,0) = accel[2] ? std::atan(accel[1] / accel[2]) : x_(0,0);
	z(1,0) = (-1 < accel[0] && accel[0] < 1) ? std::asin(-accel[0] / -1.) : x_(1,0);

	//  predicted measurement from the predicted state
	dMatrix h(2,1);
	h(0,0) = x_(0,0);
	h(1,0) = x_(1,0);

	// measurement residual
	// y = z - h
	dMatrix y(2, 1);
	y(0,0) = DeltaRad(z(0,0), h(0,0));
	y(1,0) = DeltaRad(z(1,0), h(1,0));

	const double _h[2][3] = { 
		{1, 0, 0},
		{0, 1, 0}
	};

	// observation matrix
	const dMatrix H(2, 3, &_h[0][0]);

	// Kalman gain
	dMatrix K = P_ * ~H * !(H * P_ * ~H + R);

	// Updated state estimate
	x_ = x_ + K * y;
	// Updated estimate covariance
	P_ = P_ - K * H * P_;

	return RotationMatrix (x_(0,0), x_(1,0), x_(2,0));
}
