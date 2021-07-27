
/*
 * NEO.h
 *
 * Created: 7/19/2020 9:14:30 PM
 *  Author: cube_h2
 */ 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define LED_PIN     8

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  46 // button_string 22 + front_ring 24

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 200



// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

unsigned long pretime_B,pretime_T,pretime_A;
int		Aupdown,Tupdown,Bupdown;
int		Avalue	=	0;
int		Tvalue	=	0;
int		Bvalue	=	0;
int		count	=	0;
int rate_r,rate_g,rate_b,rate_w,current_r,current_g,current_b,current_w;
int old_r,old_g,old_b,old_w;
const int rate_value = 100;

void neo_setting()
{
	 // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
	 // Any other board, you can remove this part (but no harm leaving it):
	 #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
	 clock_prescale_set(clock_div_1);
	 #endif
	 // END of Trinket-specific code.

	 strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
	 strip.show();            // Turn OFF all pixels ASAP
	 strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
}
/*
 * pixels.clear(); // Set all pixel colors to 'off'
 * pixels.setPixelColor(i, pixels.Color(0, 150, 0));
 * pixels.show();   // Send the updated pixel colors to the hardware.
 * delay(DELAYVAL); // Pause before next pass through loop
 */



//===============================================================
//                      NEO ACTION LIST
//===============================================================

void ALL_TurnOff();//all off
void B_ALL_TurnOff();//bottom off
void T_ALL_TurnOff();//top off

void safety_lamp();

void ALL_WHITE_Grade(uint16_t wait);//bottom ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
void B_ALL_WHITE_Grade(uint16_t wait);//bottom ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
void T_ALL_WHITE_Grade(uint16_t wait);//top ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½

void ALL_Color(uint8_t red,uint8_t green,uint8_t blue);//all ï¿½ï¿½ï¿½ï¿½È¯
void B_ALL_Color(uint8_t red,uint8_t green,uint8_t blue);//bottom ï¿½ï¿½ï¿½ï¿½È¯
void T_ALL_Color(uint8_t red,uint8_t green,uint8_t blue);//top ï¿½ï¿½ï¿½ï¿½È¯

void ALL_PulseWhite(uint8_t wait);
void ALL_WhiteOverRainbow(int whiteSpeed, int whiteLength);
void ALL_RainbowFade2White(int wait, int rainbowLoops, int whiteLoops);

void Vehicle_filcker(uint8_t R,uint8_t G,uint8_t B);

void Show_Battery_Amount_charge(uint16_t Bat);
void Show_Battery_Amount(uint16_t Bat);
void Show_Battery_Simple(uint16_t Bat);

void T_Rotate_1color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white,uint16_t wait);
void T_Rotate_3color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white,uint16_t wait);
void B_Gradual_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white,uint16_t wait);

void Compass();



//------------------------------------------------------------------------------------------------------------

// NEO ACTION Element

//------------------------------------------------------------------------------------------------------------

void ALL_TurnOff()//all off
{	
	if(initialize_neo == 0){
		for(int j=0; j < 46 ; j++){
			strip.setPixelColor(j, strip.Color(0, 0, 0, 0));
		}
		//A
	}
}
void B_ALL_TurnOff()//bottom off
{
	if(initialize_neo == 0){
		for(int j=0; j < 22 ; j++){
			strip.setPixelColor(j, strip.Color(0, 0, 0, 0));
		}
		//A
	}
}
void T_ALL_TurnOff()//top off
{
	if(initialize_neo == 0){
		for(int j=22; j < 46 ; j++){
			strip.setPixelColor(j, strip.Color(0, 0, 0, 0));
		}
		//A
	}
}

void safety_lamp(){
	if(initialize_neo == 0){
		for(int j=0; j < 12 ; j++){
			strip.setPixelColor(j+5, strip.Color(200, 200, 200, 0));
		}
	}
	if(nowtime > pretime_B + 1800){
		pretime_B = nowtime;
		for(int j=0; j < 5 ; j++){
			strip.setPixelColor(j, strip.Color(0, 0, 0, 0));
			strip.setPixelColor(21-j, strip.Color(0, 0, 0, 0));
		}
	}
	if(nowtime >= pretime_B + 890&&nowtime <= pretime_B + 910){
		for(int j=0; j < 5 ; j++){
			strip.setPixelColor(j, strip.Color(255, 0, 0, 0));
			strip.setPixelColor(21-j, strip.Color(255, 0, 0, 0));
		}
		//A
	}
}

