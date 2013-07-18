/*
 *  GColor.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/4/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GCOLOR_H__
#define __GCOLOR_H__

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif

#include <iostream>

#define C_BLACK 0
#define C_WHITE 1
#define C_RED	 2
#define C_GREEN 3
#define C_BLUE  4
#define C_YELLOW 5


class GColor{
protected:
	GLfloat _r; 
	GLfloat _g;
	GLfloat _b; 
	bool _isSet;
public:
	GColor(GLfloat r, GLfloat g, GLfloat b): _r(r), _g(g), _b(b), _isSet(true){}
	GColor(int color){ this->setColor(color); }
	GColor():_r(0), _g(0), _b(0), _isSet(false){}
	
	void setColor(const GLfloat r, const GLfloat g, const GLfloat b);
	
	void setColor(int color);
	
	GLfloat r();
	
	GLfloat g();
	
	GLfloat b();

	void dump();

};


#endif