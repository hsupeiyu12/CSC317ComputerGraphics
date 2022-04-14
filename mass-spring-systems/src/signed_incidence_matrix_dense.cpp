#include "signed_incidence_matrix_dense.h"

void signed_incidence_matrix_dense(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::MatrixXd & A)
{
  //////////////////////////////////////////////////////////////////////////////
    
    A = Eigen::MatrixXd::Zero(E.rows(),n); // edges x vertices
    
    for (int e=0; e<E.rows(); e++){
        int i = E(e,0);
        int j = E(e,1);
        A(e,i) += 1;
        A(e,j) += -1;
    }
    
  //////////////////////////////////////////////////////////////////////////////
}
