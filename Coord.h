/*
 *  HCoord.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/4/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __HCOORD_H__
#define __HCOORD_H__

//#define DEBUG

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif
#include <iostream>

class Coord{
protected:
	bool _isInt;
	GLint _x, _y, _z;
	GLfloat _fx, _fy, _fz;
		
public:
	
	/*Overiding constructors to real and integer use*/
	Coord(GLint x, GLint y, GLint z): _isInt(true), _x(x), _y(y), _z(z),	_fx(0), _fy(0), _fz(0){
		#ifdef DEBUG
		std::cout << (_isInt ? "is int": "is float") << std::endl; 
		#endif
		
	}
	
	Coord(GLfloat x, GLfloat y, GLfloat z): _isInt(false), _x(0), _y(0), _z(0), _fx(x), _fy(y), _fz(z){
		#ifdef DEBUG
		std::cout << (_isInt ? "is int": "is float") << std::endl; 
		#endif
		
	}
	
	Coord(){}	

	/*Setters*/
	void set(const GLint x, const GLint y, const GLint z);
	void set(const GLfloat x, const GLfloat y, const GLfloat z);
	
	/*Getters*/
	GLint x();
	GLint y();
	GLint z();

	
	GLfloat fx();
	GLfloat fy();
	GLfloat fz();

	
	/*Increment*/
	void incAll(const GLint delta);
	void incX(const GLint x);
	void incY(const GLint y);
	void incZ(const GLint z);
	
	void incAll(const GLfloat delta);
	void incX(const GLfloat x);
	void incY(const GLfloat y);
	void incZ(const GLfloat z);
	
	/*Dump*/
	void dump();	
};





#endif
