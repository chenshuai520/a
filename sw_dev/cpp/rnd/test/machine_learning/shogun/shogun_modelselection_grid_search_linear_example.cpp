//#include "stdafx.h"
#include <shogun/base/init.h>
#include <shogun/lib/config.h>
#include <shogun/evaluation/CrossValidation.h>
#include <shogun/evaluation/ContingencyTableEvaluation.h>
#include <shogun/evaluation/StratifiedCrossValidationSplitting.h>
#include <shogun/modelselection/GridSearchModelSelection.h>
#include <shogun/modelselection/ModelSelectionParameters.h>
#include <shogun/modelselection/ParameterCombination.h>
#include <shogun/labels/BinaryLabels.h>
#include <shogun/features/DenseFeatures.h>
#include <shogun/classifier/svm/LibLinear.h>


namespace {
namespace local {

shogun::CModelSelectionParameters * create_param_tree()
{
	shogun::CModelSelectionParameters *root = new shogun::CModelSelectionParameters();

	shogun::CModelSelectionParameters *c1 = new shogun::CModelSelectionParameters("C1");
	root->append_child(c1);
	c1->build_values(-2.0, 2.0, R_EXP);

	shogun::CModelSelectionParameters *c2 = new shogun::CModelSelectionParameters("C2");
	root->append_child(c2);
	c2->build_values(-2.0, 2.0, R_EXP);

	return root;
}

}  // namespace local
}  // unnamed namespace

namespace my_shogun {

using namespace shogun;

// [ref] ${SHOGUN_HOME}/examples/undocumented/libshogun/modelselection_grid_search_linear.cpp
void modelselection_grid_search_linear_example()
{
#ifdef HAVE_LAPACK
	const int32_t num_subsets = 5;
	const int32_t num_vectors = 11;

	// create some data
	shogun::SGMatrix<float64_t> matrix(2, num_vectors);
	for (int32_t i = 0; i < num_vectors * 2; ++i)
		matrix.matrix[i] = i;

	// create num_feautres 2-dimensional vectors
	shogun::CDenseFeatures<float64_t> *features = new shogun::CDenseFeatures<float64_t>(matrix);

	// create three labels
	shogun::CBinaryLabels *labels = new shogun::CBinaryLabels(num_vectors);
	for (index_t i = 0; i < num_vectors; ++i)
		labels->set_label(i, i % 2 == 0 ? 1 : -1);

	// create linear classifier (use -s 2 option to avoid warnings)
	shogun::CLibLinear *classifier = new shogun::CLibLinear(L2R_L2LOSS_SVC);

	// splitting strategy
	shogun::CStratifiedCrossValidationSplitting *splitting_strategy = new shogun::CStratifiedCrossValidationSplitting(labels, num_subsets);

	// accuracy evaluation
	shogun::CContingencyTableEvaluation *evaluation_criterium = new shogun::CContingencyTableEvaluation(ACCURACY);

	// cross validation class for evaluation in model selection
	shogun::CCrossValidation *cross = new shogun::CCrossValidation(classifier, features, labels, splitting_strategy, evaluation_criterium);

	// print all parameter available for modelselection
	// Dont worry if yours is not included, simply write to the mailing list
	classifier->print_modsel_params();

	// model parameter selection, deletion is handled by modsel class (SG_UNREF)
	shogun::CModelSelectionParameters *param_tree = local::create_param_tree();
	param_tree->print_tree();

	// handles all of the above structures in memory
	shogun::CGridSearchModelSelection *grid_search = new CGridSearchModelSelection(param_tree, cross);

	// set autolocking to false to get rid of warnings
	cross->set_autolock(false);

	shogun::CParameterCombination *best_combination = grid_search->select_model();
	SG_SPRINT("best parameter(s):\n");
	best_combination->print_tree();

	best_combination->apply_to_machine(classifier);
	shogun::CCrossValidationResult *result = (shogun::CCrossValidationResult *)cross->evaluate();

	if (result->get_result_type() != CROSSVALIDATION_RESULT)
		SG_SERROR("Evaluation result is not of type CCrossValidationResult!");

	result->print_result();

	// clean up
	SG_UNREF(result);
	SG_UNREF(best_combination);
	SG_UNREF(grid_search);
#endif // HAVE_LAPACK
}

}  // namespace my_shogun
