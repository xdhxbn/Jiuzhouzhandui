#include "stm32f10x.h"                  // Device header
#include "gpio.h"
#include "Delay.h"

/*crr 500 2500*/
void steering_engine_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=20000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=500;
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);
	
	mygpiosetinit(0,1,7);
	
	TIM_Cmd(TIM2,ENABLE);
}

void set_angle(uint16_t ccr)
{
	TIM_SetCompare2(TIM2,ccr);
}

void engine_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=1000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=18-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=100;
	TIM_OC3Init(TIM3,&TIM_OCInitStruct);
	
	mygpiosetinit(1,0,7);
	mygpiosetinit(0,4,5);
	mygpiosetinit(0,5,5);
	mygpiosetinit(0,10,5);
	
	
	mygpioout(0,10,1);
	mygpioout(0,4,1);
	mygpioout(0,5,0);
	
	TIM_Cmd(TIM3,ENABLE);
}

void engine_mode(int mode)
{
	switch(mode)
	{
		case 1://back
			mygpioout(0,5,0);
			mygpioout(0,4,1);
			break;
		case 2://forword
			mygpioout(0,5,1);
			mygpioout(0,4,0);
			break;
	}
}
void engine_start(int start)
{
	mygpioout(0,10,start);
}
void engine_speed(int speed)
{
	if(speed>=0)
	{
		engine_mode(1);
		TIM_SetCompare3(TIM3,speed);
	}
	else
	{
		engine_mode(2);
		TIM_SetCompare3(TIM3,-speed);
		
	}
}
