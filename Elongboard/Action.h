

void OUTPUT_12V(uint8_t A,uint8_t B);

//===============================================================
//                   NEO ACTION Integration
//===============================================================

void NEO_Action(uint8_t B_State,uint8_t T_State);


//===============================================================
//                        keypad Action
//===============================================================

char Read_Keypad();

char keypad_Action(char key);


//===============================================================
//                        Other Action
//===============================================================

void Save_Data();

void Get_Data();

//===========================================================================================================================//
void OUTPUT_12V(uint8_t A,uint8_t B)
{
	if(A == 1){digitalWrite(OUT12_1,HIGH);}
	else if(A == 0){digitalWrite(OUT12_1,LOW);}
	if(B == 1){digitalWrite(OUT12_2,HIGH);}
	else if(B == 0){digitalWrite(OUT12_2,LOW);}
}

//NEO ACTION MENU
void NEO_Action(uint8_t B_State,uint8_t T_State){//(B.state , T.state)
	if(B_State == 0){}
	else if(B_State == 1){B_ALL_TurnOff();}								
	else if(B_State == 2){B_Color(change_r,change_g,change_b,change_w);}		
	else if(B_State == 3){B_WHITE_Grade(240,1);}					
	else if(B_State == 4){B_filcker();}			
	else if(B_State == 5){B_Rainbow();}	
	else if(B_State == 6){B_Gradual_color(change_r,change_g,change_b,change_w);}	
	else if(B_State == 7){safety_lamp();}	

	if(T_State == 0){}		
	else if(T_State == 1){T_ALL_TurnOff();}									
	else if(T_State == 2){T_Color(change_r,change_g,change_b,change_w);}			
	else if(T_State == 3){T_WHITE_Grade(150,1);}						
	else if(T_State == 4){T_Rotate_3color(change_r,change_g,change_b,change_w,70);}	
	else if(T_State == 5){T_Rotate_1color(change_r,change_g,change_b,change_w,70);}
	else if(T_State == 6){T_filcker();}						
	else if(T_State == 7){Compass();}									
	else if(T_State == 8){Show_Battery_Amount(analogRead(Bat_Voltage));}
	else if(T_State == 9){T_Rainbow();}
	strip.show();
	if (initialize_neo == 0){initialize_neo = 1;}
	if(B_State == 4 || B_State == 7 || T_State == 6){
		mpu_status = true;
	}
	else{mpu_status = true;}
	if(T_State == 7){
		hmc_status = true;
	}
	else{hmc_status = false;}
		
	
}

void Default_Action()
{
	nowtime = millis();
	if(mpu_status==true){
		acc = get_acc_value();
	}
	//else if(nowtime > mpu_time+2000){
	//	acc = get_acc_value();
	//	mpu_time = nowtime;
	//}
	if(hmc_status==true){
		Head = get_compass_value();
	}
	//Temp = temperature_value();
	//Pressure = pressure_value();
	//if(TEST==true){
	//	BT_Serial.println(millis());
	//}
}


//keypad Read
char Read_Keypad()
{
	int Sensitivity = 22;	//0�� �������� �а�
	char key = 'n';
	digitalWrite(keypad5,LOW);
	digitalWrite(keypad6,HIGH);
	digitalWrite(keypad7,HIGH);
	digitalWrite(keypad8,HIGH);
	if(analogRead(keypad1) < Sensitivity ){key = 'C';}
	else if(analogRead(keypad2) < Sensitivity ){key = 'D';}
	else if(analogRead(keypad3) < Sensitivity ){key = 'E';}
	else if(analogRead(keypad4) < Sensitivity ){key = 'F';}
	digitalWrite(keypad5,HIGH);
	digitalWrite(keypad6,LOW);
	digitalWrite(keypad7,HIGH);
	digitalWrite(keypad8,HIGH);
	if(analogRead(keypad1) < Sensitivity ){key = '9';}
	else if(analogRead(keypad2) < Sensitivity ){key = '0';}
	else if(analogRead(keypad3) < Sensitivity ){key = 'A';}
	else if(analogRead(keypad4) < Sensitivity ){key = 'B';}
	digitalWrite(keypad5,HIGH);
	digitalWrite(keypad6,HIGH);
	digitalWrite(keypad7,LOW);
	digitalWrite(keypad8,HIGH);
	if(analogRead(keypad1) < Sensitivity ){key = '5';}
	else if(analogRead(keypad2) < Sensitivity ){key = '6';}
	else if(analogRead(keypad3) < Sensitivity ){key = '7';}
	else if(analogRead(keypad4) < Sensitivity ){key = '8';}
	digitalWrite(keypad5,HIGH);
	digitalWrite(keypad6,HIGH);
	digitalWrite(keypad7,HIGH);
	digitalWrite(keypad8,LOW);
	if(analogRead(keypad1) < Sensitivity ){key = '1';}
	else if(analogRead(keypad2) < Sensitivity ){key = '2';}
	else if(analogRead(keypad3) < Sensitivity ){key = '3';}
	else if(analogRead(keypad4) < Sensitivity ){key = '4';}
	digitalWrite(keypad5,HIGH);
	digitalWrite(keypad6,HIGH);
	digitalWrite(keypad7,HIGH);
	digitalWrite(keypad8,HIGH);
	return key;
}



