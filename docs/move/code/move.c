#include "stm32f10x.h"                  // Device header
#include "gpio.h"
#include "move.h"

void Wheel_set_mode(uint8_t mode,uint8_t GPIO1,uint8_t Pin1,uint8_t GPIO2,uint8_t Pin2)
{
	if(mode==0)
	{
		mygpioout(GPIO1,Pin1,1);
		mygpioout(GPIO2,Pin2,1);
	}
	else if(mode==1)
	{
		mygpioout(GPIO1,Pin1,1);
		mygpioout(GPIO2,Pin2,0);
	}
	else if(mode==2)
	{
		mygpioout(GPIO1,Pin1,0);
		mygpioout(GPIO2,Pin2,1);
	}
}


void MOVE_PWM_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=25600-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=640;
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	
	mygpiosetinit(0,6,7);
	mygpiosetinit(0,7,5);
	mygpiosetinit(1,0,5);
	
	mygpiosetinit(0,4,5);
	mygpiosetinit(0,5,5);
	
	mygpiosetinit(1,1,5);
	mygpiosetinit(1,10,5);
	
	mygpiosetinit(0,14,5);
	mygpiosetinit(0,13,5);
	
	TIM_Cmd(TIM3,ENABLE);
}
void MOVE_struct_copy(CAR_struct* car_now,CAR_struct* car_last)
{
	car_last->direction=car_now->direction;
	car_last->round=car_now->round;
	car_last->speed=car_now->speed;
	
	car_last->A_L.direction=car_now->A_L.direction;
	car_last->A_L.GPIO1=car_now->A_L.GPIO1;
	car_last->A_L.GPIO2=car_now->A_L.GPIO2;
	car_last->A_L.Pin1=car_now->A_L.Pin1;
	car_last->A_L.Pin2=car_now->A_L.Pin2;
	
	car_last->A_R.direction=car_now->A_R.direction;
	car_last->A_R.GPIO1=car_now->A_R.GPIO1;
	car_last->A_R.GPIO2=car_now->A_R.GPIO2;
	car_last->A_R.Pin1=car_now->A_R.Pin1;
	car_last->A_R.Pin2=car_now->A_R.Pin2;
	
	car_now->B_L.direction=car_now->B_L.direction;
	car_now->B_L.GPIO1=car_now->B_L.GPIO1;
	car_now->B_L.GPIO2=car_now->B_L.GPIO2;
	car_now->B_L.Pin1=car_now->B_L.Pin1;
	car_now->B_L.Pin2=car_now->B_L.Pin2;
	
	car_last->B_R.direction=car_now->B_R.direction;
	car_last->B_R.GPIO1=car_now->B_R.GPIO1;
	car_last->B_R.GPIO2=car_now->B_R.GPIO2;
	car_last->B_R.Pin1=car_now->B_R.Pin1;
	car_last->B_R.Pin2=car_now->B_R.Pin2;
}
void MOVE_CAR_init(CAR_struct* car_now,CAR_struct* car_last)
{
	car_now->direction=1;
	car_now->round=2;
	car_now->speed=0;
	
	car_now->A_L.direction=1;
	car_now->A_L.GPIO1=1;
	car_now->A_L.GPIO2=1;
	car_now->A_L.Pin1=1;
	car_now->A_L.Pin2=10;
	
	car_now->A_R.direction=1;
	car_now->A_R.GPIO1=0;
	car_now->A_R.GPIO2=0;
	car_now->A_R.Pin1=13;
	car_now->A_R.Pin2=14;
	
	car_now->B_L.direction=1;
	car_now->B_L.GPIO1=0;
	car_now->B_L.GPIO2=1;
	car_now->B_L.Pin1=7;
	car_now->B_L.Pin2=0;
	
	car_now->B_R.direction=1;
	car_now->B_R.GPIO1=0;
	car_now->B_R.GPIO2=0;
	car_now->B_R.Pin1=4;
	car_now->B_R.Pin2=5;
	
	MOVE_struct_copy(car_now,car_last);
	
}

