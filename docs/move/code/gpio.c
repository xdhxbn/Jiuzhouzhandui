#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h" 
uint16_t mygpio_pinnum[16]={GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,
					  GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7,
	                  GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,
                      GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15};
uint16_t mygpiomode[8]={ GPIO_Mode_AIN,/* 模拟输入 */
  GPIO_Mode_IN_FLOATING,/* 浮空输入，复位后的状态 */
  GPIO_Mode_IPD,/* 下拉输入，这里的下拉是指单片机内部的电阻 */
  GPIO_Mode_IPU, /* 上拉输入，这里的上拉是指单片机内部的电阻 */
  GPIO_Mode_Out_OD,/* 开漏输出 */
  GPIO_Mode_Out_PP,/* 推挽输出 */
  GPIO_Mode_AF_OD,/* 复用开漏输出 */
  GPIO_Mode_AF_PP/* 复用推挽输出 */
};
GPIO_TypeDef* mygpioname[7]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG};
uint32_t mygpiotimerset[7]={RCC_APB2Periph_GPIOA,
	                      RCC_APB2Periph_GPIOB,
                          RCC_APB2Periph_GPIOC,
	                      RCC_APB2Periph_GPIOD,
	                      RCC_APB2Periph_GPIOE,
	                      RCC_APB2Periph_GPIOF,
	                      RCC_APB2Periph_GPIOG};
/**
  * @brief  init gpio.
  * @param  which:0~6:the symbol of timer set GPIO A~G.
  * @param  num:0~6:the symbol of the pin of GPIO A~G.
  * @param  mode:0~7:the symbol of work mode of GPIO A~G.		  
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void mygpiosetinit(int which,int num,int mode)
{
	RCC_APB2PeriphClockCmd(mygpiotimerset[which],ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=mygpiomode[mode];
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin=mygpio_pinnum[num];
	GPIO_Init(mygpioname[which],&GPIO_InitStruct);
}

void mygpioout(int which,int num,int mode)
{
	if(mode==0)
	{
		GPIO_ResetBits(mygpioname[which],mygpio_pinnum[num]);
	}
	else
	{
		GPIO_SetBits(mygpioname[which],mygpio_pinnum[num]);
	}
}