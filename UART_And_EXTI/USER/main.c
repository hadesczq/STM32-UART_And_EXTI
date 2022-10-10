/**
  ************************************* Copyright ****************************** 
  *
  *   (C) Copyright 2022,--,China, Harbin University of Science and Technology.
  *              All Rights Reserved
  *                              
  *       By(Hades_Czq)
  *       https://github.com/hadesczq
  *    
  * FileName   : main.c   
  * Version    : v1.0		
  * Author     : Hades_Czq			
  * Date       : 2022-10-07         
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
u8 LED1_State = 0;
u8 LED2_State = 0;

/*statement--------------------------------------------------------------------*/


/*Function prototype Begin*****************************************************/
int main(void)
{

    LED_init();
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);
    Key_init();
    My_EXTI_Init();

    while(1)
    {
        Send_for_Windows();
        delay_ms(5000);
    }
}

/*Function prototype End*******************************************************/








