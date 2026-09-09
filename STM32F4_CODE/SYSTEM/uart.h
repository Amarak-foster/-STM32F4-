#ifndef __UART_H__
#define __UART_H__

#include "head.h"				//	一些标准库中的声明语句


//	串口1 初始化(bps 参数控制,8位数据,1位停止位,无校验,无流控,收发功能,接收中断)
//	USART1 TX(PA9) RX(PA10)
void Uart1_Init(uint32_t bps);

//	自定义串口发送函数
void Usart_send_byte(USART_TypeDef* USARTx,uint16_t data);


//	根据 USART1 获取到的数据控制 LED
void Uart1_Ctrl_LED(void);

#endif
