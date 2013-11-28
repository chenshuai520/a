										//#include "stdafx.h"
#define CV_NO_BACKWARD_COMPATIBILITY
#include <opencv2/opencv.hpp>
#include <boost/timer/timer.hpp>
#include <iostream>
#include <fstream>


namespace my_opencv {

void normalize_histogram(cv::MatND &hist, const double factor);

}  // namespace my_opencv

namespace {
namespace local {

void histogram_comparison()
{
	const double arr01[] = { 2.5906700e+00, 1.2953400e+00, 6.4766800e+00, 0.0000000e+00, 0.0000000e+00, 3.8860100e+00, 2.5906700e+00, 0.0000000e+00, 0.0000000e+00, 3.8860100e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 2.5906700e+00, 3.8860100e+00, 0.0000000e+00, 3.8860100e+00, 2.5906700e+00, 1.2953400e+00, 5.1813500e+00, 1.2953400e+00, 2.5906700e+00, 1.2953400e+00, 5.1813500e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 2.5906700e+00, 0.0000000e+00, 1.2953400e+00, 2.5906700e+00, 0.0000000e+00, 2.5906700e+00, 2.5906700e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 1.2953400e+00, 0.0000000e+00, 2.5906700e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 2.5906700e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 2.5906700e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 1.2953400e+00, 1.2953400e+00, 5.1813500e+00, 2.5906700e+00, 5.1813500e+00, 7.7720200e+00, 6.4766800e+00, 2.5906700e+00, 5.1813500e+00, 2.5906700e+00, 6.4766800e+00, 6.4766800e+00, 5.1813500e+00, 2.5906700e+00, 7.7720200e+00, 9.0673600e+00, 6.4766800e+00, 2.0725400e+01, 1.2953400e+01, 1.5544000e+01, 1.1658000e+01, 2.0725400e+01, 1.1658000e+01, 1.2953400e+01, 1.8134700e+01, 1.6839400e+01, 1.5544000e+01, 2.4611400e+01, 1.4248700e+01, 1.4248700e+01, 1.5544000e+01, 1.6839400e+01, 1.0362700e+01, 7.7720200e+00, 9.0673600e+00, 3.8860100e+00, 5.1813500e+00, 7.7720200e+00, 2.5906700e+00, 2.5906700e+00, 3.8860100e+00 };
	const double arr02[] = { 4.2949200e+00, 2.1474600e+00, 1.0737300e+00, 3.5791000e-01, 4.2949200e+00, 1.0737300e+00, 1.0737300e+00, 7.1582000e-01, 0.0000000e+00, 1.0737300e+00, 3.5791000e-01, 7.1582000e-01, 1.4316400e+00, 3.5791000e-01, 1.7895500e+00, 7.1582000e-01, 3.5791000e-01, 3.5791000e-01, 7.1582000e-01, 3.5791000e-01, 1.0737300e+00, 0.0000000e+00, 7.1582000e-01, 3.5791000e-01, 0.0000000e+00, 7.1582000e-01, 3.5791000e-01, 0.0000000e+00, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 7.1582000e-01, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 1.0737300e+00, 3.5791000e-01, 7.1582000e-01, 7.1582000e-01, 3.5791000e-01, 1.4316400e+00, 3.5791000e-01, 1.0737300e+00, 1.4316400e+00, 1.0737300e+00, 1.7895500e+00, 1.4316400e+00, 1.7895500e+00, 1.7895500e+00, 2.5053700e+00, 2.1474600e+00, 2.8632800e+00, 2.5053700e+00, 2.1474600e+00, 2.5053700e+00, 1.7895500e+00, 3.9370100e+00, 2.5053700e+00, 3.2211900e+00, 3.5791000e+00, 3.5791000e+00, 4.6528300e+00, 5.3686500e+00, 4.2949200e+00, 2.1474600e+00, 1.4316400e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 3.5791000e-01, 7.1582000e-01, 3.9370100e+00, 2.1474600e+00, 4.2949200e+00, 2.1474600e+00, 1.4316400e+00, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 0.0000000e+00, 3.5791000e-01, 0.0000000e+00, 7.1582000e-01, 3.5791000e-01, 1.0737300e+00, 7.1582000e-01, 0.0000000e+00, 3.5791000e-01, 3.5791000e-01, 3.5791000e-01, 1.0737300e+00, 3.5791000e-01, 1.4316400e+00, 3.5791000e-01, 1.0737300e+00, 3.5791000e-01, 1.0737300e+00, 7.1582000e-01, 1.0737300e+00, 1.0737300e+00, 1.0737300e+00, 3.2211900e+00, 1.4316400e+00, 1.4316400e+00, 1.0737300e+00, 1.0737300e+00, 1.7895500e+00, 3.2211900e+00, 1.4316400e+00, 1.7895500e+00, 2.1474600e+00, 2.1474600e+00, 3.2211900e+00, 2.1474600e+00, 2.1474600e+00, 2.8632800e+00, 3.9370100e+00, 2.8632800e+00, 4.2949200e+00, 6.4423800e+00, 2.2548300e+01, 1.2168900e+01, 6.4423800e+00, 3.9370100e+00, 6.4423800e+00, 4.6528300e+00, 4.6528300e+00, 6.4423800e+00, 3.5791000e+00, 5.7265600e+00, 6.0844700e+00, 4.2949200e+00, 6.4423800e+00, 6.4423800e+00, 6.8002900e+00, 8.2319300e+00, 1.1095200e+01, 1.3600600e+01, 1.5032200e+01, 3.0064400e+01, 4.4022900e+01, 2.8632800e+01, 2.0042900e+01, 1.9685000e+01, 5.0107400e+00, 6.8002900e+00, 8.2319300e+00, 8.5898400e+00 };

	cv::Mat histo1, histo2;
	cv::Mat(1, 360, CV_64FC1, (void *)arr01).convertTo(histo1, CV_32FC1, 1.0, 0.0);
	cv::Mat(1, 360, CV_64FC1, (void *)arr02).convertTo(histo2, CV_32FC1, 1.0, 0.0);

	std::cout << "distances between two histograms:" << std::endl;
	double dist;

	{
		boost::timer::auto_cpu_timer timer;
		// correlation: better match has higher score - perfect match = 1.0, total mismatch = -1.0.
		dist = cv::compareHist(histo1, histo2, CV_COMP_CORREL);
	}
	std::cout << "\tCorrelation:   " << dist << std::endl;

	{
		boost::timer::auto_cpu_timer timer;
		// chi-square: better match has lower score - perfect match = 0.0, mismatch > 0.0.
		dist = cv::compareHist(histo1, histo2, CV_COMP_CHISQR);
	}
	std::cout << "\tChi-Square:    " << dist << std::endl;

	{
		boost::timer::auto_cpu_timer timer;
		// histogram intersection: better match has higher score - perfect match = 1.0, total mismatch = 0.0 if two histograms are normalized to 1.
		dist = cv::compareHist(histo1, histo2, CV_COMP_INTERSECT);
	}
	std::cout << "\tIntersection:  " << dist << std::endl;

	{
		boost::timer::auto_cpu_timer timer;
		// Bhattacharyya: better match has lower score - perfect match = 0.0, total mismatch = 1.0 (???).
		dist = cv::compareHist(histo1, histo2, CV_COMP_BHATTACHARYYA);
	}
	std::cout << "\tBhattacharyya: " << dist << std::endl;
}

// [ref] histogram_2D() in opencv_histogram().
void compute_histogram(const cv::Mat &src, cv::Mat &histo, const int h_bins, const int s_bins)
{
	// create images.
	cv::Mat hsv;
	cv::cvtColor(src, hsv, CV_BGR2HSV);

	// calculate histogram.
	const int dims = 2;
	// let's quantize the hue to 30 levels and the saturation to 32 levels.
	const int bins1 = h_bins, bins2 = s_bins;
	const int histSize[] = { bins1, bins2 };
	// hue varies from 0 to 179, see cvtColor.
	const float range1[] = { 0, 180 };
	// saturation varies from 0 (black-gray-white) to 255 (pure spectrum color).
	const float range2[] = { 0, 256 };
	const float *ranges[] = { range1, range2 };
	// we compute the histogram from the 0th and 1st channels.
	const int channels[] = { 0, 1 };

#if 1
	//cv::MatND histo;  // return type: CV_32FC1, 2-dim (rows = bins1, cols = bins2).
	cv::calcHist(
		&hsv, 1, channels, cv::Mat(), // do not use mask.
		histo, dims, histSize, ranges,
		true, // the histogram is uniform.
		false
	);
#else
	const int interval1 = (range1[1] - range1[0]) / bins1;
	const int interval2 = (range2[1] - range2[0]) / bins2;

	//cv::MatND histo(cv::MatND::zeros(bins1, bins2, CV_32F));
	histo = cv::MatND::zeros(bins1, bins2, CV_32F);
	const unsigned char *imgPtr = (unsigned char *)hsv.data;
	float *binPtr = (float *)histo.data;
	for (int i = 0; i < hsv.rows * hsv.cols; ++i, imgPtr += 3)
	{
		const int idx1 = (imgPtr[channels[0]] - range1[0]) / interval1;
		const int idx2 = (imgPtr[channels[1]] - range2[0]) / interval2;
		++*(binPtr + idx1 * histo.cols + idx2);
	}
#endif

	// normalize histogram.
	const double factor = 1.0;
	my_opencv::normalize_histogram(histo, factor);
}

void compute_signature(const cv::Mat &THoG, const std::size_t dims, const std::size_t num_features, const std::size_t num_frames, cv::Mat &sig)
{
	sig.setTo(0.0f);
	for (std::size_t i = 0; i < num_features; ++i)
		for (std::size_t j = 0; j < num_frames; ++j)
		{
			const float weight = THoG.at<float>(i, j);
			if (weight > 0.0)
			{
				sig.at<float>(i * num_frames + j, 0) = weight;  // bin value (weight).
				sig.at<float>(i * num_frames + j, 1) = (float)i;  // coord 1.
				sig.at<float>(i * num_frames + j, 2) = (float)j;  // coord 2.

#if 0
				// for debugging.
				std::cout << '(' << i << ", " << j << ") : " << weight << std::endl;
#endif
			}
		}
}

void earth_movers_distance()
{
#if 1
	const std::string img1_filename("./data/machine_vision/opencv/lena_rgb.bmp");
	const std::string img2_filename("./data/machine_vision/opencv/lena_rgb.bmp");
	//const std::string img2_filename("./data/machine_vision/opencv/lena_gray.bmp");
#elif 0
	const std::string img1_filename("./data/machine_vision/teddy-imL.png");
	//const std::string img2_filename("./data/machine_vision/teddy-imL.png");
	const std::string img2_filename("./data/machine_vision/teddy-imR.png");
#endif

	// load images.
	const cv::Mat &img1 = cv::imread(img1_filename, CV_LOAD_IMAGE_COLOR);
	if (img1.empty())
	{
		std::cerr << "image file not found: " << img1_filename << std::endl;
		return;
	}
	const cv::Mat &img2 = cv::imread(img2_filename, CV_LOAD_IMAGE_COLOR);
	if (img2.empty())
	{
		std::cerr << "image file not found: " << img2_filename << std::endl;
		return;
	}

	// compute histograms.
	const std::size_t dims = 2;
	const int h_bins = 30;
	const int s_bins = 32;

	cv::Mat histo1, histo2;
	compute_histogram(img1, histo1, h_bins, s_bins);
	compute_histogram(img2, histo2, h_bins, s_bins);

	// create matrices to store signature in.
	// (histogram's size) x (histogram's dim. + 1) floating-point matrix.
	//	in case of 1D, (histogram's size) = (bin size), (histogram's dim. + 1) = 1 count(bin value) + 1 coords = 2.
	//	in case of 2D, (histogram's size) = (row's bin size) x (col's bin size), (histogram's dim. + 1) = 1 count(bin value) + 2 coords = 3.
#if 0
	// fill signatures for the two histograms.
	const int num_rows = h_bins * s_bins;
	cv::Mat sig1(num_rows, dims + 1, CV_32FC1, cv::Scalar::all(0.0f)), sig2(num_rows, dims + 1, CV_32FC1, cv::Scalar::all(0.0f));
	for (int h = 0; h < h_bins; ++h)
		for (int s = 0; s < s_bins; ++s)
		{
			const float weight1 = histo1.at<float>(h, s);
			if (weight1 > 0.0)
			{
				sig1.at<float>(h * s_bins + s, 0) = weight1;  // bin value (weight).
				sig1.at<float>(h * s_bins + s, 1) = (float)h;  // coord 1.
				sig1.at<float>(h * s_bins + s, 2) = (float)s;  // coord 2.
			}

			const float weight2 = histo2.at<float>(h, s);
			if (weight2 > 0.0)
			{
				sig2.at<float>(h * s_bins + s, 0) = weight2;  // bin value (weight).
				sig2.at<float>(h * s_bins + s, 1) = (float)h;  // coord 1.
				sig2.at<float>(h * s_bins + s, 2) = (float)s;  // coord 2.
			}
		}

	float dist;
	{
		boost::timer::auto_cpu_timer timer;
		// better match has lower score - perfect match = 0.0, total mismatch = 1.0(?).
		dist = cv::EMD(sig1, sig2, CV_DIST_L2);
	}
	std::cout << "earth mover's distance between two histograms: " << dist << std::endl;
#elif 1
	// fill signatures for the two histograms (partial matching).
	cv::Mat sig1(h_bins * s_bins, dims + 1, CV_32FC1, cv::Scalar::all(0.0f));
	for (int h = 0; h < h_bins; ++h)
		for (int s = 0; s < s_bins; ++s)
		{
			const float weight1 = histo1.at<float>(h, s);
			if (weight1 > 0.0)
			{
				sig1.at<float>(h * s_bins + s, 0) = weight1;  // bin value (weight).
				sig1.at<float>(h * s_bins + s, 1) = (float)h;  // coord 1.
				sig1.at<float>(h * s_bins + s, 2) = (float)s;  // coord 2.

#if 0
				// for debugging.
				std::cout << '(' << h << ", " << s << ") : " << weight1 << std::endl;
#endif
			}
		}
	const int s_bin_size = 15;
	for (int kk = 0; kk <= s_bins - s_bin_size; ++kk)
	{
		const int s_bin_start = kk, s_bin_end = kk + s_bin_size - 1;

        cv::Mat histo2_partial(histo2.rows, s_bin_size, histo2.type());
		histo2.colRange(s_bin_start, s_bin_end + 1).copyTo(histo2_partial);

		// re-normalize histogram.
		my_opencv::normalize_histogram(histo2_partial, 1.0);

		cv::Mat sig2(h_bins * s_bin_size, dims + 1, CV_32FC1, cv::Scalar::all(0.0f));
		for (int h = 0; h < h_bins; ++h)
			for (int s = s_bin_start; s <= s_bin_end && s < s_bins; ++s)
			{
				const float weight2 = histo2_partial.at<float>(h, s - s_bin_start);
				if (weight2 > 0.0)
				{
					sig2.at<float>(h * s_bin_size + s - s_bin_start, 0) = weight2;  // bin value (weight).
					sig2.at<float>(h * s_bin_size + s - s_bin_start, 1) = (float)h;  // coord 1.
					sig2.at<float>(h * s_bin_size + s - s_bin_start, 2) = (float)s;  // coord 2.
					//sig2.at<float>(h * s_bin_size + s - s_bin_start, 2) = (float)(s - s_bin_start);  // coord 2.

#if 0
					// for debugging.
					std::cout << '(' << h << ", " << s << ") : " << weight2 << std::endl;
#endif
				}
			}

		float dist;
		{
			boost::timer::auto_cpu_timer timer;
			// better match has lower score - perfect match = 0.0, total mismatch = 1.0(?).
			dist = cv::EMD(sig1, sig2, CV_DIST_L2);
		}
		std::cout << "earth mover's distance between two histograms: " << dist << std::endl;
	}
#endif
}

void earth_movers_distance_applied_to_THoG_using_full_reference_THoG()
{
	std::vector<std::string> filename_list;
	filename_list.push_back("E:/dataset/motion/ChaLearn_Gesture_Challenge_dataset/quasi_lossless_format/train_data/devel16_thog2_1deg_segmented/M_1_1.HoG");
	filename_list.push_back("E:/dataset/motion/ChaLearn_Gesture_Challenge_dataset/quasi_lossless_format/train_data/devel16_thog2_1deg_segmented/M_2_1.HoG");
	filename_list.push_back("E:/dataset/motion/ChaLearn_Gesture_Challenge_dataset/quasi_lossless_format/train_data/devel16_thog2_1deg_segmented/M_4_1.HoG");
	filename_list.push_back("E:/dataset/motion/ChaLearn_Gesture_Challenge_dataset/quasi_lossless_format/train_data/devel16_thog2_1deg_segmented/M_7_1.HoG");

	std::vector<cv::Mat> THoG_list;
	THoG_list.reserve(filename_list.size());
	for (std::size_t i = 0; i < filename_list.size(); ++i)
	{
		// read HoG.
		std::vector<std::vector<float> > data;
		{
			std::ifstream strm(filename_list[i]);

			std::string str;
			std::vector<float> record;
			while (strm)
			{
				if (!std::getline(strm, str)) break;

				record.clear();

				std::istringstream sstrm(str);
				while (sstrm)
				{
					if (!std::getline(sstrm, str, ',')) break;
					record.push_back((float)strtod(str.c_str(), NULL));
				}

				data.push_back(record);
			}

			if (!strm.eof())
			{
				std::cerr << "Fooey!" << std::endl;
			}
		}

		//
		const std::size_t gesture_id = std::size_t(data[0][0]);
		const std::size_t num_features = std::size_t(data[1][0]);
		const std::size_t num_frames = std::size_t(data[1][1]);

		cv::Mat THoG(num_features, num_frames, CV_32FC1);
		for (std::size_t i = 2; i < data.size(); ++i)
			for (std::size_t j = 0; j < data[i].size(); ++j)
				THoG.at<float>(i - 2, j) = data[i][j];

		my_opencv::normalize_histogram(THoG, 1.0);

		// TODO [check] >> zero histogram is treated as an uniform distribution.
		const cv::Scalar sums(cv::sum(THoG));
		const double eps = 1.0e-20;
		if (std::fabs(sums[0]) < eps) THoG = cv::Mat::ones(THoG.size(), THoG.type());

		THoG_list.push_back(THoG);
	}

	// create matrices to store signature in.
	// (histogram's size) x (histogram's dim. + 1) floating-point matrix.
	//	in case of 1D, (histogram's size) = (bin size), (histogram's dim. + 1) = 1 count(bin value) + 1 coords = 2.
	//	in case of 2D, (histogram's size) = (row's bin size) x (col's bin size), (histogram's dim. + 1) = 1 count(bin value) + 2 coords = 3.

	const std::size_t dims = 2;  // THoG is a 2-dim. histogram.
	const int frame_win_size = 15;

	std::vector<std::vector<std::vector<double> > > result(THoG_list.size(), std::vector<std::vector<double> >(THoG_list.size()));
	for (std::size_t tt = 0; tt < THoG_list.size(); ++tt)
	{
		const cv::Mat &THoG1 = THoG_list[tt];
		const int num_features1 = THoG1.rows;
		const int num_frames1 = THoG1.cols;

		// fill signatures for the two THoG's (partial matching).

		// THoG1 is used as a (full) reference THoG.
		cv::Mat sig1(num_features1 * num_frames1, dims + 1, CV_32FC1, cv::Scalar::all(0.0f));
		for (int ii = 0; ii < num_features1; ++ii)
			for (int jj = 0; jj < num_frames1; ++jj)
			{
				const float weight1 = THoG1.at<float>(ii, jj);
				if (weight1 > 0.0)
				{
					sig1.at<float>(ii * num_frames1 + jj, 0) = weight1;  // bin value (weight).
					sig1.at<float>(ii * num_frames1 + jj, 1) = (float)ii;  // coord 1.
					sig1.at<float>(ii * num_frames1 + jj, 2) = (float)jj;  // coord 2.

#if 0
					// for debugging.
					std::cout << '(' << ii << ", " << jj << ") : " << weight1 << std::endl;
#endif
				}
			}

		for (std::size_t uu = 0; uu < THoG_list.size(); ++uu)
		{
			std::cout << '(' << tt << ", " << uu << ") is processing ..." << std::endl;
			boost::timer::auto_cpu_timer timer;

			const cv::Mat &THoG2 = THoG_list[uu];
			const int num_features2 = THoG2.rows;
			const int num_frames2 = THoG2.cols;

			result[tt][uu].resize(num_frames2 - frame_win_size + 1, 0.0);

			for (int ff = 0; ff <= num_frames2 - frame_win_size; ++ff)
			{
				const int frame_start = ff, frame_end = ff + frame_win_size - 1;

		        cv::Mat THoG2_partial(THoG2.rows, frame_win_size, THoG2.type());
				THoG2.colRange(frame_start, frame_end + 1).copyTo(THoG2_partial);

				// TODO [check] >> zero histogram is treated as an uniform distribution.
				const cv::Scalar sums(cv::sum(THoG2_partial));
				const double eps = 1.0e-20;
				if (std::fabs(sums[0]) < eps) THoG2_partial = cv::Mat::ones(THoG2_partial.size(), THoG2_partial.type());

				// re-normalize histogram.
				my_opencv::normalize_histogram(THoG2_partial, 1.0);

				// THoG2 is used as an input THoG.
				cv::Mat sig2(num_features2 * frame_win_size, dims + 1, CV_32FC1, cv::Scalar::all(0.0f));
				for (int ii = 0; ii < num_features2; ++ii)
					for (int jj = frame_start; jj <= frame_end && jj < num_frames2; ++jj)
					{
						const float weight2 = THoG2_partial.at<float>(ii, jj - frame_start);
						if (weight2 > 0.0)
						{
							sig2.at<float>(ii * frame_win_size + jj - frame_start, 0) = weight2;  // bin value (weight).
							sig2.at<float>(ii * frame_win_size + jj - frame_start, 1) = (float)ii;  // coord 1.
							sig2.at<float>(ii * frame_win_size + jj - frame_start, 2) = (float)jj;  // coord 2.
							//sig2.at<float>(ii * frame_win_size + jj - frame_start, 2) = (float)(jj - frame_start);  // coord 2.

#if 0
							// for debugging.
							std::cout << '(' << ii << ", " << jj << ") : " << weight2 << std::endl;
#endif
						}
					}

				// FIXME [delete] >>
				if (tt == THoG_list.size() - 1 && uu == THoG_list.size() - 1)
				{
					const std::string sig1_filename("./data/THoG_sig1.txt");
					const std::string sig2_filename("./data/THoG_sig2.txt");
					std::ofstream stream1(sig1_filename, std::ios::out | std::ios::trunc);
					std::ofstream stream2(sig2_filename, std::ios::out | std::ios::trunc);
					stream1 << sig1 << std::endl;
					stream2 << sig2 << std::endl;
				}

				const float dist = cv::EMD(sig1, sig2, CV_DIST_L2);
				result[tt][uu][ff] = dist;
			}
		}
	}

	//
	std::cout << "earth mover's distance (EMD) test for THoG ..." << std::endl;

#if 1
	const std::string resultant_filename("./data/THoG_EMD_result.txt");
	std::ofstream stream(resultant_filename, std::ios::out | std::ios::trunc);
	if (!stream.is_open())
	{
		std::cerr << "file not found: " << resultant_filename << std::endl;
		return;
	}
#else
	std::ostream stream = std::cout;
#endif

	for (std::size_t i = 0; i < result.size(); ++i)
		for (std::size_t j = 0; j < result[i].size(); ++j)
		{
			for (std::size_t k = 0; k < result[i][j].size(); ++k)
				stream << result[i][j][k] << ", ";
			stream << std::endl;
		}
}

void earth_movers_distance_applied_to_THoG_using_partial_reference_THoG()
{
	std::vector<std::string> filename_list;
	//filename_list.push_back("E:/dataset/motion/ChaLearn_Gesture_Challenge_dataset/quasi_lossless_format/train_data/devel16_thog2_1deg_segmented/M_1_1.HoG");
	//filename_list.push_back("E:/dataset/motion/ChaLearn_Gesture_Challenge_dataset/quasi_lossless_format/train_data/devel16_thog2_1deg_segmented/M_2_1.HoG");
	filename_list.push_back("E:/dataset/motion/ChaLearn_Gesture_Challenge_dataset/quasi_lossless_format/train_data/devel16_thog2_1deg_segmented/M_4_1.HoG");
	//filename_list.push_back("E:/dataset/motion/ChaLearn_Gesture_Challenge_dataset/quasi_lossless_format/train_data/devel16_thog2_1deg_segmented/M_7_1.HoG");

	std::vector<cv::Mat> THoG_list;
	THoG_list.reserve(filename_list.size());
	for (std::size_t i = 0; i < filename_list.size(); ++i)
	{
		// read HoG.
		std::vector<std::vector<float> > data;
		{
			std::ifstream strm(filename_list[i]);

			std::string str;
			std::vector<float> record;
			while (strm)
			{
				if (!std::getline(strm, str)) break;

				record.clear();

				std::istringstream sstrm(str);
				while (sstrm)
				{
					if (!std::getline(sstrm, str, ',')) break;
					record.push_back((float)strtod(str.c_str(), NULL));
				}

				data.push_back(record);
			}

			if (!strm.eof())
			{
				std::cerr << "Fooey!" << std::endl;
			}
		}

		//
		const std::size_t gesture_id = std::size_t(data[0][0]);
		const std::size_t num_features = std::size_t(data[1][0]);
		const std::size_t num_frames = std::size_t(data[1][1]);

		cv::Mat THoG(num_features, num_frames, CV_32FC1);
		for (std::size_t i = 2; i < data.size(); ++i)
			for (std::size_t j = 0; j < data[i].size(); ++j)
				THoG.at<float>(i - 2, j) = data[i][j];

		my_opencv::normalize_histogram(THoG, 1.0);

		// TODO [check] >> zero histogram is treated as an uniform distribution.
		const cv::Scalar sums(cv::sum(THoG));
		const double eps = 1.0e-20;
		if (std::fabs(sums[0]) < eps) THoG = cv::Mat::ones(THoG.size(), THoG.type());

		THoG_list.push_back(THoG);
	}

	// create matrices to store signature in.
	// (histogram's size) x (histogram's dim. + 1) floating-point matrix.
	//	in case of 1D, (histogram's size) = (bin size), (histogram's dim. + 1) = 1 count(bin value) + 1 coords = 2.
	//	in case of 2D, (histogram's size) = (row's bin size) x (col's bin size), (histogram's dim. + 1) = 1 count(bin value) + 2 coords = 3.

	const std::size_t dims = 2;  // THoG is a 2-dim. histogram.
	const int frame_win_size1 = 20;
	const int frame_win_size2 = 15;

	std::vector<std::vector<std::vector<double> > > result(THoG_list.size(), std::vector<std::vector<double> >(THoG_list.size()));
	for (std::size_t tt = 0; tt < THoG_list.size(); ++tt)
	{
		const cv::Mat &THoG1 = THoG_list[tt];
		const int num_features1 = THoG1.rows;
		const int num_frames1 = THoG1.cols;

		// fill signatures for the two THoG's (partial matching).

		for (std::size_t uu = 0; uu < THoG_list.size(); ++uu)
		{
			std::cout << '(' << tt << ", " << uu << ") is processing ..." << std::endl;
			boost::timer::auto_cpu_timer timer;

			const cv::Mat &THoG2 = THoG_list[uu];
			const int num_features2 = THoG2.rows;
			const int num_frames2 = THoG2.cols;

			result[tt][uu].resize(num_frames2 - frame_win_size2 + 1, 0.0);

			for (int ff = 0; ff <= num_frames2 - frame_win_size2; ++ff)
			{
				const int frame_start2 = ff, frame_end2 = ff + frame_win_size2 - 1;

		        cv::Mat THoG2_partial(THoG2.rows, frame_win_size2, THoG2.type());
				THoG2.colRange(frame_start2, frame_end2 + 1).copyTo(THoG2_partial);

				// TODO [check] >> zero histogram is treated as an uniform distribution.
				const cv::Scalar sums(cv::sum(THoG2_partial));
				const double eps = 1.0e-20;
				if (std::fabs(sums[0]) < eps) THoG2_partial = cv::Mat::ones(THoG2_partial.size(), THoG2_partial.type());

				// re-normalize histogram.
				my_opencv::normalize_histogram(THoG2_partial, 1.0);

				// THoG2 is used as an input THoG.
				cv::Mat sig2(num_features2 * frame_win_size2, dims + 1, CV_32FC1, cv::Scalar::all(0.0f));
				for (int ii = 0; ii < num_features2; ++ii)
					for (int jj = frame_start2; jj <= frame_end2 && jj < num_frames2; ++jj)
					{
						const float weight2 = THoG2_partial.at<float>(ii, jj - frame_start2);
						if (weight2 > 0.0)
						{
							sig2.at<float>(ii * frame_win_size2 + jj - frame_start2, 0) = weight2;  // bin value (weight).
							sig2.at<float>(ii * frame_win_size2 + jj - frame_start2, 1) = (float)ii;  // coord 1.
							sig2.at<float>(ii * frame_win_size2 + jj - frame_start2, 2) = (float)jj;  // coord 2.
							//sig2.at<float>(ii * frame_win_size2 + jj - frame_start2, 2) = (float)(jj - frame_start2);  // coord 2.

#if 0
							// for debugging.
							std::cout << '(' << ii << ", " << jj << ") : " << weight2 << std::endl;
#endif
						}
					}

				double bestDist = std::numeric_limits<double>::max();
				for (int gg = 0; gg <= num_frames1 - frame_win_size1; ++gg)
				{
					const int frame_start1 = gg, frame_end1 = gg + frame_win_size1 - 1;

					cv::Mat THoG1_partial(THoG1.rows, frame_win_size1, THoG1.type());
					THoG1.colRange(frame_start1, frame_end1 + 1).copyTo(THoG1_partial);

					// TODO [check] >> zero histogram is treated as an uniform distribution.
					const cv::Scalar sums(cv::sum(THoG1_partial));
					const double eps = 1.0e-20;
					if (std::fabs(sums[0]) < eps) THoG1_partial = cv::Mat::ones(THoG1_partial.size(), THoG1_partial.type());

					// re-normalize histogram.
					my_opencv::normalize_histogram(THoG1_partial, 1.0);

					// THoG1 is used as a (partial) reference THoG.
					cv::Mat sig1(num_features1 * frame_win_size1, dims + 1, CV_32FC1, cv::Scalar::all(0.0f));
					for (int ii = 0; ii < num_features1; ++ii)
						for (int jj = frame_start1; jj <= frame_end1 && jj < num_frames1; ++jj)
						{
							const float weight1 = THoG1_partial.at<float>(ii, jj - frame_start1);
							if (weight1 > 0.0)
							{
								sig1.at<float>(ii * frame_win_size1 + jj - frame_start1, 0) = weight1;  // bin value (weight).
								sig1.at<float>(ii * frame_win_size1 + jj - frame_start1, 1) = (float)ii;  // coord 1.
								sig1.at<float>(ii * frame_win_size1 + jj - frame_start1, 2) = (float)jj;  // coord 2.
								//sig1.at<float>(ii * frame_win_size1 + jj - frame_start1, 2) = (float)(jj - frame_start1);  // coord 2.

	#if 0
								// for debugging.
								std::cout << '(' << ii << ", " << jj << ") : " << weight1 << std::endl;
	#endif
							}
						}

					const float dist = cv::EMD(sig1, sig2, CV_DIST_L2);
					if (dist < bestDist) bestDist = dist;
				}

				result[tt][uu][ff] = bestDist;
			}
		}
	}

	//
	std::cout << "earth mover's distance (EMD) test for THoG ..." << std::endl;

#if 1
	const std::string resultant_filename("./data/THoG_EMD_result.txt");
	std::ofstream stream(resultant_filename, std::ios::out | std::ios::trunc);
	if (!stream.is_open())
	{
		std::cerr << "file not found: " << resultant_filename << std::endl;
		return;
	}
#else
	std::ostream stream = std::cout;
#endif

	for (std::size_t i = 0; i < result.size(); ++i)
		for (std::size_t j = 0; j < result[i].size(); ++j)
		{
			for (std::size_t k = 0; k < result[i][j].size(); ++k)
				stream << result[i][j][k] << ", ";
			stream << std::endl;
		}
}

}  // namespace local
}  // unnamed namespace

namespace my_opencv {

void distance_measure()
{
	//local::histogram_comparison();

	// earth mover's distance.
	//local::earth_movers_distance();
	//local::earth_movers_distance_applied_to_THoG_using_full_reference_THoG();
	local::earth_movers_distance_applied_to_THoG_using_partial_reference_THoG();
}

}  // namespace my_opencv
