/**
  ************************************* Copyright ****************************** 
  *
  *   (C) Copyright 2022,--,China, Harbin University of Science and Technology.
  *              All Rights Reserved
  *                              
  *       By(Hades_Czq)
  *       https://github.com/hadesczq
  *    
  * FileName   : KEY.c   
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

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//¶ÁÈ¡°´¼ü0

/*variate----------------------------------------------------------------------*/

uint8_t Key_0_Flag = 0;

/*statement--------------------------------------------------------------------*/


/*Function prototype Begin*****************************************************/



/***********************************************************
*@fuction	:Key_0_Is
*@brief		:°´¼ü¼ì²â
*@param		:nop
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void Key_0_Is()
{
    Key_0_Flag = 0;
    if(KEY0 == 0)
    {
        delay_ms(10);
        Key_0_Flag = 1;
    }
    if(KEY0 == 1)
    {
        delay_ms(10);
        Key_0_Flag = 0;
    }
}

/*Function prototype End*******************************************************/



