//#include "stdafx.h"
#define CV_NO_BACKWARD_COMPATIBILITY
#include <opencv2/cudalegacy.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <stdexcept>


namespace {
namespace local {

//------------------------------------------------------------------------------
// cv::cuda::graphcut()
//	내부적으로 NVIDIA Performance Primitives (NPP) library에 있는 nppiGraphcut_32s8u() 사용.

struct BufferForBackgroundSubtraction
{
	cv::cuda::GpuMat terminals, leftTransp, rightTransp, top, bottom, labels, buf;
};

void calc_connectivity(const cv::Mat &src, cv::Mat &dst, const double threshold)
{
    dst = cv::Mat::zeros(src.size(), CV_32SC1);

    for (int y = 1; y < src.rows; ++y)
	{
        const int *spix = src.ptr<int>(y);
        const int *spix2 = src.ptr<int>(y - 1);
        int *dpix = dst.ptr<int>(y - 1);
        for (int x = 0; x < src.cols; ++x)
			dpix[x] = std::abs(threshold - std::abs(spix[x] - spix2[x]));
    }

    // ensure that the bottom pixels are 0.
    int *dpix = dst.ptr<int>(src.rows - 1);
    for (int x = 0; x < src.cols; ++x)
        dpix[x] = 0;
}

void background_subtraction_by_graph_cut()
{
	// [ref] http://ameblo.jp/sehr-lieber-querkopf/entry-11151368773.html
	//	background subtraction with considering color continuity with neighbor pixels

	const std::string src_filename("../data/machine_vision/opencv/bgsub_src.png");
	const std::string bg_filename("../data/machine_vision/opencv/bgsub_bg.png");
	const std::string diff_filename("../data/machine_vision/opencv/bgsub_diff.png");
	const std::string rightTransp_filename("../data/machine_vision/opencv/bgsub_rightTransp.png");
	const std::string bottom_filename("../data/machine_vision/opencv/bgsub_bottom.png");
	const std::string result_filename("../data/machine_vision/opencv/bgsub_result.png");
	const std::string diff_visualized_filename("../data/machine_vision/opencv/bgsub_diff_visualized.png");
	const std::string result_visualized_filename("../data/machine_vision/opencv/bgsub_result_visualized.png");

	const double threshold1 = 64.0;
	const double threshold2 = 32.0;
	const double lambda = 2.0;

	const cv::Mat src_img = cv::imread(src_filename, cv::IMREAD_GRAYSCALE);
	const cv::Mat bg_img = cv::imread(bg_filename, cv::IMREAD_GRAYSCALE);

	//
	cv::Mat src, bg;
	src_img.convertTo(src, CV_32SC1);
	bg_img.convertTo(bg, CV_32SC1);

	// calculate data terms (terminals)
	const cv::Mat diff(cv::abs(src - bg) - threshold1);

	// calculate smoothing terms
	cv::Mat rightTransp;
	cv::Mat bottom;
	calc_connectivity(src.t(), rightTransp, threshold2);
	calc_connectivity(src, bottom, threshold2);

	rightTransp *= lambda;
	bottom *= lambda;

	// calculate dummy terms (use if you need a directed MRF model)
	const cv::Mat leftTransp(rightTransp.size(), CV_32SC1, cv::Scalar::all(0));
	const cv::Mat top(bottom.size(), CV_32SC1, cv::Scalar::all(0));

	// prepare for graph-cuts on GPU
	BufferForBackgroundSubtraction buffer;

	//cv::cuda::GpuMat leftTransp(rightTransp.size(), CV_32SC1, 0);
	//cv::cuda::GpuMat top(bottom.size(), CV_32SC1 ,0);

	buffer.terminals.upload(diff);
	buffer.leftTransp.upload(leftTransp);
	buffer.rightTransp.upload(rightTransp);
	buffer.top.upload(top);
	buffer.bottom.upload(bottom);

	// run graph-cuts
	std::cout << "run graph-cuts ..." << std::endl;
	{
		const int64 start = cv::getTickCount();

		// performs labeling via graph cuts of a 2D regular 4-connected graph
		cv::cuda::graphcut(buffer.terminals, buffer.leftTransp, buffer.rightTransp, buffer.top, buffer.bottom, buffer.labels, buffer.buf);
		cv::cuda::Stream stream;
		//cv::cuda::graphcut(buffer.terminals, buffer.leftTransp, buffer.rightTransp, buffer.top, buffer.bottom, buffer.labels, buffer.buf, stream);

		const int64 elapsed = cv::getTickCount() - start;
		const double freq = cv::getTickFrequency();
		const double etime = elapsed * 1000.0 / freq;
		const double fps = freq / elapsed;
		std::cout << std::setprecision(4) << "elapsed time: " << etime <<  ", FPS: " << fps << std::endl;
	}

	//
	cv::imwrite(diff_filename, diff);
	cv::imwrite(rightTransp_filename, rightTransp);
	cv::imwrite(bottom_filename, bottom);

	const cv::Mat label(buffer.labels);
	cv::imwrite(result_filename, label);

	cv::Mat label_visualized = cv::Mat::zeros(label.size(), CV_8UC1);
	cv::threshold(label, label_visualized, 0, 255, cv::THRESH_BINARY);
	cv::imwrite(result_visualized_filename, label_visualized);

	cv::Mat diff_float, diff_visualized = cv::Mat::zeros(diff.size(), CV_8UC1);
	diff.convertTo(diff_float, CV_32FC1);
	cv::threshold(diff_float, diff_visualized, 0, 255, cv::THRESH_BINARY);
	cv::imwrite(diff_visualized_filename, diff_visualized);
}

void belief_propagation()
{
	throw std::runtime_error("Not yet implemented");
}

}  // namespace local
}  // unnamed namespace

namespace my_opencv {

void image_labeling_using_gpu()
{
	local::background_subtraction_by_graph_cut();
	//local::belief_propagation();  // Not yet implemented.
}

}  // namespace my_opencv
