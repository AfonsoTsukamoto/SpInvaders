/*
 *  Drawable.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/4/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__



#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif

#include <iostream>
#include <new>
#include "Coord.h"
#include "GColor.h"


class Drawable{
protected:
	Coord *_coords;
	//GColor _gColor; Each one of the subclasses will know its color. Make the method virtual so they have to implement it
public:
	Drawable(const GLfloat x, const GLfloat y, const GLfloat z);
	Drawable();
	~Drawable(); /*LATER!*/
	void setPosition(const GLfloat x, const GLfloat y, const GLfloat z);
	void updatePosition(const GLfloat dx, const GLfloat dy, const GLfloat dz);
	void updatePosition(Coord coords);
	Coord* getPosition();
	virtual bool collision(Drawable * obj){ throw "COLLISION BEING CALLED ON DRAWABLE!\n"; }
	virtual GColor* getColor(){ throw "GET COLOR BEING CALLED ON DRAWABLE!\n"; }
	virtual inline void setColor(const GLfloat r, const GLfloat g, const GLfloat b){ throw "SET COLOR BEING CALLED ON DRAWABLE!\n"; }
	virtual inline void draw(){ throw "DRAW BEING CALLED ON DRAWABLE!\n"; }
	virtual float left(){ throw "LEFT BEING CALLED ON DRAWABLE!\n"; }
	virtual float right(){ throw "RIGHT BEING CALLED ON DRAWABLE!\n"; }
	virtual float top(){ throw "TOP BEING CALLED ON DRAWABLE!\n"; }
	virtual float bottom(){ throw "BOTTOM BEING CALLED ON DRAWABLE!\n"; }
};





#endif
