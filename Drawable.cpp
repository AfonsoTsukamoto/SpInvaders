/*
 *  Drawable.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#include "Drawable.h"



Drawable::Drawable(const GLfloat x, const GLfloat y, const GLfloat z){
	_coords = new Coord(x,y,z);

}
Drawable::Drawable(){
	_coords = new Coord();

}

Drawable::~Drawable(){
	delete _coords;

} //TODO

void Drawable::setPosition(const GLfloat x, const GLfloat y, const GLfloat z){
	_coords->set(x, y, z);
}

void Drawable::updatePosition(const GLfloat dx, const GLfloat dy, const GLfloat dz){
	_coords->incX(dx);
	_coords->incY(dy);
	_coords->incZ(dz);
}

void Drawable::updatePosition(Coord coords){
	_coords->set(coords.fx(), coords.fy(), coords.fz());
}

Coord* Drawable::getPosition(){
	return _coords;
}