//keypad action
char keypad_Action(char key)
{
	if(key == 'A'){
		while(key != 'n'){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,50,0);
			delay(200);
			key = Read_Keypad();
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(200);
		}
		key='n';
		while(1){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,50,0);
			delay(100);
			key = Read_Keypad();
			if(key == '1'){B_NEO_State = 1;break;}
			else if(key == '2'){B_NEO_State = 2;break;}
			else if(key == '3'){B_NEO_State = 3;break;}
			else if(key == '4'){B_NEO_State = 4;break;}
			else if(key == '5'){B_NEO_State = 5;break;}
			else if(key == '6'){B_NEO_State = 6;break;}
			else if(key == '7'){B_NEO_State = 7;break;}
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(100);
		}
	}
	else if(key == 'B'){
		while(key != 'n'){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,50,0);
			delay(200);
			key = Read_Keypad();
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(200);
		}
		key='n';
		while(1){
			digitalWrite(OUT12_1,HIGH);
			delay(100);
			key = Read_Keypad();
			if(key == '1'){T_NEO_State = 1;break;}
			else if(key == '2'){T_NEO_State = 2;break;}
			else if(key == '3'){T_NEO_State = 3;break;}
			else if(key == '4'){T_NEO_State = 4;break;}
			else if(key == '5'){T_NEO_State = 5;break;}
			else if(key == '6'){T_NEO_State = 6;break;}
			else if(key == '7'){T_NEO_State = 7;break;}
			else if(key == '8'){T_NEO_State = 8;break;}
			else if(key == '9'){T_NEO_State = 9;break;}
			digitalWrite(OUT12_1,LOW);
			delay(100);
		}
	}
	else if(key == 'C'){
		while(key != 'n'){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,50,0);
			delay(200);
			key = Read_Keypad();
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(200);
		}
		key='n';
		while(1){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,50,0);
			delay(100);
			key = Read_Keypad();
			if(key == '1'){OUT1_Data = 0;break;}
			else if(key == '2'){OUT1_Data = 1;break;}
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(100);
		}
	}
	else if(key == 'D'){
		while(key != 'n'){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,50,0);
			delay(200);
			key = Read_Keypad();
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(200);
		}
		key='n';
		while(1){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,0,0);
			delay(100);
			key = Read_Keypad();
			if(key == '1'){OUT2_Data = 0;break;}
			else if(key == '2'){OUT2_Data = 1;break;}
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(100);
		}
	}
	else if(key == 'F'){
		while(key != 'n'){
			digitalWrite(OUT12_1,HIGH);
			T_Color(50,50,50,0);
			delay(200);
			key = Read_Keypad();
			digitalWrite(OUT12_1,LOW);
			T_ALL_TurnOff();
			delay(200);
		}
		key='n';
		B_NEO_State =1;
		T_NEO_State =1;
		OUT1_Data =0;
		OUT2_Data =0;
	}
	else{key = 'n';}
	
	
	while(key != 'n'){
		digitalWrite(OUT12_1,HIGH);
		T_Color(50,50,50,0);
		delay(50);
		key = Read_Keypad();
		digitalWrite(OUT12_1,LOW);
		T_ALL_TurnOff();
		delay(50);
	}
	key='n';
	
	//T_ALL_TurnOff();
}



//Other Action
void Save_Data()
{
	Serial.println("N: Saving data ");
	EEPROM.write(4,change_r);
	EEPROM.write(5,change_g);
	EEPROM.write(6,change_b);
	EEPROM.write(7,change_w);
	EEPROM.write(2,OUT1_Data);
	EEPROM.write(3,OUT2_Data);
	EEPROM.write(1,T_NEO_State);
	EEPROM.write(0,B_NEO_State);
	/*
	address		name
	0			B_NEO_State
	1			T_NEO_State
	2			OUT1_Data
	3			OUT2_Data
	4			Red
	5			Green
	6			Blue
	7			White
	*/
}
void Get_Data()
{
	Serial.println("N: Get data ");
	change_r = EEPROM.read(4);
	change_g = EEPROM.read(5);
	change_b = EEPROM.read(6);
	change_w = EEPROM.read(7);
	OUT1_Data = EEPROM.read(2);
	OUT2_Data = EEPROM.read(3);
	T_NEO_State = EEPROM.read(1);
	B_NEO_State = EEPROM.read(0);
}

void Send_Data()
{	// Send string D[BN:x/TN:x/1O:x/2O:x/CH:x/ST:xx]
	// CH:charge on/off, ST: voltage step
	uint8_t STEP = map(analogRead(Bat_Voltage),bat_minlevel,bat_maxlevel,10,99);
	BT_Serial.print("D[BN:");
	BT_Serial.print(B_NEO_State);
	BT_Serial.print("/TN:");
	BT_Serial.print(T_NEO_State);
	BT_Serial.print("/1O:");
	BT_Serial.print(OUT1_Data);
	BT_Serial.print("/2O:");
	BT_Serial.print(OUT2_Data);
	BT_Serial.print("/CH:");
	BT_Serial.print(Charge_status);
	BT_Serial.print("/ST:");
	BT_Serial.print(STEP+200);
	BT_Serial.print("]\n");
}

void Send_RGBW(){
	// Send string C[R:1xxx/G:1xxx/B:1xxx/W:1xxx]
	BT_Serial.print("C[R:");
	BT_Serial.print(change_r+1000);
	BT_Serial.print("/G:");
	BT_Serial.print(change_g+1000);
	BT_Serial.print("/B:");
	BT_Serial.print(change_b+1000);
	BT_Serial.print("/W:");
	BT_Serial.print(change_w+1000);
	BT_Serial.print("]\n");
}
