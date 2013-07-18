/*
 *  Alien.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/13/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Alien.h"
//#define DEBUG
//#define PROF
Alien::Alien(GLfloat x, GLfloat y, GLfloat z): Drawable(x,y,z){
	_color = new GColor();
	_isAlive = true;
	_footsUp =true;

}

Alien::Alien(GLfloat x, GLfloat y, GLfloat z, GLfloat widthLimits): Drawable(x,y,z){
	_color = new GColor();
	_isAlive = true;
	_footsUp = true;
	_limits = widthLimits;
}
Alien::Alien(): Drawable(){
	_color = new GColor();
	_isAlive = false;
	_footsUp = true;
}


Alien::~Alien(){
	delete _color;
}

bool Alien::collision(Drawable * obj){ 
	return	(
			(obj->bottom() <= top())
			&&
			(obj->left() >= left())
			&&
			(obj->right() <= right())
			&&
			(obj->top() >= bottom())
			)
			;
}

GColor* Alien::getColor(){ return _color; }

void Alien::setColor(const GLfloat r, const GLfloat g, const GLfloat b){
	_color->setColor(r,g,b);
}
void Alien::setColor(int color){
	_color->setColor(color);
}


float Alien::left(){
	return (_coords->fx()-0.55);
}
float Alien::right(){
	return (_coords->fx()+0.55);
}

float Alien::top(){
	return (_coords->fy()+0.4);
}
float Alien::bottom(){
	return (_coords->fy()-0.4);
}

float Alien::limits(){
	return _limits;
}

void Alien::draw(){
#ifdef DEBUG
	_coords->dump();
#endif
	
	glColor3f(_color->r(), _color->g(), _color->b());
	
	float mcolor[] = {_color->r(), _color->g(), _color->b(), 1.0f };
	GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_emission[] = {0.0, 0.0, 0.0, 0.0};
	GLfloat mat_diffuse[] = { _color->r()+0.4, _color->g()+0.4, _color->b()+0.4, 1.0 };
	GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
	float shininess= 150;
	glMaterialfv (GL_FRONT, GL_AMBIENT, mcolor);
	glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mcolor);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
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
		}else{
			glTranslatef(-0.5, 0.15, 0.0);
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
		}else{
			glTranslatef(0.5, 0.15, 0.0);
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
	
	
	
	
	float emcolor[] = {0.0,0.0,0.0, 1.0f };
	GLfloat _mat_diffuse[] = {0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, emcolor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, emcolor);
		glPushMatrix();
		glTranslatef(-0.2, 0.1, 0.0);
		glScalef(1.0, 1.0, 1.0);
		glutSolidCube(0.1);
		glPopMatrix();
	
	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mcolor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mcolor);
		/*10th (between eyes)*/
		glPushMatrix();
		glTranslatef(0.0, 0.1, 0.0);
		glScalef(3.0, 1.0, 1.0);
		glutSolidCube(0.1);
		glPopMatrix();
	
	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, emcolor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, emcolor);
	glPushMatrix();
	glTranslatef(0.2, 0.1, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();


	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mcolor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

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
	glScalef(5.0, 1.0, 1.0);
	glutSolidSphere(0.1, 40, 40);
	glPopMatrix();
	
	/*eyeeeeees!*/
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.25, 0.0, 0.0);
	glScalef(1.0, 1.5, 1.0);
	glutSolidSphere(0.09, 30, 30);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(-0.25, 0.0, 0.0);
	glScalef(1.0, 1.5, 1.0);
	glutSolidSphere(0.09, 30, 30);
	glPopMatrix();
	
	/*eyes inside*/
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.25, 0.0, 0.0);
	glScalef(1.0, 1.5, 1.0);
	glutSolidSphere(0.05, 30, 30);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-0.25, 0.0, 0.0);
	glScalef(1.0, 1.5, 1.0);
	glutSolidSphere(0.05, 30, 30);
	glPopMatrix();
	
	
	glColor3f(_color->r(), _color->g(), _color->b());
	glPushMatrix();
	glTranslatef(0.25, -0.2, 0.0);
	glScalef(1.0, 2.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.25, -0.2, 0.0);
	glScalef(1.0, 2.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
#endif
	
	glPopMatrix();


}

void Alien::reactFoots(){
	if(_footsUp)
		_footsUp = false;
	else{
		_footsUp = true;
	}
}

bool Alien::footsUp(){
	return _footsUp;
}




