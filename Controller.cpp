/*
 *  Controller.cpp
 *  CGProjMerge
 *
 *  Created by Afonso Tsukamoto on 4/9/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */



/*
 TODOs
 
 -DONE! Alien shoot: Choose random x,y inside number of aliens. Update position must check if ship is on the way. 
 
 -Fix spaceship translation. delta time is (probably) the problem. 
 
 
 */


#include "Controller.h"

Controller::Controller():_right(true),													//Two booleans for the alien move controll- See if is going right
								 _down(false),													//See if alien's moving down
								 _limits(10.0),												//Board Limits considering the center
								 _shipMovingRatio(0.0079),									//Ship's velocity
								 _alienMovingRatio(9),								//Alien's velocity
								 _shotMovingRatio(0.01),									//Shot's velocity
								 _numbAliens(11),												//Number of aliens
							    _timesPressed(0),											//Variable to save the number of times the space has been pressed
								 _alienShootCounter(0),										//Variable to save the number of alien shoots (comes from a random call
								 _points(0),
								 _camera(ORTHOGONAL_CAM),									//The camera state
								 _lastTime(glutGet(GLUT_ELAPSED_TIME)),				//Last time the processor has been Idle (to find the delta time)
								 _lastAlienFootMove(glutGet(GLUT_ELAPSED_TIME)),	//Last time the aliens have been changed/moved
								 _keyStates(new bool[256]),								//Vector to check wich keys (ascii) have been pressed
								 _keySpecialStates(new bool[2]),							//Vector to check wich keys (non ascii) have been pressed
								 _shipStroke(false),											//Ship stroke - active when the ship loses a life
								 _shipStrokeCounter(0),										//A counter for the number of strokes
								 _alienShoot(true),											//Bool to maintain the aliens shooting strike - off when ship loses life 
								 _bgTexture(0),												//Variable to save the background texture
								 _directionY(1.0),
								 _textured(false),											//Check if textures have been initialized
								 _motionBefore(MOTION_STOPPED){
									
									 
	initGame();	
}
Controller::~Controller(){
	//TODO	
}

