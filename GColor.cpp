/*
 *  GColor.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#include "GColor.h"

void GColor::setColor(const GLfloat r, const GLfloat g, const GLfloat b){
	_r = r; _g = g; _b = b; _isSet = true;
}

void GColor::setColor(int color){
	switch (color) {
		case C_BLACK:
			this->setColor(0.0f, 0.0f, 0.0f);
			break;
		case C_WHITE:
			this->setColor(1.0f, 1.0f, 1.0f);
			break;
		case C_RED:
			this->setColor(1.0f, 0.0f, 0.0f);
			break;
		case C_GREEN:
			this->setColor(0.0f, 1.0f, 0.0f);
			break;
		case C_BLUE:
			this->setColor(0.0f, 0.0f, 1.0f);
			break;
		case C_YELLOW:
			this->setColor(1.0f, 1.0f, 0.0f);
			break;
		default:
			this->setColor(0.0f, 0.0f, 0.0f);
			break;
	}
	_isSet = true;
}

GLfloat GColor::r(){ return _r; }
GLfloat GColor::g(){ return _g; }
GLfloat GColor::b(){ return _b; }

void GColor::dump(){
	std::cout << "R = " << _r << std::endl;
	std::cout << "G = " << _g << std::endl;
	std::cout << "B = " << _b << std::endl;
}