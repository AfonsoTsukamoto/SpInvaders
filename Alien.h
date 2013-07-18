/*
 *  Alien.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/13/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __ALIEN_H__
#define __ALIEN_H__




#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif

//#define ORTHO
//#define DEBUG
//#define PROF
#include "Drawable.h"
#include "Coord.h"
#include "GColor.h"

class Alien : public Drawable{
protected:
	GColor *_color;
	bool _isAlive;
	bool _footsUp;
	GLfloat _limits;
public:
	Alien(GLfloat x, GLfloat y, GLfloat z);
	Alien(GLfloat x, GLfloat y, GLfloat z, GLfloat widthLimits);
	Alien();
	~Alien();
	float limits();
	bool collision(Drawable * obj);
	GColor* getColor();
	void setColor(const GLfloat r, const GLfloat g, const GLfloat b);
	void setColor(int color);
	void draw();
	float left();
	float right();
	float top();
	float bottom();
	void reactFoots();
	bool footsUp();
};






#endif
