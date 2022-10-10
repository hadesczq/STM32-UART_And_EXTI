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
*@brief		:�ⲿ�жϳ�ʼ��
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

    //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

/***********************************************************
*@fuction	:EXTI4_IRQHandler
*@brief		:�ⲿ�жϷ�����
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

    EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ
}


/*Function prototype End*******************************************************/




