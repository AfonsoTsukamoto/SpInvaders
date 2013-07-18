/*
 *  Alien2.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __ALIEN2_H__
#define __ALIEN2_H__




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

class Alien2 : public Drawable{
protected:
	GColor *_color;
	bool _isAlive;
	bool _footsUp;
public:
	Alien2(GLfloat x, GLfloat y, GLfloat z);
	Alien2();
	
	bool collision(Drawable * obj);
	GColor* getColor();
	void setColor(const GLfloat r, const GLfloat g, const GLfloat b);
	void setColor(int color);
	void draw();
	float left();
	float right();
	float top();
	float bottom();
	
	
};





#endif