uint16_t PS2_TO_Speed(uint8_t speed_data)
{
	uint16_t speed;
	if(speed_data==128)
	{
		speed_data=127;
	}
	speed=speed_data*200;
	return(speed);
}

void MOVE_GET_PS2(uint8_t L_x,uint8_t L_y,uint8_t L_x_speed,uint8_t L_y_speed,uint8_t R_x,uint8_t R_x_speed,CAR_struct* car_now,CAR_struct* car_last)
{
	if(L_x_speed<L_y_speed)
	{
		if(L_y==0)
		{
			car_now->direction=1;
		}
		else
		{
			car_now->direction=2;
		}
		car_now->speed=PS2_TO_Speed(L_y_speed);
	}
	else if(L_x_speed>L_y_speed)
	{
		if(L_x==0)
		{
			car_now->direction=3;
		}
		else
		{
			car_now->direction=4;
		}
		car_now->speed=PS2_TO_Speed(L_x_speed);
	}
	else if(L_x_speed==0&&L_y_speed==0)
	{
		car_now->direction=0;
		car_now->speed=0;
	}
	else
	{
		car_now->direction=car_last->direction;
		car_now->speed=car_last->speed;
	}
	if(R_x_speed>0)
	{
		car_now->round=R_x;
	}
	else
	{
		car_now->round=2;
	}
}

void MOVE_set_Speed(uint16_t ccr)
{
	TIM_SetCompare1(TIM3,ccr);
}

/*1~4:front behind,left,right,5:stop*/
void MOVE_Set_direction(CAR_struct* car_now)
{
	switch(car_now->direction)
	{
		case 0:
			Wheel_set_mode(0,car_now->A_L.GPIO1,car_now->A_L.Pin1,car_now->A_L.GPIO2,car_now->A_L.Pin2);
			Wheel_set_mode(0,car_now->A_R.GPIO1,car_now->A_R.Pin1,car_now->A_R.GPIO2,car_now->A_R.Pin2);
			Wheel_set_mode(0,car_now->B_L.GPIO1,car_now->B_L.Pin1,car_now->B_L.GPIO2,car_now->B_L.Pin2);
			Wheel_set_mode(0,car_now->B_R.GPIO1,car_now->B_R.Pin1,car_now->B_R.GPIO2,car_now->B_R.Pin2);
			break;
		case 1:
			Wheel_set_mode(1,car_now->A_L.GPIO1,car_now->A_L.Pin1,car_now->A_L.GPIO2,car_now->A_L.Pin2);
			Wheel_set_mode(1,car_now->A_R.GPIO1,car_now->A_R.Pin1,car_now->A_R.GPIO2,car_now->A_R.Pin2);
			Wheel_set_mode(1,car_now->B_L.GPIO1,car_now->B_L.Pin1,car_now->B_L.GPIO2,car_now->B_L.Pin2);
			Wheel_set_mode(1,car_now->B_R.GPIO1,car_now->B_R.Pin1,car_now->B_R.GPIO2,car_now->B_R.Pin2);
			break;
		case 2:
			Wheel_set_mode(2,car_now->A_L.GPIO1,car_now->A_L.Pin1,car_now->A_L.GPIO2,car_now->A_L.Pin2);
			Wheel_set_mode(2,car_now->A_R.GPIO1,car_now->A_R.Pin1,car_now->A_R.GPIO2,car_now->A_R.Pin2);
			Wheel_set_mode(2,car_now->B_L.GPIO1,car_now->B_L.Pin1,car_now->B_L.GPIO2,car_now->B_L.Pin2);
			Wheel_set_mode(2,car_now->B_R.GPIO1,car_now->B_R.Pin1,car_now->B_R.GPIO2,car_now->B_R.Pin2);
			break;
		case 3:
			Wheel_set_mode(2,car_now->A_L.GPIO1,car_now->A_L.Pin1,car_now->A_L.GPIO2,car_now->A_L.Pin2);
			Wheel_set_mode(2,car_now->A_R.GPIO1,car_now->A_R.Pin1,car_now->A_R.GPIO2,car_now->A_R.Pin2);
			Wheel_set_mode(1,car_now->B_L.GPIO1,car_now->B_L.Pin1,car_now->B_L.GPIO2,car_now->B_L.Pin2);
			Wheel_set_mode(1,car_now->B_R.GPIO1,car_now->B_R.Pin1,car_now->B_R.GPIO2,car_now->B_R.Pin2);
			break;
		case 4:
			Wheel_set_mode(1,car_now->A_L.GPIO1,car_now->A_L.Pin1,car_now->A_L.GPIO2,car_now->A_L.Pin2);
			Wheel_set_mode(1,car_now->A_R.GPIO1,car_now->A_R.Pin1,car_now->A_R.GPIO2,car_now->A_R.Pin2);
			Wheel_set_mode(2,car_now->B_L.GPIO1,car_now->B_L.Pin1,car_now->B_L.GPIO2,car_now->B_L.Pin2);
			Wheel_set_mode(2,car_now->B_R.GPIO1,car_now->B_R.Pin1,car_now->B_R.GPIO2,car_now->B_R.Pin2);
			break;
	}
}