void Controller::HUD() const
{
    // Switch to raster mode (saving active projection)
    glDisable( GL_TEXTURE_2D);
    glMatrixMode( GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0, glutGet( GLUT_WINDOW_WIDTH), 0, glutGet( GLUT_WINDOW_HEIGHT));
    glMatrixMode( GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    int dirtyHack=0;
   glColor3f( 0., 0., 1.);
   float mcolor[] = {1.0f,1.0f, 1.0f, 1.0f };
	GLfloat mat_ambient[] = { 1.0f,1.0f, 1.0f, 1.0f };
	GLfloat mat_emission[] = {1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float shininess= 100;
	glMaterialfv (GL_FRONT, GL_AMBIENT, mcolor);
	glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	ostringstream os;
	if(glutGet( GLUT_WINDOW_WIDTH)==600)
		dirtyHack=180;
	else
		dirtyHack=glutGet(GLUT_WINDOW_WIDTH)/2 -180;
	
    os << setprecision( 1) << "Pontuation: " << _points << " Number of lifes: " << _ship->getLives();
    DisplayString( dirtyHack, glutGet( GLUT_WINDOW_HEIGHT)-20, os.str(), GLUT_BITMAP_HELVETICA_18);

	GLuint h = glutGet(GLUT_WINDOW_HEIGHT);
	GLuint w = glutGet(GLUT_WINDOW_WIDTH);

	glMaterialfv (GL_FRONT, GL_AMBIENT, mcolor);
	glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glPushMatrix();
	glNormal3f(0.0, 0.0, 1.0);
	
	glBegin(GL_LINE_STRIP);
	/*             x     y   */
	glVertex2f( (w/2)-360.0, h-20.0);
	glVertex2f( (w/2)-360.0, h);
	glVertex2f( (w/2)+360.0, h);
	glVertex2f( (w/2)+360.0, h-20.0);
	glVertex2f( (w/2)-360.0, h-20.0);
	glEnd();
	glPopMatrix();
    glMatrixMode( GL_PROJECTION);
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW);
    glPopMatrix();
    glEnable( GL_TEXTURE_2D);
}
void Controller::DisplayString( const int x, const int y, const string &label, const void * font) const
{
    void * fontToUse = (font != NULL) ? (void*) font : GLUT_BITMAP_HELVETICA_12;
    glRasterPos2i( x, y);
    for ( int i=0; i<(int)label.size(); i++)
        glutBitmapCharacter( fontToUse, label[i]);
}

void Controller::initGame(){
#ifdef MOTION_SENSOR
	//THIS IS OBJECTIVE CPP!
	initMotionSensor();
	_motionBefore = MOTION_STOPPED;
	updateXMotion();
	_motionPosBefore = getXMotion();;
#endif
	srand((unsigned)time(0));
	_totalAliens = _numbAliens * 5;
	GLfloat j = -8.0;
	#ifdef DEBUG
	std::cout << "init!" << std::endl;
	#endif
	for(size_t i = 0; i < _numbAliens; i++){
		Alien *aux = new Alien(j, 7.0, 0.0, 10.0f);
		aux->setColor(C_BLUE);
		_aliens1.push_back(aux);
		if(i==0){
			_aliensLeft = _aliensLeftInit = aux->left();
		}
		if(i==(_numbAliens-1)){
			_aliensRight = _aliensRightInit = aux->right();
		}
		j+=1.5;
	}
		
	j= -8.0;
	for(size_t i = 0; i < _numbAliens; i++){
		Alien *aux = new Alien(j, 5.0, 0.0, 10.0f);
		aux->setColor(C_GREEN);
		_aliens2.push_back(aux);
		j+=1.5;
	}
		
	j= -8.0;
	for(size_t i = 0; i < _numbAliens; i++){
		Alien *aux = new Alien(j, 3.0, 0.0, 10.0f);
		aux->setColor(C_YELLOW);
		_aliens3.push_back(aux);
		j+=1.5;
	}
	
	j= -8.0;
	for(size_t i = 0; i < _numbAliens; i++){
		Alien *aux = new Alien(j, 1.0, 0.0, 10.0f);
		aux->setColor(C_RED);
		_aliens4.push_back(aux);
		j+=1.5;
	}
		
	j= -8.0;
	for(size_t i = 0; i < _numbAliens; i++){
		Alien *aux = new Alien(j, -1.0, 0.0, 10.0f);
		aux->setColor(C_RED);
		_aliens5.push_back(aux);
		j+=1.5;
	}
		
	j=-7.0;
	for(size_t i = 0; i < 4; i++){
		Obstacle *aux = new Obstacle(j, -4.0, 0.0);
		aux->setColor(C_WHITE);
		_obstacles.push_back(aux);
		j+=5.0;
	}
	
	//SpaceShip const: (x,y,z,lives, limits)
	_ship = new SpaceShip(0.0f,-8.0f,0.0f, 5, 10.0f); 
	_ship->setColor(C_RED);
	
	j=9.0;
	for(size_t i = 0; i < _ship->getLives(); i++){
		SpaceShip *aux = new SpaceShip(j,-9.5f,0.0f); 
		aux->setColor(C_RED);
		_livesDraws.push_back(aux);
		j-=2.5;
	}
	
	if(_aliens1.size() != 0 && _aliens2.size() != 0 && _aliens3.size() != 0 && _aliens4.size() != 0 && _aliens5.size() != 0){
		#ifdef DEBUG
		std::cout << "INIT RUNNED SUCCESSFULLY\n"<<std::endl;
		#endif
	}
	for(size_t i = 0; i<256; i++){
		_keyStates[i] = false;
	}
	for(size_t i = 0; i<2; i++){
		_keySpecialStates[i] = false;
	}
	
	
	//Sound Stuff
	
	cSharp.loadFromFile("SP_C#.wav");
	gSharp.loadFromFile("SP_G#.wav");
	alienSound.setVolume(50);
	shotSound.loadFromFile("SP_Shot.wav");
	shotsSounds.setVolume(40);
	shotsSounds.setBuffer(shotSound);
	
	
	
	
	
	/*/////////////////////////
	
	//Texture mapping
	
	// allocate a texture name
	glGenTextures( 1, &_bgTexture);
	
	// select our current texture
	glBindTexture( GL_TEXTURE_2D, _bgTexture);
	
	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	
	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
						 GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the original
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	// the texture wraps over at the edges (repeat)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	
	////////////////////////*/
	
}

void Controller::draw(){
	ParticleSystem * particleAux;
	createTexture();
	
	if(_aliens1.size() == 0 && _aliens2.size() == 0 && _aliens3.size() == 0 && _aliens4.size() == 0 && _aliens5.size() == 0){
		drawText("YOU WINNNNNNNNN!!!");	
	}
	
	glPushMatrix();
	glScalef(1.0f, 1.0f, 2.5f); //TODO - this is a hack! Should'nt be done like this
	for(size_t i = 0; i<_particlePack.size(); i++){
		_particlePack[i]->Update(deltaTime());
		if(_particlePack[i]->stillAlive()){
			particleAux=_particlePack[i];
			_particlePack.erase(_particlePack.begin()+i);
		 	delete particleAux;
		}
		else{
			glPushMatrix();
			_particlePack[i]->Draw();
			Particle::CreateParticleSkeleton();
    		//Particle::LoadTexture( "256.bmp");
			glPopMatrix();
			}
	}

	for(size_t i = 0; i<_obstacles.size(); i++){
		_obstacles[i]->draw();
	}
	for(size_t i = 0; i < _shoots.size(); i++){
		_shoots[i]->draw();
	}
	for(size_t i = 0; i < _alienShoots.size(); i++){
		_alienShoots[i]->draw();
	}
	for(size_t i = 0; i < _aliens1.size(); i++){
		_aliens1[i]->draw();
	}
	for(size_t i = 0; i < _aliens2.size(); i++){
		_aliens2[i]->draw();
	}	
	for(size_t i = 0; i < _aliens3.size(); i++){
		_aliens3[i]->draw();
	}	
	for(size_t i = 0; i < _aliens4.size(); i++){
		_aliens4[i]->draw();
	}
	for(size_t i = 0; i < _aliens5.size(); i++){
		_aliens5[i]->draw();
	}
	
	
	
	if(_shipStroke){
		if(_shipStrokeCounter <=6){
			if((_shipStrokeCounter %2) != 0){
				_ship->draw();
				
			}
			//glutTimerFunc(250, incStrokeCounter, 1);
			_shipStrokeCounter++;
		}else{
			_shipStroke = false;
			_shipStrokeCounter = 0;
			_alienShoot = true;
		}
			
	}else{
		_ship->draw();
	}
	

	for(size_t i = 0; i < _livesDraws.size(); i++){
		_livesDraws[i]->draw();
	}
	glPopMatrix();
}
/*
static void Controller::incStrokeCounter(){
	_shipStrokeCounter++;
}
*/

//TODO different shoots for the aliens (hence the type variable)
void Controller::shoot(float x, float y, float z, int type){
	
	
	if(type == ALIEN_SHOOT){
		AlienShot *alien = new AlienShot(x,y,z);
		_alienShoots.push_back(alien);
	}
	if(type == SHIP_SHOOT){
		Shot *_shoot = new Shot(x,y,z);
		_shoots.push_back(_shoot);
	}
}

void Controller::shootMove(){
	Alien *alienAux;
	Obstacle *obstacleAux;
	Shot *shotAux;

	
	for(size_t i = 0; i < _shoots.size(); i++){
		/*Se os tiros sairem do ecrã (world system coordinates) devem ser apagados*/
		/*TODO - Ver se conseguimos mudar isto para reaproveitar os tiros e não andar sempre a alocar e a fazer free à memoria*/

		if(_shoots[i]->bottom() >= 20){
		 shotAux = _shoots[i];
		 _shoots.erase(_shoots.begin()+i);
		 delete shotAux;
		 } 
		
		
		if( ( i < _shoots.size() ) && (_obstacles.size() != 0) && (_obstacles[0]->getPosition()->fy() <= _shoots[i]->top()) ){
			for(int j = 0; j <  _obstacles.size(); j++){
				if(( (size_t) j < _obstacles.size())
						&& 
					_obstacles[j]->collision(_shoots[i])
					)
				{
					if(_obstacles[j]->part_destroyed(_shoots[i]->pos())){
						if(_obstacles[j]->killed()){

							ParticleSystem *aux = new ParticleSystem(true,_obstacles[j]); 
							obstacleAux = _obstacles[j]; 
							_obstacles.erase(_obstacles.begin()+j);
							delete obstacleAux;
							_particlePack.push_back(aux);
							aux->Draw();
						}
						shotAux = _shoots[i];
						_shoots.erase(_shoots.begin()+i);
						delete shotAux;
						break;
					}
				}	
			}
		}
		
		for(int j = 0; j < _numbAliens; j++){
				if( 
					( (size_t) j < _aliens1.size() ) && ( i < _shoots.size() ) && _aliens1[j]->collision(_shoots[i])
				)
			{			
				alienAux = _aliens1[j];
					
				ParticleSystem *aux = new ParticleSystem(true,_aliens1[j]); 
				_aliens1.erase(_aliens1.begin()+j);
				_points+=10;
				delete alienAux;
				_totalAliens--;
				shotAux = _shoots[i];
				_shoots.erase(_shoots.begin()+i);
				delete shotAux;
				_particlePack.push_back(aux);
				aux->Draw();
				break;
			}
			if(( (size_t) j<_aliens2.size())
				&&
					(i < _shoots.size())
				&& 
					_aliens2[j]->collision(_shoots[i])
				)
			{
				alienAux = _aliens2[j];
				ParticleSystem *aux = new ParticleSystem(true,_aliens2[j]); 
				_aliens2.erase(_aliens2.begin()+j);
				_points+=10;
				delete alienAux;
				_totalAliens--;
				shotAux = _shoots[i];
				_shoots.erase(_shoots.begin()+i);
				delete shotAux;
				_particlePack.push_back(aux);
				aux->Draw();
				break;
			}
			if(( (size_t) j<_aliens3.size())
				&&
				(i < _shoots.size())
				&& 
				_aliens3[j]->collision(_shoots[i])
				)
			{			
				alienAux = _aliens3[j];
				ParticleSystem *aux = new ParticleSystem(true,_aliens3[j]); 
				_aliens3.erase(_aliens3.begin()+j);
				_points+=10;
				delete alienAux;
				_totalAliens--;
				shotAux = _shoots[i];
				_shoots.erase(_shoots.begin()+i);
				delete shotAux;
				_particlePack.push_back(aux);
				aux->Draw();
				break;
			}
			if(( (size_t) j<_aliens4.size())
				&&
				(i < _shoots.size())
				&& 
				_aliens4[j]->collision(_shoots[i])
				)
			{
				alienAux = _aliens4[j];
				ParticleSystem *aux = new ParticleSystem(true,_aliens4[j]); 
				_aliens4.erase(_aliens4.begin()+j);
				delete alienAux;
				_totalAliens--;
				shotAux = _shoots[i];
				_shoots.erase(_shoots.begin()+i);
				delete shotAux;
				_particlePack.push_back(aux);
				aux->Draw();
				break;
			}
			if(( (size_t) j<_aliens5.size())
				&&
				(i < _shoots.size())
				&& 
				_aliens5[j]->collision(_shoots[i])
				)
			{	
				alienAux = _aliens5[j];
				ParticleSystem *aux = new ParticleSystem(true,_aliens5[j]); 
				_aliens5.erase(_aliens5.begin()+j);
				_points+=10;
				delete alienAux;
				_totalAliens--;
				shotAux = _shoots[i];
				_shoots.erase(_shoots.begin()+i);
				delete shotAux;
				_particlePack.push_back(aux);
				aux->Draw();
				break;
			}
			
		}
		//}//End of checking minimum y for colision
		
	}//End of _shoots iteration
	
	for(size_t i = 0; i<_shoots.size(); i++){
		_shoots[i]->updatePosition(0.0,(_shotMovingRatio*deltaTime()),0.0);
	}
}
void Controller::collisionTesting(){
	Alien *alienAux;
	Obstacle *obstacleAux;
	//testar se aliens batem nos obs
	//testar se aliens batem na nave
	
		for(int i = 0; i < _numbAliens; i++){
			
			if( _obstacles.size() != 0 ){
				if( ( i <  _aliens5.size() ) && ( 0 <  _obstacles.size() ) && (_obstacles[0]->getPosition()->fy() <= _aliens5[i]->bottom()) ){
					for(int j = 0; j < _obstacles.size(); j++){
						//std::cout<< "OBS_SIZE: " <<_obstacles.size()<<"ALIEN_SIZE: " << _aliens5.size()<<std::endl;
						if( _obstacles[j]->collision(_aliens5[i]) )
						{	obstacleAux = _obstacles[j]; 
							ParticleSystem *aux = new ParticleSystem(true,_obstacles[j]);
							_obstacles.erase(_obstacles.begin()+j);
							delete obstacleAux;
							alienAux = _aliens5[i];
							_aliens5.erase(_aliens5.begin()+i);
							delete alienAux;
							
							_particlePack.push_back(aux);
							aux->Draw();
							break;
						}	
					}
				}
				else if( ( i <  _aliens4.size() ) && ( 0 <  _obstacles.size() ) && (_obstacles[0]->getPosition()->fy() <= _aliens4[i]->bottom()) ){
					for(int j = 0; j < _obstacles.size(); j++){
						if(  _obstacles[j]->collision(_aliens4[i]) )
						{
							obstacleAux = _obstacles[j];
 							ParticleSystem *aux = new ParticleSystem(true,_obstacles[j]);
							_obstacles.erase(_obstacles.begin()+j);
							delete obstacleAux;
							alienAux = _aliens4[i];
							_aliens4.erase(_aliens4.begin()+i);
							delete alienAux;
							_particlePack.push_back(aux);
							aux->Draw();
							break;
						}	
					}
				}
				else if( ( i <  _aliens3.size() )&& ( 0 <  _obstacles.size() ) && (_obstacles[0]->getPosition()->fy() <= _aliens3[i]->bottom()) ){
					for(int j = 0; j < _obstacles.size(); j++){
						if(  _obstacles[j]->collision(_aliens3[i]) )
						{
							obstacleAux = _obstacles[j]; 
							ParticleSystem *aux = new ParticleSystem(true,_obstacles[j]);
							_obstacles.erase(_obstacles.begin()+j);
							delete obstacleAux;
							alienAux = _aliens3[i];
							_aliens3.erase(_aliens3.begin()+i);
							delete alienAux;
							_particlePack.push_back(aux);
							aux->Draw();
							break;
						}	
					}
				}
				else if( ( i <  _aliens2.size() )&& ( 0 <  _obstacles.size() ) && (_obstacles[0]->getPosition()->fy() <= _aliens2[i]->bottom()) ){
					for(int j = 0; j < _obstacles.size(); j++){
						if( _obstacles[j]->collision(_aliens2[i]) )
						{
							obstacleAux = _obstacles[j]; 
							ParticleSystem *aux = new ParticleSystem(true,_obstacles[j]); 
							_obstacles.erase(_obstacles.begin()+j);
							delete obstacleAux;
							alienAux = _aliens2[i];
							_aliens2.erase(_aliens2.begin()+i);
							delete alienAux;
							_particlePack.push_back(aux);
							aux->Draw();
							break;
						}	
					}
				}
				else if( ( i <  _aliens1.size() )&& ( 0 <  _obstacles.size() ) && (_obstacles[0]->getPosition()->fy() <= _aliens1[i]->bottom()) ){
					for(int j = 0; j < _obstacles.size(); j++){
						if( _obstacles[j]->collision(_aliens1[i]) )
						{
							obstacleAux = _obstacles[j]; 
							ParticleSystem *aux = new ParticleSystem(true,_obstacles[j]); 
							_obstacles.erase(_obstacles.begin()+j);
							delete obstacleAux;
							alienAux = _aliens1[i];
							_aliens1.erase(_aliens1.begin()+i);
							delete alienAux;
							_particlePack.push_back(aux);
							aux->Draw();
							break;
						}	
					}
				}
			}
			if(( i <  _aliens5.size() ) && (_ship->getPosition()->fy() <= _aliens5[i]->bottom()) ){
					if(  _ship->collision(_aliens5[i]) )
					{	ParticleSystem *aux = new ParticleSystem(true,_ship); 
						_ship->setLives(0);
						_particlePack.push_back(aux);
						aux->Draw();
					}	
			}
			else if(( i <  _aliens4.size() ) && (_ship->getPosition()->fy() <= _aliens4[i]->bottom()) ){
					if(  _ship->collision(_aliens4[i]) )
					{
						ParticleSystem *aux = new ParticleSystem(true,_ship); 
						_ship->setLives(0);
						_particlePack.push_back(aux);
						aux->Draw();
					}	
			}
			else if(( i <  _aliens3.size() ) && (_ship->getPosition()->fy() <= _aliens3[i]->bottom()) ){
					if(  _ship->collision(_aliens3[i]) )
					{
						ParticleSystem *aux = new ParticleSystem(true,_ship); 
						_ship->setLives(0);
						_particlePack.push_back(aux);
						aux->Draw();
					}	
			}
			else if(( i <  _aliens2.size() ) && (_ship->getPosition()->fy() <= _aliens2[i]->bottom()) ){
					if(  _ship->collision(_aliens2[i]) )
					{
						ParticleSystem *aux = new ParticleSystem(true,_ship); 
						_ship->setLives(0);
						_particlePack.push_back(aux);
						aux->Draw();
					}	
			}
			else if(( i <  _aliens1.size() ) && (_ship->getPosition()->fy() <= _aliens1[i]->bottom()) ){
					if(  _ship->collision(_aliens1[i]) )
					{
						ParticleSystem *aux = new ParticleSystem(true,_ship); 
						_ship->setLives(0);
						_particlePack.push_back(aux);
						aux->Draw();
					}	
			}
		}
}	

void Controller::alienMove(){
	bool flag=false;
	float bigger=0.0, smaller=0.0;
	if(_right && !_down){ //Going to the right
			#ifdef DEBUG
			std::cout << "RIGHTTTT"<< std::endl;
			#endif
			for(size_t i = 0; i < _aliens1.size(); i++){
				_aliens1[i]->updatePosition(0.275,0.0,0.0);
				bigger = BIGGER(bigger,_aliens1[i]->right());
			}
			for(size_t i = 0; i < _aliens2.size(); i++){
				_aliens2[i]->updatePosition(0.275,0.0,0.0);
				bigger = BIGGER(bigger,_aliens2[i]->right());
			}
			for(size_t i = 0; i < _aliens3.size(); i++){
				_aliens3[i]->updatePosition(0.275,0.0,0.0);
				bigger = BIGGER(bigger,_aliens3[i]->right());
			}
			for(size_t i = 0; i < _aliens4.size(); i++){
				_aliens4[i]->updatePosition(0.275,0.0,0.0);
				bigger = BIGGER(bigger,_aliens4[i]->right());
			}
			for(size_t i = 0; i < _aliens5.size(); i++){
				_aliens5[i]->updatePosition(0.275,0.0,0.0);
				bigger = BIGGER(bigger,_aliens5[i]->right());
			}
		if(bigger >=_limits){
		//next mode is down right
			_down = _right = true;
		}
		
	}
	if( (_right && _down) || (_down && !_right) ){ //down on the right and leftside
		   #ifdef DEBUG
			std::cout << "DOWWWNNNNNN"<< std::endl;
			#endif
			for(size_t i = 0; i < _aliens1.size(); i++){
				_aliens1[i]->updatePosition(0.0,-0.275,0.0);
			}
			for(size_t i = 0; i < _aliens2.size(); i++){
				_aliens2[i]->updatePosition(0.0,-0.275,0.0);
			}
			for(size_t i = 0; i < _aliens3.size(); i++){
				_aliens3[i]->updatePosition(0.0,-0.275,0.0);
			}
			for(size_t i = 0; i < _aliens4.size(); i++){
				_aliens4[i]->updatePosition(0.0,-0.275,0.0);
			}
			for(size_t i = 0; i < _aliens5.size(); i++){
				_aliens5[i]->updatePosition(0.0,-0.275,0.0);
			}
		if(_right && _down){
			_down = _right = false; //next mode is left
		}else{						   
			_down = false;				//next mode is right
			_right = true;
		}
	}
	if(!_right && !_down){ //To the left
		flag = false;
			#ifdef DEBUG
			std::cout << "LEFTTTTTT"<< std::endl;
			#endif
			for(size_t i = 0; i < _aliens1.size(); i++){
				_aliens1[i]->updatePosition(-0.275,0.0,0.0);
				smaller = SMALLER(smaller,_aliens1[i]->left());
			}
			for(size_t i = 0; i < _aliens2.size(); i++){
				_aliens2[i]->updatePosition(-0.275,0.0,0.0);
				smaller = SMALLER(smaller,_aliens2[i]->left());
			}
			for(size_t i = 0; i < _aliens3.size(); i++){
				_aliens3[i]->updatePosition(-0.275,0.0,0.0);
				smaller = SMALLER(smaller,_aliens3[i]->left());
			}
			for(size_t i = 0; i < _aliens4.size(); i++){
				_aliens4[i]->updatePosition(-0.275,0.0,0.0);
				smaller = SMALLER(smaller,_aliens4[i]->left());
			}
			for(size_t i = 0; i < _aliens5.size(); i++){
				_aliens5[i]->updatePosition(-0.275,0.0,0.0);
				smaller = SMALLER(smaller,_aliens5[i]->left());
			}
		if(smaller <= (-_limits)){
			//next mode is down left
			_down = true;
			_right= false;
		}
	}
	
	if(_footState){
		alienSound.setBuffer(cSharp);
	}else {
		alienSound.setBuffer(gSharp);
	}

	alienSound.play();	
	//sf::sleep(sf::milliseconds(200));
	//draw();
	glutPostRedisplay();
	//glutTimerFunc(8000, alienShake, 1);

}



void Controller::alienShootMove(){
	
	Alien *alienAux;
	Obstacle *obstacleAux;
	Shot *shotAux;
	AlienShot *aAux;
	for(size_t i = 0; i<_alienShoots.size(); i++){
		
		if(
			(i < _alienShoots.size()) 
				&&	
			_ship->collision(_alienShoots[i])
			)
		{
			aAux = _alienShoots[i];
			
			_livesDraws.erase(_livesDraws.begin()+(_ship->getLives()-1));
			_ship->decLives();
			ParticleSystem *aux = new ParticleSystem(true,_ship); 
			_particlePack.push_back(aux);
			aux->Draw();
			_shipStroke = true;
			_alienShoot=false;
			_alienShoots.erase(_alienShoots.begin()+i);
			delete aAux;
			
		}
		for(int j = 0; j <  _obstacles.size(); j++){
			if(( (size_t) j < _obstacles.size())
				&&
				(i < _alienShoots.size()) 
				&&	
				_obstacles[j]->collision(_alienShoots[i])
				)

			{	
				if(_obstacles[j]->alien_damage(_alienShoots[i]->pos())){
					if(_obstacles[j]->killed()){
						obstacleAux = _obstacles[j];
						ParticleSystem *aux = new ParticleSystem(true,_obstacles[j]);
						_obstacles.erase(_obstacles.begin()+j);
						delete obstacleAux;						 
						_particlePack.push_back(aux);
						aux->Draw(); 
					}
					aAux = _alienShoots[i];
					_alienShoots.erase(_alienShoots.begin()+i);
					delete aAux;
					break;
				}
			}	
		}
		_alienShoots[i]->updatePosition(0.0,-(_shotMovingRatio*deltaTime()),0.0);
		
	}
	
	
}

void Controller::alienStartShoot(Alien *a){
	int nShoots=1;
	if((glutGet(GLUT_ELAPSED_TIME)%2) == 0)
		nShoots = 2;
	
	for(int i = 0;i<nShoots; i++){
		shoot(a->getPosition()->fx(), a->getPosition()->fy(), a->getPosition()->fz(), ALIEN_SHOOT);
	}

}

void Controller::alienShoot(){
	bool alienFound=false;
	int rX,rY;
	
	while(!alienFound){
		rX = (rand()%11);
		#ifdef DEBUG
		std::cout << "Random - x: " << rX << " y: " << rY << std::endl;
		#endif
		
		if(_aliens5.size() > 0)
			rY = 5;
		else
			if(_aliens4.size() > 0)
				rY = 4;
			else
				if(_aliens3.size() > 0)
					rY = 3;
				else
					if(_aliens2.size() > 0)
						rY = 2;
					else
						if(_aliens1.size() > 0)
							rY = 1;
		
		if(_allDead)
			break;
		
		if(rY == 1){
			if(rX < _aliens1.size()){
				alienFound = true;
				alienStartShoot(_aliens1[rX]);
			}
		}else
		if(rY == 2){
			if(rX < _aliens2.size()){
				alienFound = true;
				alienStartShoot(_aliens2[rX]);				
			}
		}else
		if(rY == 3){
			if(rX < _aliens3.size()){
				alienFound = true;
				alienStartShoot(_aliens3[rX]);
			}
		}else
		if(rY == 4){
			if(rX < _aliens4.size()){
				alienFound = true;
				alienStartShoot(_aliens4[rX]);
			}
		}else
		if(rY == 5){
			if(rX < _aliens5.size()){
				alienFound = true;
				alienStartShoot(_aliens5[rX]);
			}
		}
	
	}
}
		

void Controller::alienDance(){
	for(size_t i = 0; i < _aliens1.size(); i++){
		_aliens1[i]->reactFoots();
		_footState = _aliens1[i]->footsUp();
	}
	for(size_t i = 0; i < _aliens2.size(); i++){
		_aliens2[i]->reactFoots();
	}
	for(size_t i = 0; i < _aliens3.size(); i++){
		_aliens3[i]->reactFoots();
	}
	for(size_t i = 0; i < _aliens4.size(); i++){
		_aliens4[i]->reactFoots();
	}
	for(size_t i = 0; i < _aliens5.size(); i++){
		_aliens5[i]->reactFoots();
	}
	
	_lastAlienFootMove = glutGet(GLUT_ELAPSED_TIME);
	
	glutPostRedisplay();

}


void Controller::initLighting(){
	
	//GLfloat asp= glutGet(GLUT_WINDOW_WIDTH)/glutGet(GLUT_WINDOW_HEIGHT);
	GLfloat lightPosition[] = {0.0f, -12.0f, 10.0f, 1.0f};
	GLfloat whiteSpecularLight[] = {0.9f, 0.9f, 0.9f, 1.0f}; 
	GLfloat whiteAmbientLight[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat whiteDiffuseLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat difspec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat direction[] = {0.0f, _directionY, -1.0f, 1.0};
	GLfloat px = _ship->posX();
	GLfloat py = _ship->posY();
	GLfloat pz = _ship->posZ();
	GLfloat posi[] = {px, py, pz, 1.0f};
	GLfloat pos[] = {0.0f, 0.0f, 10.0f, 1.0f};
	GLfloat white[] = {0.6f, 0.6f, 0.6f, 1.0f}; 
	GLfloat lmodel_ambient[] ={0.1f,0.1f,0.1f,1.0f}; 
	//std::cout << _ship->posX() <<"y: "<< _ship->posY() << std::endl;
	glPushMatrix();
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	
	
	glLightfv(GL_LIGHT1, GL_SPECULAR, difspec);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, difspec);
	
	
	glLightfv(GL_LIGHT1, GL_POSITION, posi);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0f); // 0~180
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, .2f); // 0~128
	
	glPopMatrix();

}

