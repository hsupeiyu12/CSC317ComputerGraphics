#include "Plane.h"
#include "Ray.h"
#include <iostream>
#include <limits>

using namespace std;

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

    // compute t
    // we need (3d) p0, n0 (from the plane); e, d (from the ray)
    
    bool hit = false;
    Eigen::Vector3d p0,n0,e,d;
    p0 = point;
    n0 = normal;
    e = ray.origin;
    d = ray.direction;
    
    double A, B, C, D, a, b, c, x1, y1, z1;
    A = n0(0);
    B = n0(1);
    C = n0(2);
    D = -n0.dot(p0);
    x1 = e(0);
    y1 = e(1);
    z1 = e(2);
    a = d(0);
    b = d(1);
    c = d(2);
    
    double Denominator = A*a + B*b + C*c ;
    if (Denominator == 0){
        hit = false;
        return hit;
    }else{
        double t_temp = -( A*x1 +B*y1 + C*z1 + D )/( Denominator );
        if ( t_temp < min_t ){
            hit = false;
            return hit;
        }else{
            hit = true;
            t = t_temp;
            n = normal/sqrt( normal(0)*normal(0) + normal(1)*normal(1) + normal(2)*normal(2) );

        }
    }
    
    return hit;
    
    
  ////////////////////////////////////////////////////////////////////////////
}

