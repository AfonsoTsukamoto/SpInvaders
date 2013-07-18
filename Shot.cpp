/*
 *  Shot.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/15/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Shot.h"

Shot::Shot(GLfloat x, GLfloat y, GLfloat z): Drawable(x, y, z){
	_color = new GColor(C_WHITE);
	

}

Shot::Shot(GLfloat x, GLfloat y, GLfloat z, bool up): Drawable(x, y, z), _up(up){
	_color = new GColor(C_WHITE);

}
Shot::Shot(): Drawable(){
	_color = new GColor(C_WHITE);
	
}

Shot::~Shot(){
	delete _color;
}

bool Shot::collision(Drawable * obj){ 
	return	(
			(right() <= obj->right())
				&&
			(left() >= obj->left())
				&&
			(top() >= obj->bottom())
				&&
			(bottom() <= obj->top())
			)
			;
}

GColor* Shot::getColor(){
	return _color;
}
void Shot::setColor(const GLfloat r, const GLfloat g, const GLfloat b){
	_color->setColor(r,b,g);
}

float Shot::left(){
	return (_coords->fx()-0.05);
}
float Shot::right(){
	return (_coords->fx()+0.05);
}
float Shot::top(){
	return (_coords->fy()+0.3);
}
float Shot::bottom(){
		return (_coords->fy()-0.3);
}
float Shot::pos(){
	return (_coords->fx());
}

void Shot::draw(){
	_width = 0.3;
	_height = 1.0;
	
	glColor3f(_color->r(), _color->g(), _color->b());
	
	float mcolor[] = {_color->r(), _color->g(), _color->b(), 1.0f };
	GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_emission[] = {0.7, 0.3, 0.1, 1.0};
	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
	float shininess= 150;
	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mcolor);
	glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mcolor);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
	/*Global Translation*/
	glPushMatrix();
	glTranslatef(_coords->fx(), _coords->fy(), _coords->fz());
	glScalef(1.0, 1.0, 2.5);	//Acertar os z's
	glScalef(1.0, 6.0, 1.0);
		
	/*Shot*/
	glutSolidCube(0.1);

	glPopMatrix();
}

