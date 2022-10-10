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

u16 USART_RX_STA = 0;     //����״̬���
int Usart_ctrl = 0; //����״̬��־
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 ResBuff[8] = {0, 0, 0, 0, 0, 0, 0, 0};
u8 Res_Count = 0;
u8 My_SendBuff[8] = {0, 0, 0, 0, 0, 0, 0, 0};
u8 i = 0;

/*statement--------------------------------------------------------------------*/


/*Function prototype Begin*****************************************************/

//////////////////////////////////////////////////////////////////////////////////
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

#if 1
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
    int handle;

};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x = x;
}
//�ض���fputc����
int fputc(int ch, FILE *f)
{
    while((USART1->SR & 0X40) == 0); //ѭ������,ֱ���������
    USART1->DR = (u8) ch;
    return ch;
}
#endif

/*ʹ��microLib�ķ���*/
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

#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ

/***********************************************************
*@fuction	:USART1_IRQHandler
*@brief		:�����ж�
*@param		:--
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void USART1_IRQHandler(void)                	//����1�жϷ������
{
    u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
    OSIntEnter();
#endif
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res = USART_ReceiveData(USART1);	//��ȡ���յ�������
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
            //У��λ
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


        if(USART_RX_STA > (USART_REC_LEN - 1))USART_RX_STA = 0; //�������ݴ���,���¿�ʼ����
    }
}
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
OSIntExit();
#endif
#endif

/***********************************************************
*@fuction	:usart_send
*@brief		:���ڷ���
*@param		:u8 byte
*@return	:void
*@author	:Hades_Czq
*@date		:2022-10-10
***********************************************************/

void usart_send(u8 byte)
{
    USART_SendData(USART1, byte);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //������ɱ�־λ
}

/***********************************************************
*@fuction	:Send_for_Windows
*@brief		:����λ����������
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
    //����λ����������
    for(i = 0; i < 8; i++)
    {
        usart_send(My_SendBuff[i]);
    }
}

/*Function prototype End*******************************************************/




