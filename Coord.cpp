/*
 *  HCoord.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#include "Coord.h"

/*Setters*/
void Coord::set(const GLint x, const GLint y, const GLint z){
	_x = x; _y = y; _z = z; _isInt = true;

}

void Coord::set(const GLfloat x, const GLfloat y, const GLfloat z){
	_fx = x; _fy = y; _fz = z;	_isInt = false;
}

/*Getters*/
GLint Coord::x(){ return _x; }
GLint Coord::y(){ return _y; }
GLint Coord::z(){ return _z; }


GLfloat Coord::fx(){ return _fx; }
GLfloat Coord::fy(){ return _fy; }
GLfloat Coord::fz(){ return _fz; }


/*Increment*/
void Coord::incAll(const GLint delta){ _x += delta; _y += delta; _z += delta;	}
void Coord::incX(const GLint x){ _x += x; }
void Coord::incY(const GLint y){ _y += y; }
void Coord::incZ(const GLint z){ _z += z; }


void Coord::incAll(const GLfloat delta){ _fx += delta; _fy += delta; _fz += delta;	}
void Coord::incX(const GLfloat x){ _fx += x; }
void Coord::incY(const GLfloat y){ _fy += y; }
void Coord::incZ(const GLfloat z){ _fz += z; }


/*Dump*/
void Coord::dump(){
	std::cout << "x = " << (_isInt ? _x : _fx) << std::endl;
	std::cout << "y = " << (_isInt ? _y : _fy) << std::endl;
	std::cout << "z = " << (_isInt ? _z : _fz) << std::endl;
}


