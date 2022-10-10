/**
  ************************************* Copyright ****************************** 
  *
  *   (C) Copyright 2022,--,China, Harbin University of Science and Technology.
  *              All Rights Reserved
  *                              
  *       By(Hades_Czq)
  *       https://github.com/hadesczq
  *    
  * FileName   : LED.c   
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
*@fuction	:LED_B5_Show
*@brief		:PB5_Ctrl
*@param		:uint8_t Ctrl
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void LED_B5_Show(uint8_t Ctrl)
{
    if(Ctrl == 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_5);
    }
    if(Ctrl == 1)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    }
}

/***********************************************************
*@fuction	:LED_E5_Show
*@brief		:PE5_Ctrl
*@param		:uint8_t Ctrl
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void LED_E5_Show(uint8_t Ctrl)
{
    if(Ctrl == 0)
    {
        GPIO_SetBits(GPIOE, GPIO_Pin_5);
    }
    if(Ctrl == 1)
    {
        GPIO_ResetBits(GPIOE, GPIO_Pin_5);
    }
}

void Close_All(void)
{
    LED_B5_Show(0);
    LED_E5_Show(0);
}
void Open_All(void)
{
    LED_B5_Show(1);
    LED_E5_Show(1);
}
void Horse(void)
{
    while(Usart_ctrl == 3)
    {
        LED_B5_Show(1);
        LED_E5_Show(0);
        delay_ms(200);
        LED_B5_Show(0);
        LED_E5_Show(1);
        delay_ms(200);
    }
}
void Blink(void)
{
    while(Usart_ctrl == 4)
    {
        LED_B5_Show(1);
        LED_E5_Show(1);
        delay_ms(200);
        LED_B5_Show(0);
        LED_E5_Show(0);
        delay_ms(200);
    }
}


/*Function prototype End*******************************************************/




