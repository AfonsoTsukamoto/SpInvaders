/*
 *  Obstacle.cpp
 *  Lab1
 *
 *  Created by Afonso Tsukamoto on 3/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Obstacle.h"
																							//			 j 0 1 2 3 4 5 6 7 8 9 0 1 2 3	
Obstacle::Obstacle(GLfloat x, GLfloat y, GLfloat z): Drawable(x,y,z){						//	[j][0]	//     + + + + + + + + + +  
	_color = new GColor();																	//	[j][1]	//   + + + + + + + + + + + + 
	_bitMap.resize(14);																		//	[j][2]	// + + + + + + + + + + + + + +
	for(int i = 0;i<14;i++){																//	[j][3] 	// + + + + + + + + + + + + + +
		_bitMap[i].resize(9);																//	[j][4] 	// + + + + + +     + + + + + +
		for(int j = 0;j < 9;j++){															//	[j][5] 	// + + + +             + + + +
			_bitMap[i][j]=true;																//	[j][6] 	// + + +                 + + +
																							//	[j][7] 	// + + +                 + + +
		}																					//	[j][8] 	// + +                     + +
	}
	//Inexistentes
	_bitMap[0][0]=false;
	_bitMap[0][1]=false;
	_bitMap[1][0]=false;
	_bitMap[12][0]=false;
	_bitMap[13][0]=false;
	_bitMap[13][1]=false;
	_bitMap[6][4]=false;
	_bitMap[7][4]=false;
	_bitMap[4][5]=false;
	_bitMap[5][5]=false;
	_bitMap[6][5]=false;
	_bitMap[7][5]=false;
	_bitMap[8][5]=false;	
	_bitMap[9][5]=false;
	_bitMap[3][6]=false;
	_bitMap[4][6]=false;
	_bitMap[5][6]=false;
	_bitMap[6][6]=false;
	_bitMap[7][6]=false;
	_bitMap[8][6]=false;
	_bitMap[9][6]=false;
	_bitMap[10][6]=false;
	_bitMap[3][7]=false;
	_bitMap[4][7]=false;
	_bitMap[5][7]=false;
	_bitMap[6][7]=false;
	_bitMap[7][7]=false;
	_bitMap[8][7]=false;
	_bitMap[9][7]=false;
	_bitMap[10][7]=false;
	_bitMap[2][8]=false;
	_bitMap[3][8]=false;
	_bitMap[4][8]=false;
	_bitMap[5][8]=false;
	_bitMap[6][8]=false;
	_bitMap[7][8]=false;
	_bitMap[8][8]=false;
	_bitMap[9][8]=false;
	_bitMap[10][8]=false;
	_bitMap[11][8]=false;
	_bitMap[12][8]=false;
	killer_counter=50;
}
Obstacle::Obstacle(): Drawable(){
	_color = new GColor();
}

bool Obstacle::collision(Drawable * obj){ 
	return	(
			(obj->right() <= right())
				&&
			(obj->left() >= left())
				&&
			(obj->top() >= bottom())
				&&
			(obj->bottom() <= top())
			)	
			;
}

GColor* Obstacle::getColor(){
	return _color;
}
void Obstacle::setColor(const GLfloat r, const GLfloat g, const GLfloat b){
	_color->setColor(r,g,b);
}
void Obstacle::setColor(int color){
	_color->setColor(color);
}
void Obstacle::drawCube(){
	
	glPushMatrix();//other Transalations are considered outside
	glTranslatef(-0.1875,-0.1875,0.0);
	for(int j=0;j<4;j++){
		glutSolidCube(0.0625);
		glPushMatrix();
		for(int i=0;i<3;i++){
			glTranslatef(0.0625, 0.0, 0.0);
			glutSolidCube(0.0625);
		}
		glPopMatrix();
		glTranslatef(0.0,0.0625,0.0);
	}
	glPopMatrix();
}
void Obstacle::draw(){
	float mcolor[] = {_color->r(), _color->g(), _color->b(), 1.0f };
	GLfloat mat_ambient[] = { _color->r()+0.4f, _color->g()+0.4f, _color->b()+0.4f, 1.0f };
	GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float shininess= 20;
	glMaterialfv (GL_FRONT, GL_AMBIENT, mcolor);
	glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	
	
	glPushMatrix();
		glScalef(1.0f,1.0f,5.0f);
		glTranslatef(_coords->fx(), _coords->fy(), _coords->fz());
			glPushMatrix();
				glTranslatef(0.0, 0.0, 0.0);//Primeira Fila
				if(_bitMap[6][0])
					drawCube();
				glPushMatrix();//Primeira Fila lado Esq
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[5][0])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[4][0])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[3][0])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[2][0])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Primeira Fila lado Dir
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[7][0])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[8][0])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[9][0])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[10][0])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[11][0])
						drawCube();
				glPopMatrix();
				//Segunda Fila
				glTranslatef(0.0, -0.25, 0.0);
				if(_bitMap[6][1])
					drawCube();
				glPushMatrix();//Segunda Fila lado Esq
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[5][1])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[4][1])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[3][1])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[2][1])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[1][1])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Segunda Fila lado Dir
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[7][1])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[8][1])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[9][1])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[10][1])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[11][1])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[12][1])
						drawCube();			
				glPopMatrix();
				//Terceira Fila
				glTranslatef(0.0, -0.25, 0.0);
				if(_bitMap[6][2])
					drawCube();
				glPushMatrix();//Terceira Fila lado Esq
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[5][2])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[4][2])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[3][2])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[2][2])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[1][2])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[0][2])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Terceira Fila lado Dir
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[7][2])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[8][2])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[9][2])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[10][2])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[11][2])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[12][2])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[13][2])
						drawCube();			
				glPopMatrix();
				//Quarta Fila
				glTranslatef(0.0, -0.25, 0.0);
				if(_bitMap[6][3])
					drawCube();
				glPushMatrix();//Terceira Fila lado Esq
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[5][3])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[4][3])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[3][3])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[2][3])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[1][3])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[0][3])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Terceira Fila lado Dir
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[7][3])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[8][3])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[9][3])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[10][3])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[11][3])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[12][3])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[13][3])
						drawCube();			
				glPopMatrix();
				//Quinta Fila
				glTranslatef(0.0, -0.25, 0.0);
				glPushMatrix();//Quinta Fila lado Esq
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[5][4])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[4][4])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[3][4])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[2][4])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[1][4])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[0][4])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Quinta Fila lado Dir
					glTranslatef(0.50, 0.0, 0.0);
					if(_bitMap[8][4])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[9][4])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[10][4])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[11][4])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[12][4])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[13][4])
						drawCube();			
				glPopMatrix();
				//Sexta Fila
				glTranslatef(0.0, -0.25, 0.0);
				glPushMatrix();//Sexta Fila lado Esq
					glTranslatef(-0.75, 0.0, 0.0);
					if(_bitMap[3][5])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[2][5])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[1][5])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[0][5])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Sexta Fila lado Dir
					glTranslatef(1.0, 0.0, 0.0);
					if(_bitMap[10][5])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[11][5])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[12][5])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[13][5])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);	
				glPopMatrix();
				//Sétima Fila
				glTranslatef(0.0, -0.25, 0.0);
				glPushMatrix();//Sétima Fila lado Esq
					glTranslatef(-1, 0.0, 0.0);
					if(_bitMap[2][6])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[1][6])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[0][6])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Sétima Fila lado Dir
					glTranslatef(1.25, 0.0, 0.0);
					if(_bitMap[11][6])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[12][6])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[13][6])
						drawCube();	
				glPopMatrix();
				//Oitava Fila
				glTranslatef(0.0, -0.25, 0.0);
				glPushMatrix();//Oitava Fila lado Esq
					glTranslatef(-1, 0.0, 0.0);
					if(_bitMap[2][7])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[1][7])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[0][7])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Oitava Fila lado Dir
					glTranslatef(1.25, 0.0, 0.0);
					if(_bitMap[11][7])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[12][7])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[13][7])
						drawCube();	
				glPopMatrix();
				//Nona Fila
				glTranslatef(0.0, -0.25, 0.0);
				glPushMatrix();//Nona Fila lado Esq
					glTranslatef(-1.25, 0.0, 0.0);
					if(_bitMap[1][8])
						drawCube();
					glTranslatef(-0.25, 0.0, 0.0);
					if(_bitMap[0][8])
						drawCube();
				glPopMatrix();
				glPushMatrix();//Nona Fila lado Dir
					glTranslatef(1.50, 0.0, 0.0);
					if(_bitMap[12][8])
						drawCube();
					glTranslatef(0.25, 0.0, 0.0);
					if(_bitMap[13][8])
						drawCube();	
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	
}

bool Obstacle::killed(){
	if(killer_counter==136)
		return true;
	return false;
}

bool Obstacle::part_destroyed(float x){
	int i = 8;
	float right,left;
	int arredonda;
	right=x+0.05;
	left=x-0.05;
	while(1){
		//Caso 1:-8.625  right:-5.125
		if(x >= -8.63f && x <= -5.12f){
			arredonda = (int) (( x/0.25 ) + 34.5);
			for(;i>0;i--){//procura primeiro cubo a destruir
				if( _bitMap[arredonda][i] == true)
					break;
			}
			if( _bitMap[arredonda][i] ){
				_bitMap[arredonda][i] = false;
				killer_counter++;
				return true;//Cortou pedaço da barreira
			}
		}
		else if(x >= -3.63f  && x <= -0.120f){
			arredonda = (int) (( x/0.25 ) + 14.5);
			for(;i>0;i--){//procura primeiro cubo a destruir
				if( _bitMap[arredonda][i] == true)
					break;
			}
			if( _bitMap[arredonda][i] ){
				_bitMap[arredonda][i] = false;
				killer_counter++;
				return true;//Cortou pedaço da barreira
			}
		}else if(x >= 1.33f  && x <= 4.88f){
			arredonda = (int) (( x/0.25 ) - 5.5);
			for(;i>0;i--){//procura primeiro cubo a destruir
				if( _bitMap[arredonda][i] == true)
					break;
			}
			if( _bitMap[arredonda][i] ){
				_bitMap[arredonda][i] = false;
				killer_counter++;
				return true;//Cortou pedaço da barreira
			}	
		}
		else if(x >= 6.36f  && x <= 9.88f){
			arredonda = (int) (( x/0.25 ) - 25.5);
			for(;i>0;i--){//procura primeiro cubo a destruir
				if( _bitMap[arredonda][i] == true)
					break;
			}
			if( _bitMap[arredonda][i] ){
				_bitMap[arredonda][i] = false;
				killer_counter++;
				return true;//Cortou pedaço da barreira
			}
		}
		if(x==right)
			x=left;
		else if(x==(right-0.05))
			x=right;
		else
			return false;
	}
	return false;
}

bool Obstacle::alien_damage(float x){
	int i = 8;
	float right,left;
	int arredonda;
	right=x+0.05;
	left=x-0.05;
	while(1){
		if(x==2)
			x=left;
		//Caso 1:-8.625  right:-5.125
		if(x >= -8.625 && x <= -5.125){
			arredonda = (int) (( x/0.25 ) + 34.5);
			for(i=0;i<9;i++){//procura primeiro cubo a destruir
				if( _bitMap[arredonda][i] == true)
					break;
			}
			if( _bitMap[arredonda][i] ){
				_bitMap[arredonda][i] = false;
				killer_counter++;
				return true;//Cortou pedaço da barreira
			}
		}else if(x >= -3.625  && x <= -0.125){
			arredonda = (int) (( x/0.25 ) + 14.5);
			for(i=0;i<9;i++){//procura primeiro cubo a destruir
				if( _bitMap[arredonda][i] == true)
					break;
			}
			if( _bitMap[arredonda][i] ){
				_bitMap[arredonda][i] = false;
				killer_counter++;
				return true;//Cortou pedaço da barreira
			}
		}else if(x >= 1.375  && x <= 4.875){
			arredonda = (int) (( x/0.25 ) - 5.5);
			for(i=0;i<9;i++){//procura primeiro cubo a destruir
				if( _bitMap[arredonda][i] == true)
					break;
			}
			if( _bitMap[arredonda][i] ){
				_bitMap[arredonda][i] = false;
				killer_counter++;
				return true;//Cortou pedaço da barreira
			}
		}else if(x >= 6.375  && x <= 9.875){
			arredonda = (int) (( x/0.25 ) - 25.5);
			for(i=0;i<9;i++){//procura primeiro cubo a destruir
				if( _bitMap[arredonda][i] == true)
					break;
			}
			if( _bitMap[arredonda][i] ){
				_bitMap[arredonda][i] = false;
				killer_counter++;
				return true;//Cortou pedaço da barreira
			}
		}
		if(x==right)
			x=left;
		else if(x==(right-0.05))
			x=right;
		else
			return false;
	}
	
}

float Obstacle::left(){
	return _coords->fx()-1.625;
}
float Obstacle::right(){
	return _coords->fx()+1.875;
}

float Obstacle::bottom(){
	return _coords->fy()-0.875;
}

float Obstacle::top(){
	return _coords->fy()+0.125;
}

