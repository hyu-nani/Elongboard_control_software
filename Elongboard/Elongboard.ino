
#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial BT_Serial(3, 2); 

/*
 * ElongBoard_software.ino
 *
 * Created: 7/19/2020 8:39:16 PM
 * Author: Bae Hyeon Han
 * Change: 7/25/2020
 */ 

#define string_buffer_size		80
#define charge_sensivity		810

int bat_maxlevel = 850;
int bat_minlevel = 720;

const bool BT_SET	=	false;
const bool TEST		=	true;
bool mpu_status	=	false;
bool hmc_status	=	false;

int initialize_neo = 0;
int Temp,Pressure,Heading,acc;

unsigned long maintime ;
unsigned long nowtime = millis();


int	i = 0;

#include "Board.h"
#include "GY_87.h"
#include "NeoPixel.h"
#include "Action.h"
#include "String_Process.h"

char String_data[string_buffer_size]; //buffer size
char keypad_data = 'n';
//N: 
void setup() {
	Serial.begin(115200);
	/* //bluetooth AT command setting motion */
	if(BT_SET == true)	BT_Serial.begin(9600);
	else				BT_Serial.begin(38400);
	while (BT_SET == true){
		if(BT_Serial.available()){
			delay(5);
			while(BT_Serial.available())Serial.write(BT_Serial.read());
		}
		if(Serial.available()){
			delay(5);
			while(Serial.available())BT_Serial.write(Serial.read());
		}
		//digitalWrite(LED,HIGH);
		//delay(2000);
		//BT_Serial.write("AT\r\n");
		//BT_Serial.write("AT+NAMEELONGBOARD1\r\n");
		//BT_Serial.write("AT+PIN0000\r\n");
		//BT_Serial.write("AT+BAUD6\r\n");
		//BPS
		//1=1200/2=2400/3=4800/4=9600/5=19200/6=38400
		//7=57600/8=115200/A=460800/B=921600/C=1382400	
		//BT_Serial.println("done!");
		//digitalWrite(LED,LOW);
		//delay(2000);
	}
	if(TEST==true){Serial.println("N: -----Ready----- ");}
	setting_pin();
	if(TEST==true){Serial.println("N: PinMode setting ");}
	neo_setting();
	if(TEST==true){Serial.println("N: Neo setting ");}
	delay(100);
	if(TEST==true){Serial.println("N: NEO pixel begin ");}
	Get_Data();
	if(TEST==true){Serial.println("N: get data from EEPROM ");}
	GY_begin();
	if(TEST==true){Serial.println("N: GY_87 begin ");}
		//if(TEST==true){Serial.println("N: ");}
	
	
	
	if(TEST==true){Serial.println("N: BT AT set");}
		
	for(int j=0;j<string_buffer_size;j++ ){// useless buffer delete
		String_data[j] = '\0';
	} 
	
	if(B_NEO_State>10){B_NEO_State=1;EEPROM.write(0,B_NEO_State);}
	if(T_NEO_State>10){T_NEO_State=1;EEPROM.write(1,T_NEO_State);}
	if(OUT1_Data>1){OUT1_Data=0;EEPROM.write(2,OUT1_Data);}
	if(OUT2_Data>1){OUT2_Data=0;EEPROM.write(3,OUT2_Data);}
	if(TEST==true){Serial.println("N: error data adjust");}
	ALL_TurnOff();
	if(TEST==true){Serial.println("N: -----Start----- ");}
	initialize_neo =0;
	Default_Action();
	Compass();
	max_head = Head;
	min_head = Head;
	maintime = nowtime;
}

