//
//  MotionInitializer.h
//

typedef struct {
	float _x,_y,_z;
}vector3D;

void initMotionSensor();
vector3D *updateAndGet3Motion();
void update3Motion();
void updateXMotion();
void updateYMotion();
void updateZMotion();
float getXMotion();
float getYMotion();
float getZMotion();

void closeMotionSensor();