void Controller::display(void){
	//GLfloat aspect =(GLfloat)WIDTH / (GLfloat)HEIGHT;	
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	initLighting();
		
	if(_camera == ORTHOGONAL_CAM){
		gluLookAt(0, 0, 5, /* look from camera XYZ */
					 0, 0, 0, /*look at the origin */
					 0, 1, 0); /* positive Y up vector*/
	}else
	if(_camera == PERSPECTIVE_BEHIND){
		gluLookAt(_ship->posX(), _ship->posY()-4, _ship->posZ()+4, /* look from camera XYZ */
					 _ship->posX(), 0, 0, /*look at the origin */
					 0, 0, 1); /* positive Y up vector*/
		
	}else
	if(_camera == PERSPECTIVE_FIRST_PERSON){
		gluLookAt(_ship->posX(), _ship->posY(), _ship->posZ()+4, /* look from camera XYZ */
					 _ship->posX(), 0, 0, /*look at the origin */
					 0, 0, 1); /* positive Y up vector*/
		
		/* abs((_ship->getPosition()->fy()*_ship->getPosition()->fz())-((_ship->getPosition()->fz()+1)*_ship->getPosition()->fy()+4)),
					 abs(((_ship->getPosition()->fz()+1)*_ship->getPosition()->fx())-(_ship->getPosition()->fx()*_ship->getPosition()->fz())),
					 abs((_ship->getPosition()->fx()*(_ship->getPosition()->fy()+4))-(_ship->getPosition()->fy()*_ship->getPosition()->fx())));  positive Y up vector*/
	}else{
		throw("UNSUPORTED CAMERA MODE!\n");
	}
	
	if(_ship->getLives() > 0){
		draw();
	}else{
		alienSound.setVolume(0);
		shotsSounds.setVolume(0);
		drawText("THAT ALLIEN JUST KILLED YOU MATE!");
	}
	HUD();
	glFlush();
	glutSwapBuffers();

}
void Controller::reshape(GLsizei w, GLsizei h){
	GLfloat aspect;
	
	if(h == 0) h = 1;	
	_width = glutGet(GLUT_WINDOW_WIDTH);
	_height = glutGet(GLUT_WINDOW_HEIGHT);
	aspect = (GLfloat)_width/(GLfloat)_height;
	
	glViewport(0, 0, _width, _height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(_camera == ORTHOGONAL_CAM){
		if (aspect>= 1) {
			glLoadIdentity();
			glOrtho(-11.0f*aspect, 11.0f*aspect, -11.0f, 11.0f, -11.0f, 11.0f);
		}else{
			glLoadIdentity();
			glOrtho(-11.0f, 11.0f, -11.0f/aspect, 11.0f/aspect, -11.0f, 11.0f);
		}
	}else{
		if(_camera == PERSPECTIVE_BEHIND){
			glLoadIdentity();
			gluPerspective(80.0, aspect, 1.0, 30.0);
		}else{
			glLoadIdentity();
			gluPerspective(80.0, aspect, 1.0, 30.0);
		}
	}
	
	

}
void Controller::keyboardFunc(unsigned char key, int x, int y){
	
	//later becomes: _keyStates[key]=true;
	
	//SPACE
	if(key == 32){
		_keyStates[32] = true;
	}
	
	
	//FIX - set camera must NOT call reshape function
	
	//1
	if(key == 49){
		
		setCamera(ORTHOGONAL_CAM);
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}
	//2
	if(key == 50){
		setCamera(PERSPECTIVE_BEHIND);
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}
	//3
	if(key == 51){
		setCamera(PERSPECTIVE_FIRST_PERSON);
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}
	
	if(key == 'q' || key == 'Q'){
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}
	if(key == 'w' || key == 'W'){
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
	}
	if(key == 'p' || key =='P'){
		_directionY+=0.1;
	}
	if(key == 'o' || key =='O'){
		_directionY-=0.1;
	}
	//CHEAT
	/*if(key == 75 || key == 107){
		_aliens1.erase(_aliens1.begin(),_aliens1.end());
		_aliens2.erase(_aliens2.begin(),_aliens2.end());
		_aliens3.erase(_aliens3.begin(),_aliens3.end());
		_aliens4.erase(_aliens4.begin(),_aliens4.end());
		_aliens5.erase(_aliens5.begin(),_aliens5.end());
	}*/
	
}

void Controller::keyboardUpFunc(unsigned char key, int x, int y){
	//later becomes: _keyStates[key]=false;
	
	
	//SPACE
	if(key == 32){
		_timesPressed++;
		_keyStates[32] = false;
	}

}

void Controller::specialKeyboardFunc(int key, int x, int y){
	if(key == GLUT_KEY_LEFT) {
		_keySpecialStates[0] = true;
	}
	if(key == GLUT_KEY_RIGHT){
		_keySpecialStates[1] = true;
		
	}
}

void Controller::specialKeyboardUpFunc(int key, int x, int y){

	if(key == GLUT_KEY_LEFT) {
		_keySpecialStates[0] = false;
	}
	if(key == GLUT_KEY_RIGHT){
		_keySpecialStates[1] = false;
	}


}

void Controller::idle(){
	int actual = glutGet(GLUT_ELAPSED_TIME);
	bool moved=false;
	setDeltaTime(actual);
	_lastTime = actual;
	
	//TODO
	/*
	if(_ship->getLives() == 0){
		_aliens1.erase(_aliens1.begin(),_aliens1.end());
		_aliens2.erase(_aliens2.begin(),_aliens2.end());
		_aliens3.erase(_aliens3.begin(),_aliens3.end());
		_aliens4.erase(_aliens4.begin(),_aliens4.end());
		_aliens5.erase(_aliens5.begin(),_aliens5.end());
		delete _ship;
		
	}*/
	
	shootMove();
	alienShootMove();
	collisionTesting();
#ifdef MOTION_SENSOR
	actualizeSpStatesSensor(&moved);
#endif
	

	//Left key pressed - moves spaceship left
	if(_keySpecialStates[0] == true){
		_ship->updatePosition(-(_shipMovingRatio*deltaTime()),0,0);
		if(moved)
			_keySpecialStates[0] = false;

	}
	//Right key pressed - moves spaceship right
	if(_keySpecialStates[1] == true){
		_ship->updatePosition((_shipMovingRatio*deltaTime()),0,0);
		if(moved)
			_keySpecialStates[1] = false;
	}
	//NORMAL KEYS
	
	//Space key pressed - shoot
	if(_keyStates[32] == true && _timesPressed > 0){
		shoot(_ship->posX(), _ship->posY()+0.2, _ship->posZ(), SHIP_SHOOT);	 
		_timesPressed--;
		shotsSounds.play();	
		//sf::sleep(sf::milliseconds(80));

	}
	
	if((((actual/1000) % 4) == 0) && _alienShoot){
		if(_alienShootCounter <= (rand()%2)){
			alienShoot();
			_alienShootCounter++;
		}
	}
	
	if((actual - _lastAlienFootMove) >= 1000){
		alienDance();
		alienMove();
		_alienShootCounter = 0;
	}
	if(_totalAliens == 0)
		_allDead = true;
	
	glutPostRedisplay();
}


int Controller::deltaTime(){
	return _deltaTime;
}

void Controller::setDeltaTime(float actual){
	_deltaTime = actual - _lastTime;
}

void Controller::setCamera(int mode){
	_camera = mode;
}

void Controller::drawText(const char *msg){
	/* raster pos sets the current raster position
	 * mapped via the modelview and projection matrices
	 */
	glColor3f(1.0, 0.0, 0.0);
	glScalef(5.0, 4.0, 4.0);
	glRasterPos3f((GLfloat)0.0, (GLfloat)0.0, (GLfloat) 0.0);
	
	/*
	 * write using bitmap and stroke chars
	 */
	while (*msg) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *msg);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*msg++);
		
	}
}

