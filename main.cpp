/*
 *  main.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/4/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

//#define DEBUG

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif

//#define ORTHO

#include <iostream>

#include <sys/time.h>

#include <vector>
/*#include "Coord.h"
#include "GColor.h"
#include "Drawable.h"
#include "SpaceShip.h"
#include "Alien.h"
#include "Alien2.h"
#include "Shot.h"
#include "Obstacle.h"*/
#include "Controller.h"

Controller *_controller;

void display(){
	_controller->display();
}

void reshape(GLsizei w, GLsizei h){
	_controller->reshape(w, h);
}
void keyboardFunc(unsigned char key, int x, int y){
	_controller->keyboardFunc(key, x, y);
}

void keyboardUpFunc(unsigned char key, int x, int y){
	_controller->keyboardUpFunc(key, x, y);
}

void specialKeyboardFunc(int key, int x, int y){
	_controller->specialKeyboardFunc(key, x, y);
}

void specialKeyboardUpFunc(int key, int x, int y){
	_controller->specialKeyboardUpFunc(key, x, y);
}

void idle(){
	_controller->idle();
}
void idle(int a){
	_controller->idle();
}
//Main App
int main(int argc, char** argv){ 
	_controller = new Controller();
	
	
	
	/*Initialization*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); 
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (-1, -1);
	glutCreateWindow("DO THE ALLIEN SHAKE"); 
	
	glEnable(GL_NORMALIZE);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	
	glShadeModel(GL_SMOOTH); 
	glEnable(GL_DEPTH_TEST);
	
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	
	glEnable(GL_TEXTURE_2D);
	
	/*Event Registration*/
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	
	glutSpecialFunc(specialKeyboardFunc);
	glutSpecialUpFunc(specialKeyboardUpFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutIdleFunc(idle);
	//glutTimerFunc(800, idle, 1);
	

	/*Let it looop mofo!*/
	glutMainLoop();
}