void ALL_WHITE_Grade(uint8_t maximum, uint16_t wait) //bottom ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
{	
	if(initialize_neo == 0){
	}
	if(nowtime > wait + pretime_A+(300-Avalue)/5){
		if(Aupdown == 1){
			Avalue+=3;
			if(Avalue >= maximum){
				Aupdown = 0;
			}
		}
		else if(Aupdown == 0){
			Avalue-=3;
			if (Avalue <= 1){
				Aupdown = 1;
			}
		}
		for(int j=0; j < 46 ; j++){
			strip.setPixelColor(j, strip.Color(0, 0, 0, Avalue));
		}
		//A
		pretime_A = nowtime;
	}
}

void B_WHITE_Grade(uint8_t maximum, uint16_t wait) //bottom ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
{
	if(initialize_neo == 0){
	}
	if(nowtime > wait + pretime_B){
		if(Bupdown == 1){
			Bvalue+=3;
			if(Bvalue >= maximum){
				Bupdown = 0;
			}
		}
		else if(Bupdown == 0){
			Bvalue-=3;
			if (Bvalue <= 1){
				Bupdown = 1;
			}
		}
		for(int j=0; j < 22 ; j++){
			strip.setPixelColor(j, strip.Color(0, 0, 0, Bvalue));
		}
		//A
		delay((300-Bvalue)/5);
		pretime_B = nowtime;
	}
}
void T_WHITE_Grade(uint8_t maximum, uint16_t wait) //top ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
{
	if(initialize_neo == 0){
	}
	if(nowtime > wait + pretime_T+(300-Tvalue)/5){
		if(Tupdown == 1){
			Tvalue+=5;
			delay((300-Tvalue)/5);
			if(Tvalue >= maximum){
				Tupdown = 0;
			}
		}
		else if(Tupdown == 0){
			Tvalue-=5;
			if (Tvalue <= 1){
				Tupdown = 1;
			}
		}
		for(int j=22; j < 46 ; j++){
			strip.setPixelColor(j, strip.Color(0, 0, 0, Tvalue));
		}
		//A
		pretime_T = nowtime;
	}
}

void ALL_Color(uint8_t red,uint8_t green,uint8_t blue,uint8_t white)  //all ï¿½ï¿½ï¿½ï¿½È¯
{
	if(initialize_neo == 0){
		for(int i=0; i < 46 ; i++){
			strip.setPixelColor(i, strip.Color(red, green, blue, white));
		}
		//A
	}
}
void B_Color(uint8_t red,uint8_t green,uint8_t blue,uint8_t white)  //bottom ï¿½ï¿½ï¿½ï¿½È¯
{
	if(initialize_neo == 0){
		for(int i=0; i < 22 ; i++){
			strip.setPixelColor(i, strip.Color(red, green, blue, white));
		}
		//A
	}
}
void T_Color(uint8_t red,uint8_t green,uint8_t blue,uint8_t white)  //top ï¿½ï¿½ï¿½ï¿½È¯
{
	if(initialize_neo == 0){
		for(int i=22; i < 46 ; i++){
			strip.setPixelColor(i, strip.Color(red, green, blue, white));
		}
		//A
	}
}



int      tail          = 0;
int      loops         = 3;
int      loopNum       = 0;
uint32_t lastTime      = millis();
uint32_t firstPixelHue = 0;
void B_Rainbow() {
	if(initialize_neo == 0){
	}

	
	for(int i=0; i<22; i++) {  // For each pixel in strip...
		int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
		strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
	}
	//A
    // Update strip with new contents
	// There's no delay here, it just runs full-tilt until the timer and
	// counter combination below runs out.

	firstPixelHue += 120; // Advance just a little along the color wheel
}

void T_Rainbow() {
	if(initialize_neo == 0){
	}

	
	for(int i=22; i<46; i++) {  // For each pixel in strip...
		int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
		strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
	}

	//A
	 // Update strip with new contents
	// There's no delay here, it just runs full-tilt until the timer and
	// counter combination below runs out.

	firstPixelHue += 120; // Advance just a little along the color wheel
}
int old_gz;

