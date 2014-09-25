#if !defined(__SIGNAL_PROCESSING__IMU_FILTERING__ARS__ARS_BY_EKF_AND_ROTATION_MATRIX_H__)
#define __SIGNAL_PROCESSING__IMU_FILTERING__ARS__ARS_BY_EKF_AND_ROTATION_MATRIX_H__ 1


#include "ARS.h"


class ARSByEKFAndRotationMatrix : public ARS 
{
public:
	typedef ARS base_type;

public:
	ARSByEKFAndRotationMatrix()
	: base_type(),
	  x_(3, 1), P_(3, 3)
	{}
private:
	virtual ~ARSByEKFAndRotationMatrix()
	{}

private:
	explicit ARSByEKFAndRotationMatrix(const ARSByEKFAndRotationMatrix &rhs);  // not implemented.
	ARSByEKFAndRotationMatrix & operator=(const ARSByEKFAndRotationMatrix &rhs);  // not implemented.

public:
	/*virtual*/ void initialize();
	// gyroscope : [deg/sec], acceleromter : [g], magnetometer : gauss [G], dt : sampling time.
	/*virtual*/ dMatrix filter(const double gyro[3], const double accel[3], const double magn[3], const double &dt);

private:
	dMatrix getCInv(const double &phi, const double &theta) const;
	dMatrix getStateTransitionMatrix(const double &phi, const double &theta, const double &wy, const double &wz) const;

private:
	// EKF�� ���� ����, ���⼭�� roll, pitch, yaw ���� ������ ����̴�.
	dMatrix x_;
	// ���� ������ ���л� ���.
	dMatrix P_;
};


#endif  // __SIGNAL_PROCESSING__IMU_FILTERING__ARS__ARS_BY_EKF_AND_ROTATION_MATRIX_H__
