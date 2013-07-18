/*
 *  Alien2.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Alien2.h"
//#define PROF
Alien2::Alien2(GLfloat x, GLfloat y, GLfloat z): Drawable(x,y,z){
	_color = new GColor();
	_isAlive = true;
	_footsUp =true;
	
}
Alien2::Alien2(): Drawable(){
	_color = new GColor();
	_isAlive = false;
	_footsUp = true;
}

bool Alien2::collision(Drawable * obj){ 
	return	(
			(obj->right() <= right())
				&&
			(obj->left() >= left())
				&&
			(obj->top() >= bottom())
				&&
			(obj->bottom() <= top())
			)
			;
}

GColor* Alien2::getColor(){ return _color; }

void Alien2::setColor(const GLfloat r, const GLfloat g, const GLfloat b){
	_color->setColor(r,g,b);
}
void Alien2::setColor(int color){
	_color->setColor(color);
}


float Alien2::left(){
	return (_coords->fx()-0.55);
}
float Alien2::right(){
	return (_coords->fx()+0.55);
}

float Alien2::top(){
	return (_coords->fy()+0.4);
}
float Alien2::bottom(){
	return (_coords->fy()-0.4);
}

void Alien2::draw(){
	
	glColor3f(_color->r(), _color->g(), _color->b());
	
	/*Global Translation*/
	glPushMatrix();
	glTranslatef(_coords->fx(), _coords->fy(), _coords->fz());
	
#ifndef PROF
	//glScalef(2.0, 2.0, 2.0);
	/*1st(central body)*/
	glPushMatrix();
	glScalef(11.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/** BOTTOM BODY**/
	
	/*2nd (left foot)*/
	glPushMatrix();
	if(_footsUp){
		glTranslatef(-0.5, -0.15, 0.0);
		//_footsUp = false;
	}else{
		glTranslatef(-0.5, 0.15, 0.0);
		//_footsUp = true;
	}
	glScalef(1.0, 2.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*3rd (bottom body)*/
	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glScalef(7.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*4th (right foot)*/
	glPushMatrix();
	if(_footsUp){
		glTranslatef(0.5, -0.15, 0.0);
		_footsUp = false;
	}else{
		glTranslatef(0.5, 0.15, 0.0);
		_footsUp = true;
	}
	glScalef(1.0, 2.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*5th (left tentacle holder)*/
	glPushMatrix();
	glTranslatef(-0.3, -0.2, 0.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*6th (right tentacle holder)*/
	glPushMatrix();
	glTranslatef(0.3, -0.2, 0.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*7th (left tentacle)*/
	glPushMatrix();
	glTranslatef(-0.15, -0.3, 0.0);
	glScalef(2.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*8th(right tentacle)*/
	glPushMatrix();
	glTranslatef(0.15, -0.3, 0.0);
	glScalef(2.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/** UPPER BODY**/
	
	/*9th (left side of left eye)*/
	glPushMatrix();
	glTranslatef(-0.35, 0.1, 0.0);
	glScalef(2.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*10th (between eyes)*/
	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.0);
	glScalef(3.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*11th(right side of right eye)*/
	glPushMatrix();
	glTranslatef(0.35, 0.1, 0.0);
	glScalef(2.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*12th (eyebrows)*/
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0);
	glScalef(7.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*13th (bottom left antena)*/
	glPushMatrix();
	glTranslatef(-0.2, 0.3, 0.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*14th (bottom right antena)*/
	glPushMatrix();
	glTranslatef(0.2, 0.3, 0.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*15th (top left antena)*/
	glPushMatrix();
	glTranslatef(-0.3, 0.4, 0.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*16th (top right antena)*/
	glPushMatrix();
	glTranslatef(0.3, 0.4, 0.0);
	glutSolidCube(0.1);
	glPopMatrix();
#else
	glScalef(1.3, 1.3, 1.3);
	
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	glScalef(5.0, 1.0, 1.0);
	glutSolidSphere(0.1, 40, 40);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.25, 0.0, 0.0);
	glScalef(1.0, 1.9, 1.0);
	glutSolidSphere(0.05, 30, 30);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.25, 0.0, 0.0);
	glScalef(1.0, 1.9, 1.0);
	glutSolidSphere(0.05, 30, 30);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.25, 0.0, 0.0);
		glRotated(180, 0, 0, 1);
	glScalef(1.0, 2.0, 1.0);
	glutSolidCone(0.05, 0.2, 30, 30);
	//glutSolidCube(0.1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.25, -0.2, 0.0);
	glRotated(180, 0, 0, 1);
	glScalef(1.0, 2.0, 1.0);
	glutSolidCone(0.05, 0.2, 30, 30);
	//glutSolidCube(0.1);
	glPopMatrix();
	
#endif
	
	glPopMatrix();
	
	
}





