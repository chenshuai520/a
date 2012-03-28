//#include "stdafx.h"
#include "umdhmm_nrutil.h"
#include "umdhmm_hmm.h"
#include <iostream>
#include <stdexcept>


namespace {
namespace local {

// [ref] umdhmm (http://www.kanungo.com/software/software.html#umdhmm)
//	genseq.c
void hmm_with_discrete_multinomial_observations__sample_umdhmm()
{
	umdhmm::HMM hmm;

	{
#if 1
		hmm.N = 3;  // the number of hidden states
		hmm.M = 2;  // the number of symbols(observations)
		const double A[] = {
			0.9,  0.05, 0.05,
			0.45, 0.1,  0.45,
			0.45, 0.45, 0.1
		};
		const double B[] = {
			0.5,   0.5,
			0.75,  0.25,
			0.25,  0.75
		};
		const double pi[] = {
			0.333, 0.333, 0.333
		};
#else
		hmm.N = 3;  // the number of hidden states
		hmm.M = 2;  // the number of symbols(observations)
		const double A[] = {
			0.5, 0.2,  0.2,
			0.2, 0.4,  0.4,
			0.1, 0.45, 0.45
		};
		const double B[] = {
			0.5,   0.5,
			0.75,  0.25,
			0.25,  0.75
		};
		const double pi[] = {
			0.333, 0.333, 0.333
		};
#endif

		hmm.A = (double **)umdhmm::dmatrix(1, hmm.N, 1, hmm.N);
		const double *ptr = A;
		for (int i = 1; i <= hmm.N; ++i)
		{
			for (int j = 1; j <= hmm.N; ++j, ++ptr)
				hmm.A[i][j] = *ptr;
		}

		hmm.B = (double **)umdhmm::dmatrix(1, hmm.N, 1, hmm.M);
		ptr = B;
		for (int j = 1; j <= hmm.N; ++j)
		{
			for (int k = 1; k <= hmm.M; ++k, ++ptr)
				hmm.B[j][k] = *ptr;
		}

		hmm.pi = (double *)umdhmm::dvector(1, hmm.N);
		ptr = pi;
		for (int i = 1; i <= hmm.N; ++i, ++ptr)
			hmm.pi[i] = *ptr;
	}

	// set random number generator seed
	const int seed = umdhmm::hmmgetseed();

	std::cout << "Random seed = " << seed << std::endl;

	//
	const int T = 100;  // length of observation sequence, T

	int	*O = umdhmm::ivector(1,T);  // alloc space for observation sequence O[1..T]
	int	*q = umdhmm::ivector(1,T);  // alloc space for state sequence q[1..T]

	umdhmm::GenSequenceArray(&hmm, seed, T, O, q);

	//
	umdhmm::PrintSequence(stdout, T, O);

	//
	umdhmm::free_ivector(O, 1, T);
	umdhmm::free_ivector(q, 1, T);
	umdhmm::FreeHMM(&hmm);
}

}  // namespace local
}  // unnamed namespace

void hmm_sample()
{
    local::hmm_with_discrete_multinomial_observations__sample_umdhmm();
}