void loop() {
	
    // if(analogRead(DC_IN)>charge_sensivity){
	//	Charge_status = 1;
	///	goto Charging_mode;
	//}
	
	//============================run mode==============================
	basic_cycle:
	while(1){
		digitalWrite(LED,LOW);
		nowtime = millis();
		if(BT_Serial.available() > 0){
			delay(10);
			i = 0;
			while(BT_Serial.available() > 0){ //buffer receive
				String_data[i] = BT_Serial.read();
				i++;
				if(i%25 == 0){
					T_Rotate_1color(10,110,200,0,1);
				}
				if(TEST==true){BT_Serial.println(String_data[i]);}
				if(i>string_buffer_size){
					break;
				}
			}
			goto Serial_data_receive;
			break;
		}
		else if (nowtime > maintime+790 && nowtime <maintime +800){
			T_ALL_TurnOff();	
		}
		while(nowtime >= maintime + 1500){// main action loop
			//interrupt
			keypad_data = Read_Keypad();
			if(keypad_data != 'n'){
				if(TEST==true){					//testing
					BT_Serial.print("N: key = ");
					BT_Serial.println(keypad_data);
				}
				if (keypad_data =='E'){
					ALL_TurnOff();
					goto Keypad_setting_mode;
				}
				else if(keypad_data == 'F'){
					initialize_neo = 0;
					Show_Battery_Simple(analogRead(Bat_Voltage));
					delay(1000);
					keypad_data == 'n';
				}
			}
			else if(analogRead(DC_IN)>charge_sensivity){
				Charge_status = 1;
				goto Charging_mode;
				break;
			}
			if(BT_Serial.available() > 0){
				i = 0;
				while(BT_Serial.available() > 0){ //buffer receive
					String_data[i] = BT_Serial.read();
					if(i%25 == 0){//led output
				   		T_Rotate_1color(10,110,200,0,1);
					}
					if(TEST==true){BT_Serial.println(String_data[i]);} //testing
					i++;
					if(i>string_buffer_size){
						break;
					}
				}
				goto Serial_data_receive;
				break;
			}
			 
			NEO_Action(B_NEO_State,T_NEO_State);
			OUTPUT_12V(OUT1_Data,OUT2_Data);
			
			Default_Action();
			 
			while(Temp >= 50&&Temp<=150){
				ALL_Color(255,0,0,0);
				delay(200);
				ALL_TurnOff();
				delay(1000);	
				BT_Serial.print("Too high temp : ");
				BT_Serial.println(Temp);
			}
		}
	}
  
  
	//========================= keypad setting mode ===========================
	Keypad_setting_mode:
	while(1){
		digitalWrite(LED,HIGH);
		while(keypad_data != 'n'){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,0,0);
			delay(200);
			keypad_data = Read_Keypad();
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(200);
		}
		keypad_data='n';
		while(keypad_data == 'n'){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,0,0);
			delay(200);
			keypad_data = Read_Keypad();
			digitalWrite(OUT12_1,LOW);
			delay(200);
		}
		keypad_Action(keypad_data);
		keypad_data ='n';
		Send_Data();
		Save_Data();
		digitalWrite(LED,LOW);
		initialize_neo = 0;
		maintime = nowtime;
		goto basic_cycle;
		break;
	}
  
  
	//========================= Serial data receive ============================
	Serial_data_receive:
	while(1){
		if(TEST == true){
			BT_Serial.print("N: Number of strings: ");
			BT_Serial.println(BT_Serial.available());
		}
		i = 0;
		if(TEST == true){
			BT_Serial.print("N: Receive Data: ");
			while(String_data[i]!='\0'){
				BT_Serial.print(String_data[i]);
				i++;
			}
			BT_Serial.println(" ");
		}
		Serial_Action(String_data); //ï¿½ï¿½ï¿½Ú¿ï¿½ ï¿½ï¿½ï¿?
		i = 0;
		while(String_data[i]!='\0'){  //delete
			String_data[i] = '\0';
			i++;
		}
		Get_Data();
		//BT_Serial.println("N: Done ");
		if(B_NEO_State>10){B_NEO_State=1;EEPROM.write(0,B_NEO_State);}
		if(T_NEO_State>10){T_NEO_State=1;EEPROM.write(1,T_NEO_State);}
		if(OUT1_Data>1){OUT1_Data=0;EEPROM.write(2,OUT1_Data);}
		if(OUT2_Data>1){OUT2_Data=0;EEPROM.write(3,OUT2_Data);}
		if(change_r<0||change_r>255){change_r = 0;}
		if(change_g<0||change_g>255){change_g = 0;}
		if(change_b<0||change_b>255){change_b = 0;}
		if(change_w<0||change_w>255){change_w = 0;}
		if(BT_Serial.available()==0){
			initialize_neo = 0;
		}
		maintime = nowtime;
		goto basic_cycle;
		break;
	}
  
  
  //============================ charging mode ==============================
	
	Charging_mode:
	int bat_count=0;
	int bat_value;
	Save_Data();
	initialize_neo = 0;
	ALL_Color(0,100,20,0);
	digitalWrite(LED,HIGH);
	Send_Data();
	digitalWrite(LED,LOW);
	ALL_TurnOff();
	OUTPUT_12V(0,0);
	while(1){ //charging mode
		B_ALL_TurnOff();//?˜ë‹¨ë¶€ OFF, ?ë‹¨ë¶€ë°°í„°ë¦??œì‹œ
		Show_Battery_Amount_charge(analogRead(Bat_Voltage));
		nowtime = millis();
		strip.show();
		if(bat_count >= 20000){						
			digitalWrite(LED,HIGH);
			Send_Data();
			digitalWrite(LED,LOW);
			bat_count = 0;
		}
		else if(BT_Serial.available() > 0){
			int i = 0;
			while(BT_Serial.available() > 0){ //buffer ï¿½Ô·ï¿½
				String_data[i] = BT_Serial.read();
				i++;
				if(i>string_buffer_size){
					break;
				}
			}	
			i = 0;
			while(1){
				if(String_data[i] == 'A'){
					digitalWrite(LED,HIGH);
					Send_Data();
					bat_count = 0;
					i=0;
					while(String_data[i]!='\0'){  //delete
						String_data[i] = '\0';
						i++;
					}
					digitalWrite(LED,LOW);
					break;
				}
				i++;
			}
		}
		else if( analogRead(DC_IN) < charge_sensivity ){
			initialize_neo = 0;
			Charge_status = 0;
			T_Color(100,0,0,0);
			delay(100);
			T_ALL_TurnOff();
			Get_Data();
			maintime = nowtime;
			goto basic_cycle;
			break;
		}
		else{bat_count++;}
	}

}