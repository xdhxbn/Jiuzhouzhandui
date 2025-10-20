#ifndef MOVE_h
#define MOVE_h

typedef struct { 
	  uint8_t direction;//1:��ת��0����ת
	  uint8_t GPIO1;
	  uint8_t Pin1;//����ʱΪ1
	  uint8_t GPIO2;
	  uint8_t Pin2;//����ʱΪ0
} wheel_struct;
typedef struct { 
    wheel_struct A_L;//up right    A  B
	  wheel_struct B_L;//up left     B  A
    wheel_struct A_R;
		wheel_struct B_R;
	
	  uint8_t direction;//1:up,2:down,3:left,4:right 0:stop
	  uint8_t round;//1:follow time,0:against time,2:none
    uint16_t speed;
} CAR_struct;

uint16_t PS2_TO_Speed(uint8_t speed_data);

/*�ӿں���*/
void MOVE_CAR_init(CAR_struct* car_now,CAR_struct* car_last);
void MOVE_GET_PS2( uint8_t L_x,uint8_t L_y,uint8_t L_x_speed,uint8_t L_y_speed,uint8_t R_x,uint8_t R_x_speed,CAR_struct* car_now,CAR_struct* car_last);
void MOVE_SET_MODE(CAR_struct* car_now,CAR_struct* car_last);
void MOVE_PWM_init(void);
/*����Ϊ�Գ��ӵĲ���*/
void MOVE_Set_direction(CAR_struct* car_now);
void MOVE_Set_around(CAR_struct* car_now);
void MOVE_set_Speed(uint16_t ccr);


/*����Ϊ�����ӵĲ���*/

void Wheel_set_mode(uint8_t mode,uint8_t GPIO1,uint8_t Pin1,uint8_t GPIO2,uint8_t Pin2);
	
#endif