void MOVE_Set_around(CAR_struct* car_now)
{
	switch(car_now->direction)
	{
		case 0:
			Wheel_set_mode(2,car_now->A_L.GPIO1,car_now->A_L.Pin1,car_now->A_L.GPIO2,car_now->A_L.Pin2);
			Wheel_set_mode(1,car_now->A_R.GPIO1,car_now->A_R.Pin1,car_now->A_R.GPIO2,car_now->A_R.Pin2);
			Wheel_set_mode(2,car_now->B_L.GPIO1,car_now->B_L.Pin1,car_now->B_L.GPIO2,car_now->B_L.Pin2);
			Wheel_set_mode(1,car_now->B_R.GPIO1,car_now->B_R.Pin1,car_now->B_R.GPIO2,car_now->B_R.Pin2);
			break;
		case 1:
			Wheel_set_mode(1,car_now->A_L.GPIO1,car_now->A_L.Pin1,car_now->A_L.GPIO2,car_now->A_L.Pin2);
			Wheel_set_mode(2,car_now->A_R.GPIO1,car_now->A_R.Pin1,car_now->A_R.GPIO2,car_now->A_R.Pin2);
			Wheel_set_mode(1,car_now->B_L.GPIO1,car_now->B_L.Pin1,car_now->B_L.GPIO2,car_now->B_L.Pin2);
			Wheel_set_mode(2,car_now->B_R.GPIO1,car_now->B_R.Pin1,car_now->B_R.GPIO2,car_now->B_R.Pin2);
			break;
		case 2:
			Wheel_set_mode(0,car_now->A_L.GPIO1,car_now->A_L.Pin1,car_now->A_L.GPIO2,car_now->A_L.Pin2);
			Wheel_set_mode(0,car_now->A_R.GPIO1,car_now->A_R.Pin1,car_now->A_R.GPIO2,car_now->A_R.Pin2);
			Wheel_set_mode(0,car_now->B_L.GPIO1,car_now->B_L.Pin1,car_now->B_L.GPIO2,car_now->B_L.Pin2);
			Wheel_set_mode(0,car_now->B_R.GPIO1,car_now->B_R.Pin1,car_now->B_R.GPIO2,car_now->B_R.Pin2);
			break;
	}
}

void MOVE_SET_MODE(CAR_struct* car_now,CAR_struct* car_last)
{
	if(car_now->round==2)
	{
		if(car_last->round!=2)
		{
			MOVE_set_Speed(0);
		}
		if(car_now->direction==car_last->direction)
		{
			if(car_now->speed!=car_last->speed)
			{
				MOVE_set_Speed(car_now->speed);
			}
		}
		else
		{
			MOVE_set_Speed(0);
			MOVE_Set_direction(car_now);
			MOVE_set_Speed(car_now->speed);
		}
	}
	else
	{
		/*if(car_last->round==2&&car_last->speed!=0)
		{
			MOVE_set_Speed(0);
		}*/
		if(car_now->round!=car_last->round)
		{
			MOVE_set_Speed(0);
			MOVE_Set_around(car_now);
			MOVE_set_Speed(20000);
		}
	}
	
	MOVE_struct_copy(car_now,car_last);
}
