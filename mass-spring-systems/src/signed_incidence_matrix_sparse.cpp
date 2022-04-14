#include "signed_incidence_matrix_sparse.h"
#include <vector>

void signed_incidence_matrix_sparse(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::SparseMatrix<double>  & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Triplet<double> > ijv;

    for (int e=0; e<E.rows(); e++){
        int i = E(e,0);
        int j = E(e,1);
        ijv.emplace_back(e,i,1.);
        ijv.emplace_back(e,j,-1.);
    }
    A.resize(E.rows(),n);
    A.setFromTriplets(ijv.begin(),ijv.end());
  //////////////////////////////////////////////////////////////////////////////
}
