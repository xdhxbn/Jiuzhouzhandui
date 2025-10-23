#ifndef PS2_h
#define PS2_h
/*PA 4,5,6,7*/
typedef struct {
	  uint8_t ID;/*41,73*/
    uint8_t data1;  /*51 means OK*/     
    uint8_t data2;  /*left down right up start R3 L3 Select*/ 
    uint8_t data3;  /*A S D W R1 L1 R2 L2*/     
    uint8_t data4;  /*joystick Rx,10000000 mean mid ,left smaller,right diger*/
    uint8_t data5;  /*joystick Ry,01111111 mean mid ,up smaller,down diger*/
    uint8_t data6;  /*joystick Lx,10000000 mean mid ,left smaller,right diger*/
		uint8_t data7;  /*joystick Ly,01111111 mean mid ,up smaller,down diger*/
} PS2data_struct;

typedef struct {
    uint8_t SELECT;       
    uint8_t START;
	
    uint8_t L1;       
    uint8_t R1;
    uint8_t L2;       
    uint8_t R2;	
	  uint8_t L3;       
    uint8_t R3; 
	
    uint8_t UP;
		uint8_t RIGHT;
		uint8_t DOWN;
		uint8_t LEFT;
	  uint8_t W;
	  uint8_t D;
	  uint8_t S;
	  uint8_t A;
} PS2KEY_struct;

typedef struct { 
    uint8_t L_x;//0:left,1:right
	  uint8_t L_y;//0:up,1:down
    uint8_t L_x_speed;//LEFT<=0X80,RIGHT<=0X7F
		uint8_t L_y_speed;
	
	  uint8_t R_x;//0:left,1:right
	  uint8_t R_y;//0:up,1:down
    uint8_t R_x_speed;//LEFT<=0X80,RIGHT<=0X7F
		uint8_t R_y_speed;
} PS2Joystick_struct;

typedef struct {      
	PS2Joystick_struct PS2Joystick;
	PS2KEY_struct PS2KEY;
	PS2data_struct PS2data;
	uint8_t ID;
} PS2_struct;
void PS2_init(void);
void PS2_GET_data(PS2data_struct* PS2data);
void get_PS2_key(PS2KEY_struct* PS2KEY,PS2data_struct* PS2data,PS2_struct* PS2);
void get_PS2_joystick(PS2Joystick_struct* PS2joystick,PS2data_struct* PS2data);
	
#endif
