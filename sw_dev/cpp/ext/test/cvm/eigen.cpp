#include <cvm/cvm.h>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void eigen_srmatirx();
void eigen_srsmatirx();

void eigen()
{
	eigen_srmatirx();
	eigen_srsmatirx();
}

void eigen_srmatirx()
{
	try
	{
		const int dim = 2;

		cvm::srmatrix m(dim);
		cvm::scmatrix eigvec_r(dim);
		cvm::cvector eigval(dim);
/*
		m(1,1) = 0.1; m(1,2) = 0.2; m(1,3) = 0.1;
		m(2,1) = 0.11; m(2,2) = -2.9; m(2,3) = -8.4;
		m(3,1) = 0.; m(3,2) = 2.91; m(3,3) = 8.2;
*/
		m(1,1) = 1.0; m(1,2) = 4.0;
		m(2,1) = 9.0; m(2,2) = 1.0;
		std::cout << m;
		for (cvm::srmatrix::iterator it = m.begin(); it != m.end(); ++it)
			std::cout << *it << ", ";
		std::cout << std::endl;
		for (int col = 1; col <= m.nsize(); ++col) {
			cvm::rvector colvec = m(col);
			std::cout << col << "-th col: ";
			for (cvm::rvector::iterator it = colvec.begin(); it != colvec.end(); ++it)
				std::cout << *it << ", ";
			std::cout << std::endl;
		}
		std::cout << std::endl;

		eigval = m.eig(eigvec_r, true);
		std::cout << eigval << std::endl;
		std::cout << eigvec_r << std::endl;

		cvm::srmatrix eigvec2_r(eigvec_r.real());
		eigvec2_r(1) /= eigvec2_r(1).norm();
		eigvec2_r(2) /= eigvec2_r(2).norm();
		std::cout << eigvec2_r;
	}
	catch (const cvm::cvmexception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void eigen_srsmatirx()
{
	try
	{
		const int row_dim = 2, col_dim = 3;

		cvm::rmatrix m(row_dim, col_dim);
		cvm::srsmatrix eigvec_r(row_dim);
		cvm::rvector eigval(row_dim);

		m(1,1) = 1.0; m(1,2) = 4.0; m(1,3) = 2.0;
		m(2,1) = 9.0; m(2,2) = 1.0; m(2,3) = 1.0;
		std::cout << m << std::endl;

		eigval = cvm::srsmatrix(m * ~m).eig(eigvec_r);
		std::cout << eigval << std::endl;
		std::cout << eigvec_r << std::endl;

	}
	catch (const cvm::cvmexception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
}