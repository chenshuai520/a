#include "stdafx.h"
#include <Eigen/Core>


// import most common Eigen types 
USING_PART_OF_NAMESPACE_EIGEN

int fixed_size(int, char *[])
{
	Matrix3f m3;
	m3 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	Matrix4f m4 = Matrix4f::Identity();
	Vector4i v4(1, 2, 3, 4);

	std::cout << "m3\n" << m3 << "\nm4:\n" << m4 << "\nv4:\n" << v4 << std::endl;

	return 0;
}