/************************************************************************/
/*                             Elongboard                               */
/************************************************************************/
#define			string_buffer_size		80
#define			charge_sensivity		810

int				bat_maxlevel		=	850;
int				bat_minlevel		=	720;

const bool		BT_SET				=	false;
const bool		TEST				=	false;
bool			mpu_status			=	false;
bool			hmc_status			=	false;

int				initialize_neo		=	0;
int				Temp,Pressure,Heading,acc;

unsigned long	maintime;	
unsigned long	nowtime				=	millis();

char			String_data[string_buffer_size]; //buffer size
char			keypad_data			=	'n';
int				i					=	0;


/************************************************************************/
/*                               GY-87                                  */
/************************************************************************/
int				Head;
int				min_head,max_head;
int				old_ax,old_ay;


/************************************************************************/
/*                            neo-pixel                                 */
/************************************************************************/
unsigned long	pretime_B,pretime_T,pretime_A;
int				Aupdown,Tupdown,Bupdown;
int				Avalue				=	0;
int				Tvalue				=	0;
int				Bvalue				=	0;
int				count				=	0;
int				rate_r,rate_g,rate_b,rate_w,current_r,current_g,current_b,current_w;
int				old_r,old_g,old_b,old_w;
const int		rate_value			=	100;

int				sum					=	0;
int				grad_count			=	0;

int				old_gz;
int				sensivity_fliker	=	3000;

int				tail				=	0;
int				loops				=	3;
int				loopNum				=	0;
uint32_t		lastTime			=	millis();
uint32_t		firstPixelHue		=	0;


/************************************************************************/
/*                             Action                                   */
/************************************************************************/
uint8_t			B_NEO_State,T_NEO_State;			//NEO action
uint16_t		change_r=0,change_g=0,change_b=0,change_w=0;		//COLOR
uint8_t			OUT1_Data, OUT2_Data,Charge_status;	//othe
int				mpu_time			=	1000;