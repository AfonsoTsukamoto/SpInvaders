/*
 *  Obstacle.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__




#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif

//#define ORTHO
//#define DEBUG
#include "Drawable.h"
#include "Coord.h"
#include "GColor.h"
#include <vector>

class Obstacle : public Drawable{
protected:
	GColor *_color;	
	std::vector< std::vector<bool> > _bitMap;
	int killer_counter;
public:
	Obstacle(GLfloat x, GLfloat y, GLfloat z);
	Obstacle();
	
	bool collision(Drawable * obj);
	GColor* getColor();
	void setColor(const GLfloat r, const GLfloat g, const GLfloat b);
	void setColor(int color);
	void drawCube();
	void draw();
	bool killed();
	bool part_destroyed(float x);
	bool alien_damage(float x);
	float left();
	float right();
	float bottom();
	float top();
	
	
};


#endif
