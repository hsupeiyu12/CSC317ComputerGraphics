#include "fast_mass_springs_step_sparse.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::SparseMatrix<double>  & M,
  const Eigen::SparseMatrix<double>  & A,
  const Eigen::SparseMatrix<double>  & C,
  const Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
    double w = 1e10;
    int n = V.rows();
    
    Eigen::MatrixXd y;
    y.resize(n, 3);
    
    Eigen::MatrixXd bb;
    bb.resize(n, 3);
    
    Eigen::MatrixXd d;
    d.resize(E.rows(),3);
    
    y = M *(2*Ucur - Uprev)/(delta_t*delta_t) + fext;
    //bb = k * A.transpose() * d + y; // d undefined here
    
    Eigen::RowVector3d V1;
    Eigen::RowVector3d V2;
    
    Unext = Ucur;
    
    for(int iter = 0;iter < 50;iter++)
    {
        // Step 1 (local): Given current values of p determine dij for each spring.
        for (int e=0; e<E.rows(); e++) //each spring e
        {
            double len = r(e);
            V1 = Unext.row(E(e,0));
            V2 = Unext.row(E(e,1));
            d.row(e) = len * (V1-V2).normalized();
        }
        bb = k * A.transpose() * d + y;
        bb += w * C.transpose() * C * V; // penalty method: new b
        
        //Step 2 (global): Given all vectors, find positions that minimize quadratic energy $\tilde{E}$.
        Unext = prefactorization.solve(bb);
      
        //Step 3: if "not satisfied", go to Step 1.
    }
  //////////////////////////////////////////////////////////////////////////////
}
