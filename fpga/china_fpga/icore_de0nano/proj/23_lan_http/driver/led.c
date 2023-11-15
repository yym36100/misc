/*
 * FILE                : led.c
 * DESCRIPTION         : This file is led driver.
 * Author              : ysloveivy
 * Copyright           :
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 12/20/2015
 *
 * create.
 * --------------------
 */
//--------------------------- Include ---------------------------//
#include "..\include\led.h"
#include "..\fwlib\inc\stm32f4xx_gpio.h"
#include "..\fwlib\inc\stm32f4xx_rcc.h"

//--------------------- Function Prototype ----------------------//
static int initialize(void);

//--------------------------- Variable --------------------------//
LED_T led = {
	.initialize = initialize
};
//--------------------------- Function --------------------------//
/*
 * Name                : initialize
 * Description         : ---
 * Author              : ysloveivy.
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 12/20/2015
 * 
 * create.
 * --------------------
 */
static int initialize(void)
{
	GPIO_InitTypeDef   GPIO_uInitStructure;

	//LED IO��ʼ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;    //����������ɫLED�Ƶ�IO�˿�
	GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_OUT;                          //���ö˿�Ϊ���ģʽ
	GPIO_uInitStructure.GPIO_OType = GPIO_OType_PP;                         //�������
	GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_UP;                           //����
	GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;                     //�����ٶ�Ϊ������

	GPIO_Init(GPIOI,&GPIO_uInitStructure);

	//PI5��PI6��PI7����ɫLED�ƣ�PI5��PI6��PI7�øߵ�λ����Ϩ��
	GPIO_SetBits(GPIOI,GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);

	return 0;
}