int sensivity_fliker =3000;
void B_filcker(){ //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	if(initialize_neo == 0){
	}
	if(gz<old_gz+100&&gz > old_gz-100){
		old_gz = (gx+(old_gz*99))/100;
	}
	if (gz < old_gz-sensivity_fliker)
	{
		for(int j=0; j < 11 ; j++){
			strip.setPixelColor(j, strip.Color(255, 255, 0, 0));
		}
	}
	else if(gz > old_gz+sensivity_fliker)
	{
		for(int j=11; j < 22 ; j++){
			strip.setPixelColor(j, strip.Color(255, 255, 0, 0));
		}
	}
	else{
		for(int j=0; j < 22 ; j++){
			strip.setPixelColor(j, strip.Color(0, 100, 0, 0));
		}
		old_gz = gz;
	}
	//A
}
void T_filcker(){ //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	if(initialize_neo == 0){
	}
	if(gz<old_gz+100&&gz > old_gz-100){
		old_gz = (gx+(old_gz*99))/100;
	}
	if (gz < old_gz-sensivity_fliker)
	{
		for(int j=25; j < 32 ; j++){
			strip.setPixelColor(j, strip.Color(100, 100, 0, 0));
		}
	}
	else if(gz > old_gz+sensivity_fliker)
	{
		for(int j=37; j < 44 ; j++){
			strip.setPixelColor(j, strip.Color(100, 100, 0, 0));
		}
	}
	else{
		for(int j=22; j < 46 ; j++){
			strip.setPixelColor(j, strip.Color(0, 0, 0, 0));
		}
		old_gz = gz;
	}
	//A
}

void Show_Battery_Amount_charge(uint16_t Bat)
{
	if(initialize_neo == 0){
	}
	if(nowtime > 800 + pretime_T){
		int step = map(Bat,bat_minlevel,bat_maxlevel,24,44);
		for(int i = 22;i<46;i++){
			strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
		}
		strip.setPixelColor(22, strip.Color(0, 0, 0, 0));
		strip.setPixelColor(23, strip.Color(20,0,0,0));
		strip.setPixelColor(45, strip.Color(0,0,50,0));
		for(int i = 24;i<45;i++){
			strip.setPixelColor(i, strip.Color(0, 0, 0, 3));
		}
		if(step>23&&step<45){
			strip.setPixelColor(step, strip.Color(10,10,10,0));
		}
		//A
		pretime_T = nowtime;
	}
}

void Show_Battery_Amount(uint16_t Bat)
{
	if(initialize_neo == 0){
	}
	if(nowtime > 800 + pretime_T){
		int step = map(Bat,bat_minlevel,bat_maxlevel,24,44);
		for(int i = 22;i<46;i++){
			strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
		}
		strip.setPixelColor(22, strip.Color(0, 0, 0, 0));
		strip.setPixelColor(23, strip.Color(60,0,0,0));
		strip.setPixelColor(45, strip.Color(0,0,100,0));
		for(int i = 24;i<45;i++){
			strip.setPixelColor(i, strip.Color(0, 0, 0, 3));
		}
		if(step>23&&step<45){
			strip.setPixelColor(step, strip.Color(40,40,40,0));	
		}
		//A
		pretime_T = nowtime;
	}
}

void Show_Battery_Simple(uint16_t Bat){
	if(initialize_neo == 0){
		for(int i = 0;i<22;i++){
			strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
		}
	}
	int step = map(Bat,bat_minlevel,bat_maxlevel,1,9);
	for(int i = 0;i<21;i++){
	strip.setPixelColor(i, strip.Color(0, 0, 0, 3));
	}
	strip.setPixelColor(0, strip.Color(60,0,0,0));
	strip.setPixelColor(21, strip.Color(60,0,0,0));
	strip.setPixelColor(10, strip.Color(0,0,100,0));
	strip.setPixelColor(11, strip.Color(0,0,100,0));
	if(step>0&&step<10){
		strip.setPixelColor(step, strip.Color(40,40,40,0));
		strip.setPixelColor(21-step, strip.Color(40,40,40,0));
	}
	strip.show();
}

void T_Rotate_1color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white, uint16_t wait){
	if(initialize_neo == 0){
	}
	if(nowtime > wait + pretime_T){
		if(count == 22 ){	
			for(int i = 22;i<46;i++){
				strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
			}
			strip.setPixelColor(count+21, strip.Color(red/40, green/40, blue/40, white/40));
			strip.setPixelColor(count+22, strip.Color(red/20, green/20, blue/20, white/20));
			strip.setPixelColor(count+23, strip.Color(red/6, green/6, blue/6, white/6));
			strip.setPixelColor(count, strip.Color(red, green, blue, white));
		}
		else if(count == 23){
			for(int i = 22;i<46;i++){
				strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
			}
			strip.setPixelColor(count+21, strip.Color(red/40, green/40, blue/40, white/40));
			strip.setPixelColor(count+22, strip.Color(red/20, green/20, blue/20, white/20));
			strip.setPixelColor(count-1, strip.Color(red/6, green/6, blue/6, white/6));
			strip.setPixelColor(count, strip.Color(red, green, blue, white));
		}
		else if(count == 24){
			for(int i = 22;i<46;i++){
				strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
			}
			strip.setPixelColor(count+22, strip.Color(red/40, green/40, blue/40, white/40));
			strip.setPixelColor(count-2, strip.Color(red/20, green/20, blue/20, white/20));
			strip.setPixelColor(count-1, strip.Color(red/6, green/6, blue/6, white/6));
			strip.setPixelColor(count, strip.Color(red, green, blue, white));
		}
		else if(count > 24 && count < 46){
			for(int i = 22;i<46;i++){
				strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
			}
			strip.setPixelColor(count-3, strip.Color(red/40, green/40, blue/40, white/40));
			strip.setPixelColor(count-2, strip.Color(red/20, green/20, blue/20, white/20));
			strip.setPixelColor(count-1, strip.Color(red/6, green/6, blue/6, white/6));
			strip.setPixelColor(count, strip.Color(red, green, blue, white));
		}
		
		count++;
		if(count > 45){count = 22;}
		//A
		pretime_T = nowtime;
	}
}

