#include "ARSByEKFAndQuaternion.h"
#include "mm.h"


// [ref]
//	http://blog.daum.net/pg365/83.
//	http://blog.daum.net/pg365/172.


void ARSByEKFAndQuaternion::initialize()
{
	base_type::initialize();

	// EKF�� ���� ���Ϳ� ���л� ����� �ʱ�ȭ �Ѵ�.
	x_.set_s(1);
	x_.set_v(dVector3(0, 0, 0));

	P_.unit();  // ���л� ����� ������ķ� �ʱ�ȭ
}

dMatrix ARSByEKFAndQuaternion::getStateTransitionMatrix(double wx, double wy, double wz, const double &dt) const
{
	dMatrix A(4, 4);

	wx *= 0.5*dt;
	wy *= 0.5*dt;
	wz *= 0.5*dt;

	A(0,0) = 1;		A(0,1) = wz;	A(0,2) = -wy;	A(0,3) = wx;
	A(1,0) = -wz;	A(1,1) = 1;		A(1,2) = wx;	A(1,3) = wy;
	A(2,0) = wy;	A(2,1) = -wx;	A(2,2) = 1;		A(2,3) = wz;
	A(3,0) = -wx;	A(3,1) = -wy;	A(3,2) = -wz;	A(3,3) = 1;

	return A;
}

dMatrix ARSByEKFAndQuaternion::getMeasurementMatrix(const Quaternion &q) const
{
	const double eps = 1e-10;

	const double e1 = q.v_[0];
	const double e2 = q.v_[1];
	const double e3 = q.v_[2];
	double a = e3*(e1*e1 + e2*e2 + e3*e3);
	double b = std::sqrt(e1*e1 + e2*e2);

	if (-eps < a && a < eps) a = eps;
	if (b < eps) b = eps;

	const double _h[1][4] = { 
		{ (e1*e3*e3 + eps)/(a*b + eps), (e2*e3*e3 + eps)/(a*b + eps), (e3*b + eps)/(a + eps), 0	},
	};

	// observation matrix
	dMatrix H(1, 4, &_h[0][0]);

	return H;
}

dMatrix ARSByEKFAndQuaternion::filter(const double gyro[3], const double accel[3], const double magn[3], const double &dt)
{
	computeGyroAverage(average_gyro_, gyro, 10000, 10.);

	/////////////////////////////////////////////////////////////////////////
	// Predict ����

	// ���̷� ������ ���̾ ���� �����ϱ� ���� ���ӵ� ������ ���ӵ� ��հ��� ����.
	dVector w = dVector3(
		_DEG2RAD*(gyro[0] - average_gyro_[0]), 
		_DEG2RAD*(gyro[1] - average_gyro_[1]), 
		_DEG2RAD*(gyro[2] - average_gyro_[2])
	);

	// state transition matrix
	dMatrix A = getStateTransitionMatrix (w[0], w[1], w[2], dt);
	
	double _b[4][3] = {
		{ x_.s_,    -x_.v_[2],  x_.v_[1] },
		{ x_.v_[2],  x_.s_,    -x_.v_[0] },
		{-x_.v_[1],  x_.v_[0],  x_.s_    },
		{-x_.v_[0], -x_.v_[1], -x_.v_[2] },
	};

	dMatrix B(4, 3, &_b[0][0]);
	B = B * 0.5 * dt;

	const double _q[3][3] = { 
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 },
	};

	// Covariance matrix of porcess noises
	const dMatrix Q(3, 3, &_q[0][0]);

	// Predicted state estimate
	x_ = x_ * Quaternion(w[0]*dt, w[1]*dt, w[2]*dt);
	// Predicted estimate covariance
	P_ = A * P_ * ~A + B * Q * ~B;

	/////////////////////////////////////////////////////////////////////////
	// Update ����

	// ������ �������� �ʴ� ��Ȳ���� �׻� �߷� ���ӵ��� �Ʒ� ����(-z)���� �ۿ��ϰ� �ֱ�
	// ������, ������ �������� ���� ���� ���ӵ� ����(g)�� �߷°� �����ϴ�. �׷���
	// ���ӵ� ������ �ڼ��κ��� ���� �ڼ� _Q�� ������ �� �ִ�.
	dVector g0 = dVector3(0., 0., -1.);
	Quaternion a(0, accel[0], accel[1], accel[2]);

	// g�� ���� ��ǥ�踦 �������� �� �����̹Ƿ�, �̵��� ���� ��ǥ�� �������� ǥ���ϱ� 
	// ���ؼ��� _Q�� ���ؼ� ���� ��ǥ�� �������� ��ȯ�Ѵ�.
	Quaternion ag = x_ * a * x_.i();

	// ���� ��ǥ�迡�� ���ӵ� ������ ������ �߷� ����(Qg)�� �̻����� �߷� ����(g0)�� �̷�� 
	// normal vector(ng)�� ���հ�(alpha)�� ���Ѵ�.
	dVector ng = Cross(ag.v(), g0);
	double alpha = std::asin(Norm2(ng) / Norm2(ag.v()));

	dMatrix H = getMeasurementMatrix(x_);

	// �߷����� ã�� ������ ������ ������Ʈ �ϴ� ����(�̵�)�� ���Ѵ�. 
	// �߷� ������ ũ�Ⱑ 1.��ó�� �� �̵��� Ŀ���ϰ� 1.���� �־��� ���� �̵��� ����� �Ѵ�.
	double l = std::sqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]) - 1.;
	double s = std::exp(-l * l);

	const double _r[1][1] = { 
		{ 1/s },
	};

	const dMatrix R(1, 1, &_r[0][0]);

	// Kalman gain
	dMatrix K = P_ * ~H * !(H * P_ * ~H + R);

	double Ka = K.normF ();

	// Updated state estimate
	x_ = Quaternion(Ka * alpha, ng) * x_;
	x_.unit();

	// Updated estimate covariance
	P_ = P_ - K * H * P_;

	return x_.RotationMatrix ();
}
