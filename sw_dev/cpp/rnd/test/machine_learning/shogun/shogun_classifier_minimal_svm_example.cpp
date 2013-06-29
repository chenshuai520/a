//#include "stdafx.h"
#include <shogun/labels/BinaryLabels.h>
#include <shogun/features/DenseFeatures.h>
#include <shogun/kernel/GaussianKernel.h>
#include <shogun/classifier/svm/LibSVM.h>
#include <shogun/base/init.h>
#include <shogun/lib/common.h>
#include <shogun/io/SGIO.h>


namespace {
namespace local {

}  // namespace local
}  // unnamed namespace

namespace my_shogun {

using namespace shogun;

// [ref] ${SHOGUN_HOME}/examples/undocumented/libshogun/classifier_minimal_svm.cpp
void classifier_minimal_svm_example()
{
	// create some data
	shogun::SGMatrix<float64_t> matrix(2, 3);
	for (int32_t i = 0; i < 6; ++i)
		matrix.matrix[i] = i;

	// create three 2-dimensional vectors 
	// shogun will now own the matrix created
	shogun::CDenseFeatures<float64_t> *features = new shogun::CDenseFeatures<float64_t>();
	features->set_feature_matrix(matrix);

	// create three labels
	shogun::CBinaryLabels *labels = new shogun::CBinaryLabels(3);
	labels->set_label(0, -1);
	labels->set_label(1, +1);
	labels->set_label(2, -1);

	// create gaussian kernel with cache 10MB, width 0.5
	shogun::CGaussianKernel *kernel = new shogun::CGaussianKernel(10, 0.5);
	kernel->init(features, features);

	// create libsvm with C=10 and train
	shogun::CLibSVM *svm = new shogun::CLibSVM(10, kernel, labels);
	svm->train();

	// classify on training examples
	for (int32_t i = 0; i < 3; ++i)
		SG_SPRINT("output[%d] = %f\n", i, svm->apply_one(i));

	// free up memory
	SG_UNREF(svm);
}

}  // namespace my_shogun
