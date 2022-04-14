#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////

    int n = V.rows(); // num of vertices
    
    // Calculate r
    r.resize(E.rows());
    Eigen::RowVector3d V1, V2;
    for (int e=0; e<E.rows(); e++){
        int i = E(e,0);
        int j = E(e,1);
        V1 = V.row(i);
        V2 = V.row(j);
        r(e) = (V1 - V2).norm();
    }
    
    // Calculate M
    M = Eigen::MatrixXd::Zero(n,n);
    for (int row=0; row<n; row++){
        M(row,row) += m(row);
    }
    
    // Calculate A
    signed_incidence_matrix_dense(n,E,A);
    
    // Calculate C
    C = Eigen::MatrixXd::Zero(b.rows(),n);
    for (int row=0; row<b.rows(); row++){
        C(row, b(row)) += 1;
    }
    
    double w = 1e10;
    Eigen::MatrixXd Q;
    Q.resize(n,n);
    Q = (k * A.transpose() * A) + (M / (delta_t*delta_t))
        + w * (C.transpose() * C);
    
    
    /////////////////////////////////////////////////////////////////////////////
    prefactorization.compute(Q);
    return prefactorization.info() != Eigen::NumericalIssue;
}
