#include "Triangle.h"
#include "Ray.h"
#include <math.h>       /* sqrt */
#include <iostream>

using namespace std;


bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    
    // vertices A,B,C
    Eigen::Vector3d A,B,C;
    A = get<0>(corners);
    B = get<1>(corners);
    C = get<2>(corners);
    
    Eigen::Vector3d E,D;
    E = ray.origin;
    D = ray.direction;
    
    // matrix: (a-b) (a-c) d  x = (a-e)
    Eigen::Vector3d AminusB, AminusC, AminusE;
    AminusB = A - B;
    AminusC = A - C;
    AminusE = A - E;
    
    double a,b,c, d,e,f, g,h,i, j,k,l;
    
    a = AminusB(0);
    b = AminusB(1);
    c = AminusB(2);
    
    d = AminusC(0);
    e = AminusC(1);
    f = AminusC(2);
    
    g = D(0);
    h = D(1);
    i = D(2);
    
    j =  AminusE(0);
    k =  AminusE(1);
    l =  AminusE(2);
    
    // M = a(ei − hf ) + b(gf − di) + c(dh − eg)
    double M = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
    
    double beta, gamma;
    //β = [j(ei − hf ) + k(gf − di) + l(dh − eg)]/M
    //γ = [i(ak − jb) + h(jc − al) + g(bl − kc)]/M
    //t = −[f (ak − jb) + e(jc − al) + d(bl − kc)]/M

    t = - (f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;
    if (t < min_t){
        t = min_t;
        n = D;
        return false;
    }
    
    gamma = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
    if (gamma < 0 || gamma > 1){
        t = min_t;
        n = D;
        return false;
    }
    
    beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
    if (beta < 0 || beta > (1-gamma) ){
        t = min_t;
        n = D;
        return false;
    }
       
    n(0) = b*f - c*e;
    n(1) = -(a*f - c*d);
    n(2) = a*e - b*d;
    
    n.normalized();
    
    return true;
  ////////////////////////////////////////////////////////////////////////////
}