void Controller::setWidth(int width){}
void Controller::setHeight(int height){}
void Controller::framesInc(void){
	_frames++;
}
void Controller::drawPlane(int divs = 10, float ex=0.0, float ey=0.0, float ez=1.0){

	
	float x1, x2, y1, y2, s1, s2, t1, t2;
	x1 = y1 = -12.5;
	s1 = t1 = 0.0;
	for( int j=0; j<divs; j++)
	{	
		t2 = t1 + (1.0/divs);
		y2 = y1 + (25.0/divs);
		for( int i=0; i<divs; i++)
		{
			s2 = s1 + (1.0/divs);
			x2 = x1 + (25.0/divs);
			
			
			
			glBegin( GL_TRIANGLE_STRIP);
			glNormal3f(ex,ey,ez);
			
			glTexCoord2f( s1, t1);
			glVertex3f(   x1, y1, 0.);
			
			glTexCoord2f( s2, t1);
			glVertex3f(   x2, y1, 0.);
			
			glTexCoord2f( s1, t2);
			glVertex3f(   x1, y2, 0.);
			
			
			glTexCoord2f( s2, t2);
			glVertex3f(   x2, y2, 0.);
			glEnd();
			
			x1 = x2;
			s1 = s2;
		}
		y1 = y2;
		x1 = -12.5;
		t1 = t2;
		s1 = 0.0;
	}
	


}

