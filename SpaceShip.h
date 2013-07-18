/*
 *  SpaceShip.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/4/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__


#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif


//#define DEBUG
//#define PROF
#include "Drawable.h"
#include "Coord.h"
#include "GColor.h"

class SpaceShip : public Drawable{
protected:
	GColor *_color;
	GLfloat _limits;
	int _lives;
public:
	SpaceShip(GLfloat x, GLfloat y, GLfloat z, int lives);
	SpaceShip(GLfloat x, GLfloat y, GLfloat z, int lives, GLfloat widthLimits);
	SpaceShip(GLfloat x, GLfloat y, GLfloat z);
	SpaceShip();
	void decLives();
	int getLives();
	void setLives(int lives);
	bool collision(Drawable * obj);
	GColor* getColor();
	void setColor(const GLfloat r, const GLfloat g, const GLfloat b);
	void setColor(int color);
	float left();
	float right();
	float top();
	float bottom();
	bool inLimit(bool left);
	//Overrides Drawable
	void updatePosition(const GLfloat dx, const GLfloat dy, const GLfloat dz);
	float posX();
	float posY();
	float posZ();
	void draw();
	void drawT();
};

#endif
