#include "my_headfile.h"

void my_gpio_init_PA()
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PA�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			    //LED0-->PA.2 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);			     //��ʼ��GPIOA.2

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			    //LED0-->PA.8 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);			     //��ʼ��GPIOA.8
}

void LED_init()
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    GPIO_SetBits(GPIOE, GPIO_Pin_5);
}

void Key_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void uart_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��

    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

    //USART1_RX	  GPIOA.10��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

    //USART ��ʼ������

    USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1

}
