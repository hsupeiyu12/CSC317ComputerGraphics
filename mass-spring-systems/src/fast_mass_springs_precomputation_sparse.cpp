#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
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
    std::vector<Eigen::Triplet<double> > M_ijv;
    M.resize(V.rows(),V.rows());
    for (int row=0; row<n; row++){
        M_ijv.emplace_back(row,row,m(row));
    }
    M.setFromTriplets(M_ijv.begin(),M_ijv.end());
    
    // Calculate A
    signed_incidence_matrix_sparse(n,E,A);
    
    // Calculate C
    std::vector<Eigen::Triplet<double> > C_ijv;
    C.resize(b.rows(),V.rows());
    for (int row=0; row<b.rows(); row++){
        C_ijv.emplace_back(row,b(row),1.0);
    }
    C.setFromTriplets(C_ijv.begin(),C_ijv.end());
    
    double w = 1e10;
    Eigen::SparseMatrix<double> Q(n,n);
    Q = (k * A.transpose() * A) + (M / (delta_t*delta_t))
        + w * C.transpose() * C;
    
    
    /////////////////////////////////////////////////////////////////////////////
    prefactorization.compute(Q);
    return prefactorization.info() != Eigen::NumericalIssue;

}
