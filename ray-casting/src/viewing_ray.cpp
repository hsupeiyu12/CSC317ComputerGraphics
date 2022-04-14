#include "viewing_ray.h"


void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
    
    // set u and v sclars
    double u,v;
    u = (camera.width * (j + 0.5) / width) - camera.width/2;
    v = -(camera.height * (i + 0.5) / height) + camera.height/2;

    // set ray.direction
    double d = camera.d;
    ray.direction = -d*camera.w + u*camera.u + v*camera.v;
    
    // set ray.origin
    ray.origin = camera.e;

  ////////////////////////////////////////////////////////////////////////////
}

