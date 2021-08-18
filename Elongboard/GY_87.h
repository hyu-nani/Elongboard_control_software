
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#include "BMP180I2C.h"
#include "math.h"
//#include "motion_app.h"
#define BMP_ADDRESS 0x77

//0x1E : HMC5883L
//0x68 : MPU6050
//0X77 : BMP180

BMP180I2C bmp180(BMP_ADDRESS);

MPU6050 accelgyro;
HMC5883L mag;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;



void GY_begin() 
{
	Wire.begin();
	accelgyro.setI2CMasterModeEnabled(false);
	accelgyro.setI2CBypassEnabled(true) ;
	accelgyro.setSleepEnabled(false);
	if(TEST==true){Serial.println("N: Initializing I2C devices...");}
	accelgyro.initialize();
	mag.initialize();
	if(TEST==true){Serial.println(mag.testConnection() ? "N: HMC5883L connection successful" : "N: HMC5883L connection failed");}

	// verify connection
	if(TEST==true){Serial.println("N: Testing device connections...");}
	if(TEST==true){Serial.println(accelgyro.testConnection() ? "N: MPU6050 connection successful" : "N: MPU6050 connection failed");}
	//begin() initializes the interface, checks the sensor ID and reads the calibration parameters.
	if (!bmp180.begin())
	{
		if(TEST==true){Serial.println(accelgyro.testConnection() ? "N: begin() failed. check your BMP180 Interface and I2C Address." : " ");}
	}

	//reset sensor to default parameters.
	bmp180.resetToDefaults();

	//enable ultra high resolution mode for pressure measurements
	bmp180.setSamplingMode(BMP180MI::MODE_UHR);
}

int temperature_value()
{

	//wait for the measurement to finish. proceed as soon as hasValue() returned true.
	bmp180.hasValue();

	int value = bmp180.getTemperature(); 
	return value;
}

int pressure_value()
{
	
	//wait for the measurement to finish. proceed as soon as hasValue() returned true.
	bmp180.hasValue();
	
	int value = bmp180.getPressure();
	
	return value;
}

int get_compass_value()
{
	mag.getHeading(&mx, &my, &mz); //Mag
	
	// To calculate heading in degrees. 0 degree indicates North
	float heading = atan2(my,mx);
	float declinationAngle = -0.0457;
	heading += declinationAngle;
	// Correct for when signs are reversed.
	if(heading < 0)
	heading += 2*PI;
	
	// Check for wrap due to addition of declination.
	if(heading > 2*PI)
	heading -= 2*PI;

	return (heading * 180/M_PI);
}
int get_acc_value(){
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //Acc & Gyro
	
	int value = pow((pow(ax-old_ax,2)+pow(ay-old_ay,2)),0.5);
	old_ax = ax;
	old_ay = ay;
	return value;
}
/*
	//�� �޾Ƴ��� �Լ�
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	mag.getHeading(&mx, &my, &mz);

	// display tab-separated accel/gyro x/y/z values
	Serial.print("a/g:\t");
	Serial.print(ax); Serial.print("\t");
	Serial.print(ay); Serial.print("\t");
	Serial.print(az); Serial.print("\t");
	Serial.print(gx); Serial.print("\t");
	Serial.print(gy); Serial.print("\t");
	Serial.print(gz);Serial.print("\t");
	
	Serial.print("mag:\t");
	Serial.print(mx); Serial.print("\t");
	Serial.print(my); Serial.print("\t");
	Serial.print(mz); Serial.print("\t");
	
	// To calculate heading in degrees. 0 degree indicates North
	float heading = atan2(my, mx);
	if(heading < 0)
	heading += 2 * M_PI;
	Serial.print("heading:\t");
	Serial.println(heading * 180/M_PI);
}
*/
