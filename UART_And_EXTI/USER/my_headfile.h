#ifndef USER_MY_HEADFILE_H_
#define USER_MY_HEADFILE_H_


#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "stdio.h"




void my_gpio_init_PA();
void LED_init();
void Key_init();

extern uint8_t Key_0_Flag;


void LED_B5_Show(uint8_t Ctrl);
void LED_E5_Show(uint8_t Ctrl);
void Close_All(void);
void Open_All(void);
void Horse(void);
void Blink(void);
extern u8 LED1_State;
extern u8 LED2_State;


void Key_0_Is();


void My_EXTI_Init(void);



#define USART_REC_LEN  			7  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART_RX_STA;         		//接收状态标记
void uart_init(u32 bound);
void usart_send(u8 byte);
extern int Usart_ctrl;

extern u8 My_SendBuff[8];
extern u8 i;

void Send_for_Windows(void);

#endif /* USER_MYHEADFILE_H_ */