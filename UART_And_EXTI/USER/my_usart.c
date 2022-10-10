/**
  ************************************* Copyright ******************************
  *
  *   (C) Copyright 2022,--,China, Harbin University of Science and Technology.
  *              All Rights Reserved
  *
  *       By(Hades_Czq)
  *       https://github.com/hadesczq
  *
  * FileName   : my_usart.c
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

u16 USART_RX_STA = 0;     //接收状态标记
int Usart_ctrl = 0; //控制状态标志
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u8 ResBuff[8] = {0, 0, 0, 0, 0, 0, 0, 0};
u8 Res_Count = 0;
u8 My_SendBuff[8] = {0, 0, 0, 0, 0, 0, 0, 0};
u8 i = 0;

/*statement--------------------------------------------------------------------*/


/*Function prototype Begin*****************************************************/

//////////////////////////////////////////////////////////////////////////////////
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
    while((USART1->SR & 0X40) == 0); //循环发送,直到发送完毕
    USART1->DR = (u8) ch;
    return ch;
}
#endif

/*使用microLib的方法*/
/*
int fputc(int ch, FILE *f)
{
USART_SendData(USART1, (uint8_t) ch);

while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}

   return ch;
}
int GetKey (void)  {

   while (!(USART1->SR & USART_FLAG_RXNE));

   return ((int)(USART1->DR & 0x1FF));
}
*/

#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目

/***********************************************************
*@fuction	:USART1_IRQHandler
*@brief		:串口中断
*@param		:--
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
    u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
    OSIntEnter();
#endif
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART1);	//读取接收到的数据
        ResBuff[Res_Count] = Res;
        if(Res == 0xAA || Res_Count > 0)
        {
            Res_Count++;
        }
        else
            Res_Count = 0;
        if(Res_Count == 8)
        {
            Res_Count = 0;
            //校验位
            if(ResBuff[0] == 0xAA && ResBuff[1] == 0xBB && ResBuff[2] == 0xCC && ResBuff[3] == 0xDD)
            {
                if(ResBuff[5] == 0x01)
                {
                    LED_E5_Show(1);
                    LED1_State = 1;
                }
                else if(ResBuff[5] == 0x00)
                {
                    LED_E5_Show(0);
                    LED1_State = 0;
                }
                Send_for_Windows();

            }
        }


        if(USART_RX_STA > (USART_REC_LEN - 1))USART_RX_STA = 0; //接收数据错误,重新开始接收
    }
}
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
OSIntExit();
#endif
#endif

/***********************************************************
*@fuction	:usart_send
*@brief		:串口发送
*@param		:u8 byte
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void usart_send(u8 byte)
{
    USART_SendData(USART1, byte);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //发送完成标志位
}

/***********************************************************
*@fuction	:Send_for_Windows
*@brief		:向上位机发送数据
*@param		:void
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void Send_for_Windows(void)
{
    My_SendBuff[0] = 0xAA;
    My_SendBuff[1] = 0xBB;
    My_SendBuff[2] = 0xCC;
    My_SendBuff[3] = 0xDD;
    My_SendBuff[4] = 0x01;

    if(LED1_State == 0)
    {
        My_SendBuff[5] = 0x00;
    }
    else if(LED1_State == 1)
    {
        My_SendBuff[5] = 0x01;
    }
    if(LED2_State == 0)
    {
        My_SendBuff[6] = 0x00;
    }
    else if(LED2_State == 1)
    {
        My_SendBuff[6] = 0x01;
    }
    //向上位机发送数据
    for(i = 0; i < 8; i++)
    {
        usart_send(My_SendBuff[i]);
    }
}

/*Function prototype End*******************************************************/




