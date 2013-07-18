/*
 *  SpaceShip.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "SpaceShip.h"
#define DEBUG

SpaceShip::SpaceShip(GLfloat x, GLfloat y, GLfloat z, int lives): Drawable(x, y, z), _limits(1){
	_color = new GColor();
	_lives = lives;
}
SpaceShip::SpaceShip(GLfloat x, GLfloat y, GLfloat z): Drawable(x, y, z), _limits(1){
	_color = new GColor();
}

SpaceShip::SpaceShip(GLfloat x, GLfloat y, GLfloat z, int lives, GLfloat widthLimits): Drawable(x,y,z), _limits(widthLimits), _lives(lives){
	_color = new GColor();
}

SpaceShip::SpaceShip(){
	_color = new GColor();
}


void SpaceShip::decLives(){
	_lives--;
}

int SpaceShip::getLives(){
	return _lives;
}
void SpaceShip::setLives(int lives){
	_lives=lives;
}
bool SpaceShip::collision(Drawable * obj){ 
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

GColor* SpaceShip::getColor(){
	return _color;
}

void SpaceShip::setColor(const GLfloat r, const GLfloat g, const GLfloat b){
	_color->setColor(r,g,b);
}

void SpaceShip::setColor(int color){
	_color->setColor(color);
	
}

float SpaceShip::left(){
	return (_coords->fx()-0.85);
}
float SpaceShip::right(){
	return (_coords->fx()+0.85);
}
float SpaceShip::top(){
	return (_coords->fy()+0.4);
}
float SpaceShip::bottom(){
	return (_coords->fy()-0.4);
}

float SpaceShip::posX(){
	return _coords->fx();
}

float SpaceShip::posY(){
	return _coords->fy();
}

float SpaceShip::posZ(){
	return _coords->fz();
}


bool SpaceShip::inLimit(bool left){
	if(((_coords->fx() >= (-_limits+0.4)) && left) || ((_coords->fx() <= (_limits-0.4)) && !left))
		return true;
	return false;
}

//Overrides Drawable
void SpaceShip::updatePosition(const GLfloat dx, const GLfloat dy, const GLfloat dz){
#ifdef DEBUG
	std::cout << "Spaceship method" << "Return is" << (inLimit((dx<0.0) ? true : false ) ? "true" : "false") <<std::endl;
#endif
	
	if(inLimit( (dx<0.0) ? true : false )){
		Drawable::_coords->incX(dx);
		Drawable::_coords->incY(dy);
		Drawable::_coords->incZ(dz);
	}
#ifdef DEBUG
	Drawable::_coords->dump();
#endif
}

void SpaceShip::draw(){ 
	
#ifdef DEBUG
	_coords->dump();
#endif
	float mcolor[] = {_color->r()-0.2, _color->g()-0.4, _color->b()-0.4, 1.0f };
	GLfloat mat_ambient[] = { 0.5, 0.0, 0.0, 1.0 };
	GLfloat mat_emission[] = {0., 0., 0., 1.0};
	GLfloat mat_diffuse[] = { 0.4, .0, .0, 1.0 };
	GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
	float shininess= 150;
	glMaterialfv (GL_FRONT, GL_AMBIENT, mcolor);
	//glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
	
	
	//glColor3f(_color->r(), _color->g(), _color->b());
	
	glPushMatrix();
	glTranslatef(_coords->fx(), _coords->fy(), _coords->fz());
	glScalef(1.0, 1.0, 2.5); //Acertar os z's
	/*Spaceship bottom*/
	glPushMatrix();
	glScalef(17.0, 3.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*Spaceship middle*/
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0);
	glScalef(14.0, 1.0, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	/*Spaceship top/shooter*/
	glPushMatrix();
	glTranslatef(0, 0.3, 0);
	glScalef(1.0, 1.2, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
#ifdef PROF
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	glScalef(7.0, 1.0, 1.0);
	glutSolidSphere(0.1, 30, 30);
	glPopMatrix();
#endif
	glPopMatrix();
	
	
}


void SpaceShip::drawT(){ 
	
	float mcolor[] = {_color->r()-0.4, _color->g()-0.4, _color->b()-0.4, 1.0f };
	GLfloat mat_ambient[] = { 0.5, 0.0, 0.0, 1.0 };
	GLfloat mat_emission[] = {0., 0., 0., 1.0};
	GLfloat mat_diffuse[] = { 1., 1., 1., 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess= 150;
	glMaterialfv (GL_FRONT, GL_AMBIENT, mcolor);
	glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
	glPushMatrix();
	glTranslatef(_coords->fx(), _coords->fy(), _coords->fz());
	glScalef(1.0, 1.0, 2.5); //Acertar os z's
	
	
	//Lado direito paralelo a z
	glBegin(GL_POLYGON);
	glVertex3f(0.9f, -0.4f, 0.0f);
	glVertex3f(0.9f, 0.4f, 0.0f);
	glVertex3f(0.9f, 0.4f, 0.1f);
	glVertex3f(0.9f, -0.4f, 0.1f);	
	glEnd();
	
	//lado direito perpendicular a z
	glBegin(GL_POLYGON);
	glVertex3f(0.9f, 0.4f, 0.1f);
	glVertex3f(0.8f, 0.4f, 0.1f);
	glVertex3f(0.8f, -0.4f, 0.1f);
	glVertex3f(0.9f, -0.4f, 0.1f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(0.9f, -0.4f, 0.1f);
   glVertex3f(0.9f, -0.4f, 0.0f);
	glVertex3f(0.0f, -0.4f, 0.0f);
	glVertex3f(0.0f, -0.4f, 0.1f);
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);
	
	//triang
	glVertex3f(0.8f, 0.4f, 0.1f); //far antigo
	glVertex3f(0.7f, 0.4f, 0.12f); //far novo
	glVertex3f(0.8f, -0.4f, 0.1f); //near antigo

	glVertex3f(0.8f, -0.4f, 0.1f); //near antigo
	glVertex3f(0.7f, 0.4f, 0.12f); //far novo
	glVertex3f(0.7f, -0.4f, 0.12f); //near novo
	
	glVertex3f(0.8f, -0.4f, 0.1f); //near antigo
	glVertex3f(0.7f, -0.4f, 0.1f); //far novo
	glVertex3f(0.7f, -0.4f, 0.12f); //far novo
	
	//triang
	glVertex3f(0.7f, 0.4f, 0.12f); //far antigo
	glVertex3f(0.6f, 0.4f, 0.14f); //far novo
	glVertex3f(0.7f, -0.4f, 0.12f); //near antigo


	glVertex3f(0.7f, -0.4f, 0.12f); //near antigo
	glVertex3f(0.6f, 0.4f, 0.14f); //far novo
	glVertex3f(0.6f, -0.4f, 0.14f); //near novo	
	
	glVertex3f(0.7f, -0.4f, 0.1f); //far novo
	glVertex3f(0.6f, -0.4f, 0.1f); //far novo
	glVertex3f(0.6f, -0.4f, 0.14f); //near novo	
	glVertex3f(0.7f, -0.4f, 0.12f); //far novo
	
	//triang
	glVertex3f(0.6f, 0.4f, 0.14f);
	glVertex3f(0.5f, 0.4f, 0.16f);
	glVertex3f(0.6f, -0.4f, 0.14f);

	glVertex3f(0.6f, -0.4f, 0.14f);
	glVertex3f(0.5f, 0.4f, 0.16f);
	glVertex3f(0.5f, -0.4f, 0.16f);
	
	glVertex3f(0.6f, -0.4f, 0.1f); //near novo	
	glVertex3f(0.5f, -0.4f, 0.1f); //near novo
	glVertex3f(0.5f, -0.4f, 0.16f);
	glVertex3f(0.6f, -0.4f, 0.14f); //near novo	
	//triang
	glVertex3f(0.5f, 0.4f, 0.16f);
	glVertex3f(0.4f, 0.4f, 0.18f);
	glVertex3f(0.5f, -0.4f, 0.16f);
	
	glVertex3f(0.5f, -0.4f, 0.16f);
	glVertex3f(0.4f, 0.4f, 0.18f);
	glVertex3f(0.4f, -0.4f, 0.18f);
	
	glVertex3f(0.5f, -0.4f, 0.1f);
	glVertex3f(0.4f, -0.4f, 0.11f);
	glVertex3f(0.4f, -0.4f, 0.18f);
	glVertex3f(0.5f, -0.4f, 0.16f);

	//triang
	glVertex3f(0.4f, 0.4f, 0.18f);//far antigo
	glVertex3f(0.3f, 0.4f, 0.18f); //far novo
	glVertex3f(0.4f, -0.4f, 0.18f);//near antigo
	
	glVertex3f(0.4f, -0.4f, 0.18f); //near antigo
	glVertex3f(0.3f, 0.4f, 0.18f); //far novo
	glVertex3f(0.3f, -0.4f, 0.18f); //near novo
	
	glVertex3f(0.4f, -0.4f, 0.1f);
	glVertex3f(0.3f, -0.4f, 0.1f);
	glVertex3f(0.3f, -0.4f, 0.18f); //near novo
	glVertex3f(0.4f, -0.4f, 0.17f);
	
	//triang
	glVertex3f(0.3f, 0.4f, 0.18f);
	glVertex3f(0.2f, 0.4f, 0.15f);
	glVertex3f(0.3f, -0.4f, 0.18f);
	
	glVertex3f(0.3f, -0.4f, 0.18f);
	glVertex3f(0.2f, 0.4f, 0.15f);
	glVertex3f(0.2f, -0.4f, 0.15f);
	
	glVertex3f(0.3f, -0.4f, 0.1f); //near novo
	glVertex3f(0.2f, -0.4f, 0.1f); //near novo
	glVertex3f(0.2f, -0.4f, 0.15f);
	glVertex3f(0.3f, -0.4f, 0.18f); //near novo
	
	//triang
	glVertex3f(0.2f, 0.4f, 0.15f);
	glVertex3f(0.1f, 0.4f, 0.12f);
   glVertex3f(0.2f, -0.4f, 0.15f);
	
	glVertex3f(0.2f, -0.4f, 0.15f);
   glVertex3f(0.1f, 0.4f, 0.12f);
	glVertex3f(0.1f, -0.4f, 0.12f);
	
	glVertex3f(0.2f, -0.4f, 0.1f);
	glVertex3f(0.1f, -0.4f, 0.1f);
	glVertex3f(0.1f, -0.4f, 0.12f);
	glVertex3f(0.2f, -0.4f, 0.15f);
	
	//triang
	glVertex3f(0.1f, 0.4f, 0.12f);
	glVertex3f(0.0f, 0.4f, 0.1f);
	glVertex3f(0.1f, -0.4f, 0.12f);
	
	glVertex3f(0.1f, -0.4f, 0.12f);
	glVertex3f(0.0f, 0.4f, 0.1f);
	glVertex3f(0.0f, -0.4f, 0.1f);
	
	glVertex3f(0.1f, -0.4f, 0.1f);
	glVertex3f(0.0f, -0.4f, 0.1f);
	glVertex3f(0.1f, -0.4f, 0.12f);
	glEnd();
	
	
	
	
	//////////////////////////////
	
	//Left side
	
	//////////////////////////////
	
	

	
	glBegin(GL_TRIANGLE_STRIP);
	
	//triang
	glVertex3f(-0.8f, 0.4f, 0.1f); //far antigo
	glVertex3f(-0.7f, 0.4f, 0.12f); //far novo
	glVertex3f(-0.8f, -0.4f, 0.1f); //near antigo
	
	glVertex3f(-0.8f, -0.4f, 0.1f); //near antigo
	glVertex3f(-0.7f, 0.4f, 0.12f); //far novo
	glVertex3f(-0.7f, -0.4f, 0.12f); //near novo
	
	glVertex3f(-0.8f, -0.4f, 0.1f); //near antigo
	glVertex3f(-0.7f, -0.4f, 0.1f); //far novo
	glVertex3f(-0.7f, -0.4f, 0.12f); //far novo
	
	//triang
	glVertex3f(-0.7f, 0.4f, 0.12f); //far antigo
	glVertex3f(-0.6f, 0.4f, 0.14f); //far novo
	glVertex3f(-0.7f, -0.4f, 0.12f); //near antigo
	
	
	glVertex3f(-0.7f, -0.4f, 0.12f); //near antigo
	glVertex3f(-0.6f, 0.4f, 0.14f); //far novo
	glVertex3f(-0.6f, -0.4f, 0.14f); //near novo	
	
	glVertex3f(-0.7f, -0.4f, 0.1f); //far novo
	glVertex3f(-0.6f, -0.4f, 0.1f); //far novo
	glVertex3f(-0.6f, -0.4f, 0.14f); //near novo	
	glVertex3f(-0.7f, -0.4f, 0.12f); //far novo
	
	//triang
	glVertex3f(-0.6f, 0.4f, 0.14f);
	glVertex3f(-0.5f, 0.4f, 0.16f);
	glVertex3f(-0.6f, -0.4f, 0.14f);
	
	glVertex3f(-0.6f, -0.4f, 0.14f);
	glVertex3f(-0.5f, 0.4f, 0.16f);
	glVertex3f(-0.5f, -0.4f, 0.16f);
	
	glVertex3f(-0.6f, -0.4f, 0.1f); //near novo	
	glVertex3f(-0.5f, -0.4f, 0.1f); //near novo
	glVertex3f(-0.5f, -0.4f, 0.16f);
	glVertex3f(-0.6f, -0.4f, 0.14f); //near novo	
	//triang
	glVertex3f(-0.5f, 0.4f, 0.16f);
	glVertex3f(-0.4f, 0.4f, 0.18f);
	glVertex3f(-0.5f, -0.4f, 0.16f);
	
	glVertex3f(-0.5f, -0.4f, 0.16f);
	glVertex3f(-0.4f, 0.4f, 0.18f);
	glVertex3f(-0.4f, -0.4f, 0.18f);
	
	glVertex3f(-0.5f, -0.4f, 0.1f);
	glVertex3f(-0.4f, -0.4f, 0.11f);
	glVertex3f(-0.4f, -0.4f, 0.18f);
	glVertex3f(-0.5f, -0.4f, 0.16f);
	
	//triang
	glVertex3f(-0.4f, 0.4f, 0.18f);//far antigo
	glVertex3f(-0.3f, 0.4f, 0.18f); //far novo
	glVertex3f(-0.4f, -0.4f, 0.18f);//near antigo
	
	glVertex3f(-0.4f, -0.4f, 0.18f); //near antigo
	glVertex3f(-0.3f, 0.4f, 0.18f); //far novo
	glVertex3f(-0.3f, -0.4f, 0.18f); //near novo
	
	glVertex3f(-0.4f, -0.4f, 0.1f);
	glVertex3f(-0.3f, -0.4f, 0.1f);
	glVertex3f(-0.3f, -0.4f, 0.18f); //near novo
	glVertex3f(-0.4f, -0.4f, 0.17f);
	
	//triang
	glVertex3f(-0.3f, 0.4f, 0.18f);
	glVertex3f(-0.2f, 0.4f, 0.15f);
	glVertex3f(-0.3f, -0.4f, 0.18f);
	
	glVertex3f(-0.3f, -0.4f, 0.18f);
	glVertex3f(-0.2f, 0.4f, 0.15f);
	glVertex3f(-0.2f, -0.4f, 0.15f);
	
	glVertex3f(-0.3f, -0.4f, 0.1f); //near novo
	glVertex3f(-0.2f, -0.4f, 0.1f); //near novo
	glVertex3f(-0.2f, -0.4f, 0.15f);
	glVertex3f(-0.3f, -0.4f, 0.18f); //near novo
	
	//triang
	glVertex3f(-0.2f, 0.4f, 0.15f);
	glVertex3f(-0.1f, 0.4f, 0.12f);
   glVertex3f(-0.2f, -0.4f, 0.15f);
	
	glVertex3f(-0.2f, -0.4f, 0.15f);
   glVertex3f(-0.1f, 0.4f, 0.12f);
	glVertex3f(-0.1f, -0.4f, 0.12f);
	
	glVertex3f(-0.2f, -0.4f, 0.1f);
	glVertex3f(-0.1f, -0.4f, 0.1f);
	glVertex3f(-0.1f, -0.4f, 0.12f);
	glVertex3f(-0.2f, -0.4f, 0.15f);
	
	//triang
	glVertex3f(-0.1f, 0.4f, 0.12f);
	glVertex3f(0.0f, 0.4f, 0.1f);
	glVertex3f(-0.1f, -0.4f, 0.12f);
	
	glVertex3f(-0.1f, -0.4f, 0.12f);
	glVertex3f(0.0f, 0.4f, 0.1f);
	glVertex3f(0.0f, -0.4f, 0.1f);
	
	glVertex3f(-0.1f, -0.4f, 0.1f);
	glVertex3f(0.0f, -0.4f, 0.1f);
	glVertex3f(-0.1f, -0.4f, 0.12f);
	glEnd();	
	
	//Lado direito paralelo a z
	glBegin(GL_POLYGON);
	glVertex3f(-0.9f, -0.4f, 0.0f);
	glVertex3f(-0.9f, 0.4f, 0.0f);
	glVertex3f(-0.9f, 0.4f, 0.1f);
	glVertex3f(-0.9f, -0.4f, 0.1f);	
	glEnd();
	
	//lado direito perpendicular a z
	glBegin(GL_POLYGON);
	glVertex3f(-0.9f, 0.4f, 0.1f);
	glVertex3f(-0.8f, 0.4f, 0.1f);
	glVertex3f(-0.8f, -0.4f, 0.1f);
	glVertex3f(-0.9f, -0.4f, 0.1f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-0.9f, -0.4f, 0.1f);
   glVertex3f(-0.9f, -0.4f, 0.0f);
	glVertex3f(0.0f, -0.4f, 0.0f);
	glVertex3f(0.0f, -0.4f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.12, 0.4, 0.0);
	glVertex3f(-0.12, 0.4, 0.1);
	glVertex3f(-0.12, 0.7, 0.1);
	glVertex3f(-0.12, 0.7, 0.0);
	
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-0.12, 0.7, 0.1);
	glVertex3f(0.12, 0.7, 0.1);
	glVertex3f(0.12, 0.7, 0.0);
	glVertex3f(-0.12, 0.7, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(0.12, 0.7, 0.1);
	glVertex3f(0.12, 0.4, 0.1);
	glVertex3f(0.12, 0.4, 0.0);
	glVertex3f(0.12, 0.7, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(0.12, 0.7, 0.1);
	glVertex3f(-0.12, 0.7, 0.1);
	glVertex3f(-0.12, 0.4, 0.1);
	glVertex3f(0.12, 0.4, 0.1);
	glEnd();
	
	
	glBegin(GL_POLYGON);
	glVertex3f(-0.9, -0.4, 0.0);
	glVertex3f(0.9, -0.4, 0.0);
	glVertex3f(0.9, 0.4, 0.0);
	glVertex3f(-0.9, 0.4, 0.0);
	glEnd();
	
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 0.1);
	glVertex3f(-0.9, -0.3, 0.05);
	glVertex3f(-0.9, 0.3, 0.05);
	glVertex3f(-1.0, 0.3, 0.05);
	glVertex3f(-1.0, -0.3, 0.05);
	glEnd();
	
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 0.1);
	glVertex3f(0.9, -0.3, 0.05);
	glVertex3f(0.9, 0.3, 0.05);
	glVertex3f(1.0, 0.3, 0.05);
	glVertex3f(1.0, -0.3, 0.05);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 0.1);
	glVertex3f(-0.9, -0.3, 0.04);
	glVertex3f(-0.9, 0.3, 0.04);
	glVertex3f(-1.0, 0.3, 0.04);
	glVertex3f(-1.0, -0.3, 0.04);
	glEnd();
	
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 0.1);
	glVertex3f(0.9, -0.3, 0.04);
	glVertex3f(0.9, 0.3, 0.04);
	glVertex3f(1.0, 0.3, 0.04);
	glVertex3f(1.0, -0.3, 0.04);
	glEnd();
	
	
	glPopMatrix();
	
	
	
//TODO	
	
}





