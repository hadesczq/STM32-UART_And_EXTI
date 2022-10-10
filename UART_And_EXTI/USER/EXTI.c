/**
  ************************************* Copyright ****************************** 
  *
  *   (C) Copyright 2022,--,China, Harbin University of Science and Technology.
  *              All Rights Reserved
  *                              
  *       By(Hades_Czq)
  *       https://github.com/hadesczq
  *    
  * FileName   : EXTI.c   
  * Version    : v1.0		
  * Author     : Hades_Czq			
  * Date       : 2022-10-10         
  * Description:    
  * Function List:  
  	1. ....
  	   <version>: 		
  <modify staff>:
  		  <data>:
   <description>:  
  	2. ...
  ******************************************************************************
 */
 
/*include----------------------------------------------------------------------*/
#include "my_headfile.h"

/*define-----------------------------------------------------------------------*/


/*variate----------------------------------------------------------------------*/


/*statement--------------------------------------------------------------------*/


/*Function prototype Begin*****************************************************/


/***********************************************************
*@fuction	:My_EXTI_Init
*@brief		:外部中断初始化
*@param		:void
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void My_EXTI_Init(void)
{

    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//KEY0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}

/***********************************************************
*@fuction	:EXTI4_IRQHandler
*@brief		:外部中断服务函数
*@param		:void
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void EXTI4_IRQHandler(void)
{

    Key_0_Is();

    if(Key_0_Flag == 1)
    {
        LED_B5_Show(1);
        LED2_State = 1;

        while(Key_0_Flag == 1)
        {
            Key_0_Is();
            delay_ms(500);
            Send_for_Windows();
        }
    }
    if(Key_0_Flag == 0)
    {
        LED_B5_Show(0);
        LED2_State = 0;
        //Send_for_Windows();
    }

    EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位
}


/*Function prototype End*******************************************************/