void Controller::createTexture(){
	//TEXTURE
	//TODO - Loading the pic must save its data to reload opengl memory
	
	if(!_textured){
	_textures = new Texture();
	_bgTexture = _textures->loadBitmap("SI_Space.bmp");
	_textured = true;
	}
	
	float mcolor[] = {0.6f,0.6f,0.6f,1.0f};
	GLfloat mat_ambient[] = {1.0f,1.0f, 1.0f, 1.0f };
	GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat mat_diffuse[] = { 1.0f,1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shininess= 60;
	glMaterialfv (GL_FRONT, GL_AMBIENT, mcolor);
	glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glBindTexture(GL_TEXTURE_2D, _bgTexture);	
	

	if(_camera != ORTHOGONAL_CAM){
		//Fixed bottom
		glPushMatrix();
		drawPlane(10, 0.0, 0.0,-1.0);
		glPopMatrix();
		
		//Back
		glPushMatrix();
		glTranslatef(0.0, 12.5, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		drawPlane(10,0.0,-1.0,0.0);
		glPopMatrix();
		
		//Top
		glPushMatrix();
		glTranslatef(0.0, 0.0, 12.5);
		glRotatef(180.0, 1.0, 0.0, 0.0);
		drawPlane(10,0.0,0.0,-1.0);
		glPopMatrix();
		
		//Left
		glPushMatrix();
		glTranslatef(-12.5, 0.0, 0.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		drawPlane(10,1.0,0.0,0.0);
		glPopMatrix();
		
		//Left
		glPushMatrix();
		glTranslatef(12.5, 0.0, 0.0);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		drawPlane(10,-1.0,0.0,0.0);
		glPopMatrix();
	}else{
		//Fixed bottom
		glPushMatrix();
		drawPlane();
		glPopMatrix();
		
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	/*const GLuint *temp = &_bgTexture;
	glDeleteTextures(1, temp);
	delete _textures;*/
	

}

void Controller::actualizeSpStatesSensor(bool *moved){
	float actualX=0;
	int actualMotion;
	float interval = 0.02;
	updateXMotion();
	actualX = getXMotion();
	
	std::cout << actualX << std::endl;
	
	if(_motionBefore == MOTION_STOPPED){
		if(actualX < (_motionPosBefore-interval)){
			actualMotion = MOTION_RIGHT;
		}else
		if(actualX > (_motionPosBefore+interval)){
			actualMotion = MOTION_LEFT;
		}else{
			actualMotion = MOTION_STOPPED;	
		}

	}else
	if(_motionBefore == MOTION_LEFT){
		if(actualX > (_motionPosBefore+interval))
			actualMotion = MOTION_LEFT;
		else 
		if(actualX < (_motionPosBefore-interval))
			actualMotion = MOTION_RIGHT;
		else
			actualMotion = MOTION_STOPPED;
	}else
	if(_motionBefore == MOTION_RIGHT){
		if(actualX < (_motionPosBefore-interval))
			actualMotion = MOTION_RIGHT;
		else
		if(actualX > (_motionPosBefore+interval))
			actualMotion = MOTION_LEFT;
		else
			actualMotion = MOTION_STOPPED;
	}
	
	if(actualMotion == MOTION_STOPPED){
		*moved = false;
		std::cout << "MOTION STOPPED" <<std::endl;
		return;
	}
	
	if(actualMotion == MOTION_LEFT){
				std::cout << "MOTION LEFT" <<std::endl;
		*moved = true;
		_keySpecialStates[0] = true;
	}
	if(actualMotion == MOTION_RIGHT){
				std::cout << "MOTION RIGHT" <<std::endl;
		*moved = true;
		_keySpecialStates[1] = true;
	}
	
	
}