void T_Rotate_3color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white, uint16_t wait){
	if(initialize_neo == 0){
	}
	if(nowtime > wait + pretime_T){
		for(int i = 22;i<46;i++){
			strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
		}
		if(count>=23 && count<=29)
		{
			strip.setPixelColor(count-1, strip.Color(red/10, green/10, blue/10, white/10));
			strip.setPixelColor(count+7, strip.Color(red/10, green/10, blue/10, white/10));
			strip.setPixelColor(count+15, strip.Color(red/10, green/10, blue/10, white/10));
			strip.setPixelColor(count, strip.Color(red, green, blue, white));
			strip.setPixelColor(count+8, strip.Color(red, green, blue, white));
			strip.setPixelColor(count+16, strip.Color(red, green, blue, white));
		}
		else if(count == 30){
			strip.setPixelColor(45, strip.Color(red/10, green/10, blue/10, white/10));
			strip.setPixelColor(29, strip.Color(red/10, green/10, blue/10, white/10));
			strip.setPixelColor(37, strip.Color(red/10, green/10, blue/10, white/10));
			strip.setPixelColor(22, strip.Color(red, green, blue, white));
			strip.setPixelColor(30, strip.Color(red, green, blue, white));
			strip.setPixelColor(38, strip.Color(red, green, blue, white));
		}
		if(count >= 30 || count < 23){
			count = 23;
		}
		else{
			count++;
		}
		//A
		pretime_T = nowtime;
	}	
}
int sum=0;
int grad_count=0;
void B_Gradual_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
	if(initialize_neo == 0){
	}
	if ((nowtime - pretime_B) >= 30)//(1000-map(acc,0,5000,0,500))
	{	
		if(grad_count > 0 && grad_count <=10){
			strip.setPixelColor(grad_count, strip.Color(red, green, blue, white));
			strip.setPixelColor(21-grad_count, strip.Color(red, green, blue, white));
		}
		else if(grad_count == 11){
			strip.setPixelColor(11, strip.Color(red, green, blue, white));
			strip.setPixelColor(10, strip.Color(red, green, blue, white));
			strip.setPixelColor(0, strip.Color(red, green, blue, white));
			strip.setPixelColor(21, strip.Color(red, green, blue, white));
		}
		if(grad_count > 0){
			strip.setPixelColor(grad_count-1, strip.Color(0, 0, 0, 0));
			strip.setPixelColor(22-grad_count, strip.Color(0, 0, 0, 0));
		}
		if(grad_count >= 11){
			grad_count = 0;
		}
		else{
			grad_count++;
		}
		//A
		pretime_B = nowtime;
	}
}
void Compass()
{
	if(initialize_neo == 0){
		
	}
	if (Head < min_head){
		min_head = Head;
	}
	else if (Head > max_head){
		max_head = Head;
	}
	if (min_head == 0){min_head = Head;}
	else if(max_head == 0){max_head = Head;}
	int head = map(Head,min_head,max_head,22,45);
	for(int i = 22;i<46;i++){
		strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
	}
	if(max_head - min_head > 30){
		if(head <= 42){
			strip.setPixelColor((head/2)+12, strip.Color(0, 0, 20, 0));
			strip.setPixelColor(67-((head/2)+11), strip.Color(0, 0, 20, 0));
		}
		else if(head > 42){
			strip.setPixelColor(22, strip.Color(0, 100, 0, 0)); 
			strip.setPixelColor(28, strip.Color(0, 0, 100, 0));
			strip.setPixelColor(34, strip.Color(0, 100, 0, 0));
			strip.setPixelColor(40, strip.Color(100, 0, 0, 0));  
		}
		//A
	}
	else if(nowtime> pretime_T+1000){
		for(int i = 22;i<46;i++){
			strip.setPixelColor(i, strip.Color(100, 0, 100, 0));
		}
		//A
		delay(500);
		pretime_T = nowtime;
	}
}
