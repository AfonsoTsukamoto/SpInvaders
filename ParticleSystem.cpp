#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "ParticleSystem.h"


// ParticleSystem Implementation


ParticleSystem::ParticleSystem( const bool burst,Drawable * obj)
{
	
	r=obj->getColor()->r();
	g=obj->getColor()->g();
	b=obj->getColor()->b();	
	x=obj->getPosition()->fx();
	y=obj->getPosition()->fy();
	z=obj->getPosition()->fz();
	std::cout<<"PARTICLE PARTY"<<std::endl;
	std::cout<<"X: "<<x <<"Y: "<<y <<"Z: "<<z <<std::endl;
    for ( int i=0; i<Max_Particles; i++)
        activeParticles.push_back( new Particle(r, g, b, x, y, z) );
    respawnParticles = !burst;
}


int ParticleSystem::Max_Particles =500;


void ParticleSystem::Update( const float elapsed)
{
    list<Particle*>::iterator it = activeParticles.begin();
    while ( it != activeParticles.end() ) {
        (*it)->Update( elapsed, respawnParticles);
		if ( (*it)->IsAlive() )
			it++;
		else
		{
			deadParticles.push_back( *it);
			it = activeParticles.erase( it);
		}
    }
}

bool ParticleSystem::stillAlive(){
	if(deadParticles.size()==1000)
		return true;
	else
		return false;

}

void ParticleSystem::Draw() const
{	

	

    list<Particle*>::const_iterator it = activeParticles.begin();
    while ( it != activeParticles.end() ) {
        (*it)->Draw();
        it++;
    }
}


void ParticleSystem::Reset()
{
    list<Particle*>::iterator it = activeParticles.begin();
    while ( it != activeParticles.end() ) {
        (*it)->Respawn( true);
        it++;
    }
	it = deadParticles.begin();
	while( it != deadParticles.end() )
	{
		(*it)->Respawn();
		activeParticles.push_back( *it);
		it = deadParticles.erase( it);
	}
}
