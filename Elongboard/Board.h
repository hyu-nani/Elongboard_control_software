
/*
 * Board.h
 *
 * Created: 7/19/2020 9:10:07 PM
 *  Author: Bae hyeon han
 */ 

/* 
//////////////////////////////////////////////////////////////////////////////////////////////
                                  BOARD PINOUT for Atmel Studio
PC
0 ADC0/BAT-V
1 ADC1/DC-IN
2 ADC2/keypad1
3 ADC3/keypad2
4 ADC4/SDA
5 ADC5/SCL
A6  keypad3
A7  keypad4

PD
0 RXD
1 TXD
2 INT0/BT_RX
3 INT1/BT_TX
4 T0/keypad5
5 T1/keypad6
6 AIN0/keypad7
7 AIN1/keypad8

PB
0 ICP/NEO-pixel
1 OC1A/GY-INT
2 SS/OC1B/GY-DRDY
3 MOSI/OC2/OUT2(12v)
4 MISO/OUT1(12v)
5 SCK/G-Led
6 XTAL1
7 XTAL2

//////////////////////////////////////////////////////////////////////////////////////////////
                                     BOARD PINOUT for Arduino
 Digital Pin
 0	RXD
 1	TXD
 2	INT0/BT_RX
 3	INT1/BT_TX
 4	T0/keypad5
 5	T1/keypad6
 6	AIN0/keypad7
 7	AIN1/keypad8
 8	NeoPixel
 9	OC1A/GY-INT
 10	SS/OC1B/GY-DRDY
 11	MOSI/OC2/OUT2(12v)
 12	MISO/OUT1(12v)	
 13	SCK/G-Led
 
 Analog Pin
 A0	ADC0/BAT-V
 A1	ADC1/DC-IN
 A2	ADC2/keypad1
 A3	ADC3/keypad2
 A4	ADC4/SDA
 A5	ADC5/SCL
 A6	keypad3
 A7	keypad4
 
 //////////////////////////////////////////////////////////////////////////////////////////////
*/


#define Bat_Voltage A0
#define DC_IN		  A1
#define keypad1		A2
#define keypad2		A3
#define keypad3		A6
#define keypad4		A7
#define keypad5		4
#define keypad6		5
#define keypad7		6
#define keypad8		7
//#define NEO			8 //Neopixel setting
#define GY_INT		9
#define GY_DRDY		10
#define OUT12_2		11
#define OUT12_1		12
#define LED			13

void setting_pin()
{
	//pinMode(NEO,OUTPUT);
	pinMode(Bat_Voltage,INPUT);
	pinMode(DC_IN,INPUT);
	pinMode(keypad1,INPUT_PULLUP);
	pinMode(keypad2,INPUT_PULLUP);
	pinMode(keypad3,INPUT_PULLUP);
	pinMode(keypad4,INPUT_PULLUP);
	pinMode(keypad5,OUTPUT);
	pinMode(keypad6,OUTPUT);
	pinMode(keypad7,OUTPUT);
	pinMode(keypad8,OUTPUT);
	pinMode(GY_INT,INPUT);
	pinMode(GY_DRDY,INPUT);
	pinMode(OUT12_1,OUTPUT);
	pinMode(OUT12_2,OUTPUT);
	pinMode(LED,OUTPUT);
	
	digitalWrite(OUT12_2,LOW);
	digitalWrite(OUT12_1,LOW);
	delay(1);
	
}
/*

*/
