#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "Particle.h"

Particle::Particle(float _r,float _g,float  _b, float _x, float  _y, float _z)
{	r=_r;
	g=_g;
	b=_b;	
	x=_x;
	y=_y;
	z=_z;
	life = 0.0f;
	
    Respawn();
}


const bool Particle::Respawn( const bool force)
{
    if ( life <= 0.0f  || force )
    {
        double v = 0.7*frand()+0.2;
        double phi = frand()*M_PI;
        double theta = 2.0*frand()*M_PI;
		  vx = v * cos(theta) * sin(phi);
        vy = v * sin(theta) * sin(phi);
        vz = v * cos(phi);
        ax =  0.0001f; /* just a little wind */
        ay =  0.0001f; /* gravity pull */
        az = -0.25f;
        
        life = 1.0f;		                        /* life granted to particle */
		fade = 0.0001515 + frand() * .000303;	    /* life decay */
        return true;
    }
    return false;
}


const Particle & Particle::operator = (const Particle & another)
{
    x  = another.x;
    y  = another.y;
    z  = another.z;
    vx = another.vx;
    vy = another.vy;
    vz = another.vz;
    ax = another.ax;
    ay = another.ay;
    az = another.az;
    r  = another.r;
    g  = another.g;
    b  = another.b;
    life = another.life;
    fade = another.fade;
    
    return *this;
}


const bool Particle::Update(const float elapsedTime, const bool respawn)
{
    if ( respawn && life <= 0. )
        Respawn();
    if ( life > 0. )
    {
        float delta = elapsedTime * .00378;
        x += (vx * delta);
        y += (vy * delta);
        z += (vz * delta);
        vx += (ax * delta);
        vy += (ay * delta);
        vz += (az * delta);
        life -= (fade * elapsedTime );
        return true;
    }
    return false;
}


unsigned int Particle::ParticleSkeleton;


void Particle::Draw() const
{	float mcolor[] = {r, g,b, 1.0f };
	GLfloat mat_ambient[] = {r+0.4f,g+0.4f, b+0.4f, 1.0f };
	GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float shininess= 80;
	glMaterialfv (GL_FRONT, GL_AMBIENT, mcolor);
	glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
    glTranslatef( x, y, z);
    glColor4f( r, g, b, life);
    glCallList( ParticleSkeleton);
    glPopMatrix();
}


unsigned int Particle::CreateParticleSkeleton()
{

    ParticleSkeleton = glGenLists( 1);
    glNewList( ParticleSkeleton, GL_COMPILE);
    glScalef( .5, .5, 1.);
    glutSolidCube(0.05);
    glEnd();
    glEndList();
    return ParticleSkeleton;
}
