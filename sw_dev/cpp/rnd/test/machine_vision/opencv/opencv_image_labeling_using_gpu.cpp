//#include "stdafx.h"
#define CV_NO_BACKWARD_COMPATIBILITY
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <iostream>
#include <stdexcept>


namespace {
namespace local {

//------------------------------------------------------------------------------
// cv::gpu::graphcut()
//	���������� nppiGraphcut_32s8u() ���.
//		NVIDIA Performance Primitives (NPP) library �ȿ� ����.

void graph_cut()
{
	throw std::runtime_error("not yet implemented");
}

void belief_propagation()
{
	throw std::runtime_error("not yet implemented");
}

}  // namespace local
}  // unnamed namespace

namespace my_opencv {

void image_labeling_using_gpu()
{
	local::graph_cut();
	local::belief_propagation();
}

}  // namespace my_opencv
