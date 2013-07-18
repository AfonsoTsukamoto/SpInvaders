/*
 *  AlienShot.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 5/7/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
/*
 *  Shot.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/15/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __ALIEN_SHOT_H__
#define __ALIEN_SHOT_H__



#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif

#include "Drawable.h"
#include "GColor.h"

class AlienShot : public Drawable {
	
protected:
	GColor *_color;
	float _width;
	float _height;
	bool _up;
public:
	AlienShot(GLfloat x, GLfloat y, GLfloat z);
	AlienShot(GLfloat x, GLfloat y, GLfloat z, bool up);
	AlienShot();
	~AlienShot();
	bool collision(Drawable * obj);
	GColor* getColor();
	void setColor(const GLfloat r, const GLfloat g, const GLfloat b);
	void draw();
	float left();
	float right();
	float top();
	float bottom();
	float pos();
};





#endif

