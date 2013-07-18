/*
 *  Texture.h
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 4/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

//#define DEBUG



#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif
#include <iostream>
#include <fstream>
#include <map>
class Texture{
protected:
	std::map<std::string,GLuint> _textures;

	
public:
	Texture();
	~Texture();
	GLuint loadBitmap(const char *imagepath);
	GLuint getTexture(std::string textName);

};






#endif