#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__


#include "Particle.h"
#include "Drawable.h"
#include <string>
#include <list>
using std::string;
using std::list;

class ParticleSystem {
    
public:
    ParticleSystem( const bool burst ,Drawable * obj);
    void Update( const float elapsed);
	bool stillAlive();
    void Draw() const;
    void Reset();
	const int NoParticles() const { return (int) activeParticles.size(); }
protected:
	float	 r,  g,  b; // colour
	float    x,  y,  z; // position
    list<Particle*> activeParticles, deadParticles;
    bool              respawnParticles;
    static int        Max_Particles;
};


#endif
