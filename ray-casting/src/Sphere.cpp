#include "Sphere.h"
#include "Ray.h"
#include <math.h>       /* sqrt */
#include <iostream>

using namespace std;
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    
    // compute (double) t by solviong the quadratic equation
    // Need (vec3d) d,e,c (center), and double r(radius)
    
    bool hit = false;
    
    Eigen::Vector3d d,e,c, temp;
    d = ray.direction;
    e = ray.origin;
    c = center;
    
    double A, B, C;
    
    
    A  = d(0)*d(0) + d(1)*d(1) +d(2)*d(2);
    temp = c - e;
    B = -2*( d.dot(temp) );
    C = temp(0)*temp(0) + temp(1)*temp(1) + temp(2)*temp(2) - radius*radius;
    
    double delta = B*B - 4*A*C;
    
    if (delta < 0){
        hit = false;
        return hit;
    }else{
        if (delta == 0){
            t = -B / (2*A);
            if (t > min_t){
                hit = true;
                n = (e + t * d - c);
                n = n/sqrt(n(0)*n(0)+n(1)*n(1)+n(2)*n(2));
                return hit;
            }else{
                hit = false;
                return hit;
            }
        }else{ // delta > 0
            double ans_plus =  (-B + sqrt(delta) )/(2*A);
            double ans_minus = (-B - sqrt(delta) )/(2*A);
            if (ans_minus>0){
                t = ans_minus;
            }else{
                t = ans_plus;
            }
            if (t >= min_t){
                hit = true;
                n = (e + t * d - c);
                n = n/sqrt(n(0)*n(0)+n(1)*n(1)+n(2)*n(2));
                return hit;
            }else{
                hit = false;
                return hit;
            }
        }
     }
    
    return hit;
  ////////////////////////////////////////////////////////////////////////////
}

