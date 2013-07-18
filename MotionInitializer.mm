//
//  MotionInitializer.m
//

#import "MotionInitializer.h"
#import "smslib.h"

static float _xMotion, _yMotion, _zMotion;
static sms_acceleration _accel;
static vector3D _vector;

void initMotionSensor(){
	int result = smsStartup(nil, @selector(logMessage: ));
	int length,i;
	
	
	if(result != SMS_SUCCESS)
		NSLog(@"Couldn't load sensor");
	length = smsGetBufferLength();
	
	char *buffer = (char*)malloc(length);
	smsGetBufferData(buffer);
	
	for (i = 0; i < length; i++) {
		NSLog(@"%02.2hhx ", buffer[i]);
	}
	NSLog(@"\n");


}

vector3D* updateAndGet3Motion(){
	int result = smsGetData(&_accel);
	
	if (result != SMS_SUCCESS) {
		NSLog(@"ERROR FETCHING ACCEL");
	}	
	_vector._x = _accel.x;
	_vector._y = _accel.y;
	_vector._z = _accel.z;
	
	return (&_vector);
	
}

void update3Motion(){
	int result = smsGetData(&_accel);
	
	if (result != SMS_SUCCESS) {
		NSLog(@"ERROR FETCHING ACCEL");
	}	
	_xMotion = _accel.x;
	_yMotion = _accel.y;
	_zMotion = _accel.z;
	
}

void updateXMotion(){
	
	int result = smsGetData(&_accel);
	if (result != SMS_SUCCESS) {
			NSLog(@"ERROR FETCHING ACCEL");
	}
	_xMotion = _accel.x;
}

void updateYMotion(){
	
	int result = smsGetData(&_accel);
	if (result != SMS_SUCCESS) {
		NSLog(@"ERROR FETCHING ACCEL");
	}
	_yMotion = _accel.y;
}

void updateZMotion(){
	
	int result = smsGetData(&_accel);
	if (result != SMS_SUCCESS) {
		NSLog(@"ERROR FETCHING ACCEL");
	}
	_zMotion = _accel.z;
}



float getXMotion(){
	return _xMotion;
} 

float getYMotion(){
	return _yMotion;
}

float getZMotion(){
	return _zMotion;
}

void closeMotionSensor(){
	smsShutdown();
}
