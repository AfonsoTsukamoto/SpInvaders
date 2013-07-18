/*
 *  Controller.h
 *  CGProjMerge
 *
 *  Created by Afonso Tsukamoto on 4/9/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <vector>
#include "Coord.h"
#include "GColor.h"
#include "Drawable.h"
#include "SpaceShip.h"
#include "Alien.h"
#include "Alien2.h"
#include "Shot.h"
#include "Obstacle.h"
#include "Texture.h"
#include "AlienShot.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include <SFML/Audio.hpp>


#define MOTION_SENSOR

#include "MotionInitializer.h"
#define ORTHOGONAL_CAM 11
#define PERSPECTIVE_BEHIND 12
#define PERSPECTIVE_FIRST_PERSON 13

#define ALIEN_SHOOT 14
#define SHIP_SHOOT 15

#define MOTION_STOPPED 16

#define MOTION_LEFT 17

#define MOTION_RIGHT 18

#define BIGGER(A,B) ((A>B)?(A):(B))
#define SMALLER(A,B) ((A<B)?(A):(B))
class Controller{
protected:
	GLsizei _width;
	GLsizei _height;
	std::vector<Alien*> _aliens1;
	std::vector<Alien*> _aliens2;
	std::vector<Alien*> _aliens3;
	std::vector<Alien*> _aliens4;
	std::vector<Alien*> _aliens5;
	std::vector<Shot*> _shoots;
	std::vector<AlienShot*> _alienShoots;
	std::vector<SpaceShip*> _livesDraws;
	std::vector<ParticleSystem*> _particlePack;
	SpaceShip *_ship;
	std::vector<Obstacle*> _obstacles;
	int _numbAliens;
	int _counter;
	bool _down;
	bool _right;
	bool _changeArms;
	float _aliensRight;
	float _aliensLeft;
	float _aliensRightInit;
	float _aliensLeftInit;
	float _limits;
	int _fps;
	float _lastTime;
	float _lastAlienFootMove;
	float _deltaTime;
	int _camera;
	int _frames;
	int _points;
	double _shipMovingRatio;
	double _shotMovingRatio;
	double _alienMovingRatio;
	bool* _keyStates;
	bool* _keySpecialStates;
	int _timesPressed;
	int _alienShootCounter;
	bool _shipStroke;
	int _shipStrokeCounter;
	bool _alienShoot;
	bool _allDead;
	int _totalAliens;
	//Sound stuff
	sf::SoundBuffer cSharp;
	sf::SoundBuffer gSharp;
	sf::SoundBuffer shotSound;
	sf::Sound shotsSounds;
	sf::Sound alienSound;
	bool _footState;
	GLfloat _directionY;
	//GL Textures
	GLuint _bgTexture;
	Texture *_textures;
	bool _textured;
	
	int _motionBefore;
	float _motionPosBefore;
public:
	Controller();
	~Controller();
	void HUD() const;
	void DisplayString( const int x, const int y, const string &label, const void * font) const;
	void initGame();
	void draw();
	void shoot(float x, float y, float z, int type);
	void shootMove();
	void collisionTesting();
	void alienMove();
	void alienDance();
	void shipMove();
	void alienShootMove();
	void alienStartShoot(Alien *a);
	void alienShoot();
	
	/*Callback Functions*/
	void initLighting();
	void display(void);
	void reshape(GLsizei w, GLsizei h);
	void keyboardFunc(unsigned char key, int x, int y);
	void keyboardUpFunc(unsigned char key, int x, int y);
	void specialKeyboardFunc(int key, int x, int y);
	void specialKeyboardUpFunc(int key, int x, int y);
	void idle();
	
	int deltaTime();
	void setDeltaTime(float actual);
	void setCamera(int mode);
	void drawText(const char *msg);
	void setWidth(int width);
	void setHeight(int height);
	void framesInc(void);
	void incStrokeCounter();
	void drawPlane(int divs, float ex, float ey, float ez);
	void createTexture();
	
	void actualizeSpStatesSensor(bool *moved);

};




#endif
