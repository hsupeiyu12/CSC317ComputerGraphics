#include "first_hit.h"
#include <limits>
#include <iostream>
using namespace std;
bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    
    bool hit = false;
    int idx = 0;
    t = numeric_limits<double>::infinity();
    double t_temp;
    Eigen::Vector3d n_temp;
    
    for (int i = 0; i < objects.size(); ++i){
        
        if ((objects[i])->intersect(ray,min_t,t_temp,n_temp)){
            
            if (t_temp < t){
                t = t_temp;
                hit_id = i;
                hit = true;
                n = n_temp.normalized();
            }
        }
    }
    return hit;
  ////////////////////////////////////////////////////////////////////////////
}

