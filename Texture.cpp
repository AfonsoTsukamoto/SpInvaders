/*
 *  Texture.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 4/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Texture.h"




Texture::Texture(): _textures(){}
Texture::~Texture(){}


GLuint Texture::loadBitmap(const char * imagepath){
	// Data read from the header of the BMP file
	unsigned char header[54];		// Each BMP file begins by a 54-bytes header
	unsigned int dataPos;			// Position in the file where the actual data begins
	unsigned int width, height;	//Pretty self explanatory
	unsigned int imageSize;			// = width*height*3
	unsigned char * data;			// Actual RGB data
	unsigned int textureID;
	FILE * file = fopen(imagepath,"rb"); //Open file
	if (!file){ 
		std::cerr << "ERROR OPENING BITMAP" << std::endl;
		return -1;
	}
	
	if (fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
		std::cerr << "ERROR READING BITMAP HEADER" << std::endl;
		return -1;
	}
	
	if (header[0]!='B' || header[1]!='M'){
		std::cerr << "ERROR READING BITMAP HEADER" << std::endl;
		return -1;
	}
	
	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);  //Header points to a certain point on the string. Since it calls for the pointed by its memory address,it is the actual pointer.
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	
	

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way
		
	//std::cout << imageSize << "w:" << width << "h:" << height <<std::endl;
	// Create a buffer
	data = new unsigned char [imageSize];
	
	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);
	
	//Everything is in memory now, the file can be closed
	fclose(file);
	
	glPixelStoref( GL_UNPACK_ALIGNMENT, 1);

	// Create one OpenGL textur
	
	glGenTextures(1, &textureID);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	_textures[imagepath] = textureID;
	
	if(gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, data ) != 0){
		std::cerr << "ERROR BUILDING MIPMAP" << std::endl;
		return -1;
	}

	
	return textureID;
	
	
}



GLuint Texture::getTexture(std::string textName){
	return _textures[textName];
}


