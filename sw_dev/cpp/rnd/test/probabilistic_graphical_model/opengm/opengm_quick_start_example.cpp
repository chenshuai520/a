#include <opengm/opengm.hxx>
#include <opengm/graphicalmodel/graphicalmodel.hxx>
#include <opengm/operations/minimizer.hxx>
#include <opengm/operations/adder.hxx>
#include <opengm/inference/icm.hxx>


namespace {
namespace local {

}  // namespace local
}  // unnamed namespace

namespace my_opengm {

// REF [file] >> ${OPENGM_HOME}/src/examples/unsorted-examples/quick_start.cxx
void quick_start_example()
{
	// Construct a graphical model with 
	// - 5 variables with { 5, 5, 2, 2, 10 } labels.
	// - addition as the operation (template parameter Adder).
	typedef opengm::GraphicalModel<float, opengm::Adder> Model;

	const std::size_t numsOfLabels[] = { 5, 5, 2, 2, 10 };
	Model gm(opengm::DiscreteSpace<>(numsOfLabels, numsOfLabels + 5));

	typedef opengm::ExplicitFunction<float> ExplicitFunction;
	typedef Model::FunctionIdentifier FunctionIdentifier;

	// Local model.
	// Add 1st order functions and factors to the model.
	for (std::size_t variable = 0; variable < gm.numberOfVariables(); ++variable)
	{
		// Construct 1st order function.
		const std::size_t shape[] = { gm.numberOfLabels(variable) };
		ExplicitFunction func1(shape, shape + 1);
		for (std::size_t state = 0; state < gm.numberOfLabels(variable); ++state)
			func1(state) = float(std::rand()) / RAND_MAX;  // random toy data

		// Add function.
		const FunctionIdentifier fid1 = gm.addFunction(func1);

		// Add factor.
		const std::size_t variableIndex[] = { variable };
		gm.addFactor(fid1, variableIndex, variableIndex + 1);
	}

	// 3-wise interaction.
	// Add 3rd order functions and factors to the model.
	for (std::size_t variable1 = 0; variable1 < gm.numberOfVariables(); ++variable1)
		for (std::size_t variable2 = variable1 + 1; variable2 < gm.numberOfVariables(); ++variable2)
			for (std::size_t variable3 = variable2 + 1; variable3 < gm.numberOfVariables(); ++variable3)
			{
				const std::size_t shape[] = {
					gm.numberOfLabels(variable1),
					gm.numberOfLabels(variable2),
					gm.numberOfLabels(variable3)
				};

				// Construct 3rd order function.
				ExplicitFunction func3(shape, shape + 3);
				for (std::size_t state1 = 0; state1 < gm.numberOfLabels(variable1); ++state1)
					for (std::size_t state2 = 0; state2 < gm.numberOfLabels(variable2); ++state2)
						for (std::size_t state3 = 0; state3 < gm.numberOfLabels(variable3); ++state3)      
							func3(state1, state2, state3) = float(std::rand()) / RAND_MAX;  // random toy data.

				const FunctionIdentifier fid3 = gm.addFunction(func3);

				// Sequences of variable indices need to be (and in this case are) sorted.
				const std::size_t variableIndexSequence[] = { variable1, variable2, variable3 };
				gm.addFactor(fid3, variableIndexSequence, variableIndexSequence + 3);
			}

	// Set up the optimizer (ICM).
	typedef opengm::ICM<Model, opengm::Minimizer> IcmType;
	typedef IcmType::VerboseVisitorType VerboseVisitorType;
	IcmType icm(gm);

	// Obtain the (approximate) argmin.
	VerboseVisitorType verboseVisitor;

	std::cout << "on inferring ..." << std::endl;
	icm.infer(verboseVisitor);

	// Output the (approximate) argmin.
	std::vector<std::size_t> argmin;
	icm.arg(argmin);

	for (std::size_t variable = 0; variable < gm.numberOfVariables(); ++variable)
		std::cout << "var" << variable << "=" << argmin[variable] << std::endl;
}

}  // namespace my_opengm
