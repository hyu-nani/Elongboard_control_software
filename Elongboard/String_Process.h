
/*
 * String_Process.h
 *
 * Created: 7/20/2020 4:15:16 PM
 *  Author: cube_
 */ 
//===============================================================
//                      Serial Action
//===============================================================

void Serial_Action(char str[])
{
	int num=0,position=1;
	
	while(str[num] != '\0'){
		num++;
	}
	uint8_t length_string = num;
	num = 0;
	//T_ALL_Color(100,100,100,0);
	//delay(10);
	//T_ALL_Color(0,100,0,0);
	
	
	       
	//���ڿ� ó�� ������ ������	D[BN:x/TN:x/1O:x/2O:x]
	//          RGB				C[R:1xxx/G:1xxx/B:1xxx/W:1xxx] 
	//			������ Ȯ�ο�		Autodata
	//			RGB �� Ȯ�ο�	Basecolor
	//         ������ ������ [BN:x/TN:x/1O:x/2O:x/CH:x/ST:x]
	
	while(1){
		
		if(str[num] == 'D' ){	//D[BN:x/TN:x/1O:x/2O:x]24
			num = 0;
			position = 1;
			while(str[num] != '\0'){
				if((str[num] == ':')||(str[num] == ';')){
					switch(position){
						case 1:
							B_NEO_State = int(str[num+1] - 48);
							position++;
							break;
						case 2:
							T_NEO_State = int(str[num+1] - 48);
							position++;
							break;
						case 3:
							OUT1_Data = int(str[num+1] - 48);
							position++;
							break;
						case 4:
							OUT2_Data = int(str[num+1] - 48);
							position++;
							break;
					}
				}
				num++;
			}
			Send_Data();
			goto string_process_end;
			break;
		}
		
		else if(str[num]== 'C' ){	//C[R:1xxx/G:1xxx/B:1xxx/W:1xxx] 32
			num = 0;
			position = 1;
			
			while(str[num]!='\0'){
				if((str[num] == ':')||(str[num] == ';')){
					switch(position){
						case 1:
							change_r = int(100*(str[num+2]-48)+10*(str[num+3]-48)+(str[num+4]-48));
							position++;
							break;
						case 2:
							change_g = int(100*(str[num+2]-48)+10*(str[num+3]-48)+(str[num+4]-48));
							position++;
							break;
						case 3:
							change_b = int(100*(str[num+2]-48)+10*(str[num+3]-48)+(str[num+4]-48));
							position++;
							break;
						case 4:
							change_w = int(100*(str[num+2]-48)+10*(str[num+3]-48)+(str[num+4]-48));
							position++;
							break;
					}
				}
				num++;
			}
			
			Send_RGBW();
			initialize_neo = 0;
			goto string_process_end;
			break;
		}
		else if(str[0]== 'T' ){	//Autodata
			//TEST = true;
			goto string_process_end;
			break;
		}
		else if(str[0]== 'A' ){	//Autodata
			Send_Data();
			goto string_process_end;
			break;
		}
		
		else if(str[0]== 'B' ){ //Basecolor
			Send_RGBW();
			goto string_process_end;
			break;
		}
		
		else{
			//BT_Serial.println("N: Data Delete");
			goto string_process_end;
			break;
		}
		
		num++;
	}
	
	
	string_process_end:
	position = 1;
	num = 0;
	Save_Data();
}
