#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <string>
#include <list>
#include "glbmp.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctype.h>
#include <cmath>
#include <cstdlib>



#define frand()			((float)rand()/RAND_MAX)
#ifndef M_PI
#define M_PI 3.14159265
#endif
using std::string;
using std::list;
using namespace std;

class Particle {
	float	life;		// life
	float	fade;		// fade
	float	 r,  g,  b; // colour
	float    x,  y,  z; // position
	float   vx, vy, vz; // speed
    float   ax, ay, az; // aceleration
    static unsigned int ParticleSkeleton;
   
public:
    Particle(float _r,float _g,float  _b, float _x, float  _y, float _z);
    Particle( const Particle & another) { *this = another; }
    const Particle & operator = ( const Particle & another);
    const bool Update( const float elapsedTime, const bool respawn);
    void       Draw() const;
    const bool Respawn( const bool force = false);
	const bool IsAlive() const { return life>0.f; }
	const bool IsDead()  const { return life<=0.0f; } 
    
    static unsigned int CreateParticleSkeleton();
};

#endif

