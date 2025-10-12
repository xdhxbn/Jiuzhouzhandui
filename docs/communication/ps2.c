#include "stm32f10x.h"                  // Device header
#include "gpio.h"
#include "Delay.h"

#include "ps2.h"
#include "PS2ins.h"
void PS2_CS(uint8_t choose)
{
	mygpioout(0,4,choose);
}
void PS2_CK(uint8_t edge)
{
	mygpioout(0,5,edge);
}
void PS2_DO(uint8_t bit)//jie DI
{
	mygpioout(0,7,bit);
}
uint8_t PS2_DI(void)
{
	return(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6));
}

void PS2_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	mygpiosetinit(0,7,5);
	mygpiosetinit(0,5,5);
	mygpiosetinit(0,6,3);
	mygpiosetinit(0,4,5);
	
	PS2_CS(1);
	PS2_CK(1);
	
	/*SPI_InitTypeDef SPI_InitStruct;
	
	SPI_InitStruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256 ;
	SPI_InitStruct.SPI_CPHA=SPI_CPHA_1Edge ;
	SPI_InitStruct.SPI_CPOL=SPI_CPOL_High ;
	SPI_InitStruct.SPI_CRCPolynomial=7;
	SPI_InitStruct.SPI_DataSize=SPI_DataSize_8b ;
	SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_LSB;
	SPI_InitStruct.SPI_Mode=SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS=SPI_NSS_Soft ;
	SPI_Init(SPI1,&SPI_InitStruct);
	
	SPI_Cmd(SPI1, ENABLE);*/
}

uint8_t transport_Byte(uint8_t Byte_data)
{
	uint8_t i,recieve=0x00;
	
	for(i=0;i<8;i++)
	{
		PS2_DO(!!(Byte_data&(0x01<<i)));
		PS2_CK(0);
		Delay_us(16);
		
		if(PS2_DI()==1)
		{
			recieve|=(0x01<<i);
		}
		
		PS2_CK(1);
		Delay_us(16);
	}
	
	return(recieve);
}

void PS2_GET_data(PS2data_struct* PS2data)
{
	PS2_CS(0);
  Delay_us(40);
	
	transport_Byte(PS2_start);
	Delay_us(20);
	PS2data->ID=transport_Byte(PS2_ready);
	Delay_us(20);
	PS2data->data1=transport_Byte(PS2_null2);
	Delay_us(20);
  PS2data->data2=transport_Byte(PS2_null2);
	Delay_us(20);
  PS2data->data3=transport_Byte(PS2_null2);
	Delay_us(20);
  PS2data->data4=transport_Byte(PS2_null2);
	Delay_us(20);
  PS2data->data5=transport_Byte(PS2_null2);
	Delay_us(20);
  PS2data->data6=transport_Byte(PS2_null2);
	Delay_us(20);
	PS2data->data7=transport_Byte(PS2_null2);
	Delay_us(20);
	
	PS2_CS(1);
}
/*x means the place of the bit ,from left to right,from 0 to 8*/
uint8_t get_bit(uint8_t bety,uint8_t x)
{
	return(!!(bety&(0x80>>x)));
}
void get_PS2_key(PS2KEY_struct* PS2KEY,PS2data_struct* PS2data,PS2_struct* PS2)
{
	PS2->ID=PS2data->ID;
	
	PS2KEY->LEFT=get_bit(PS2data->data2,0);
	PS2KEY->DOWN=get_bit(PS2data->data2,1);
	PS2KEY->RIGHT=get_bit(PS2data->data2,2);
	PS2KEY->UP=get_bit(PS2data->data2,3);
	PS2KEY->START=get_bit(PS2data->data2,4);
	PS2KEY->R3=get_bit(PS2data->data2,5);
	PS2KEY->L3=get_bit(PS2data->data2,6);
	PS2KEY->SELECT=get_bit(PS2data->data2,7);
	
	PS2KEY->A=get_bit(PS2data->data3,0);
	PS2KEY->S=get_bit(PS2data->data3,1);
	PS2KEY->D=get_bit(PS2data->data3,2);
	PS2KEY->W=get_bit(PS2data->data3,3);
	PS2KEY->R1=get_bit(PS2data->data3,4);
	PS2KEY->L1=get_bit(PS2data->data3,5);
	PS2KEY->R2=get_bit(PS2data->data3,6);
	PS2KEY->L2=get_bit(PS2data->data3,7);
}
void get_PS2_joystick(PS2Joystick_struct* PS2joystick,PS2data_struct* PS2data)
{
	if(PS2data->data4>=PS2_Joystick_x_mid)
	{
		PS2joystick->R_x=1;
		PS2joystick->R_x_speed=PS2data->data4-PS2_Joystick_x_mid;
	}
	else
	{
		PS2joystick->R_x=0;
		PS2joystick->R_x_speed=PS2_Joystick_x_mid-PS2data->data4;
	}
	
	if(PS2data->data5>=PS2_Joystick_y_mid)
	{
		PS2joystick->R_y=1;
		PS2joystick->R_y_speed=PS2data->data5-PS2_Joystick_y_mid;
	}
	else
	{
		PS2joystick->R_y=0;
		PS2joystick->R_y_speed=PS2_Joystick_y_mid-PS2data->data5;
	}
	
	if(PS2data->data6>=PS2_Joystick_x_mid)
	{
		PS2joystick->L_x=1;
		PS2joystick->L_x_speed=PS2data->data6-PS2_Joystick_x_mid;
	}
	else
	{
		PS2joystick->L_x=0;
		PS2joystick->L_x_speed=PS2_Joystick_x_mid-PS2data->data6;
	}
	
	if(PS2data->data7>=PS2_Joystick_y_mid)
	{
		PS2joystick->L_y=1;
		PS2joystick->L_y_speed=PS2data->data7-PS2_Joystick_y_mid;
	}
	else
	{
		PS2joystick->L_y=0;
		PS2joystick->L_y_speed=PS2_Joystick_y_mid-PS2data->data7;
	}
}
