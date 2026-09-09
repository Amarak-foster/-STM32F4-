#include "uart.h"		//	自定义的头文件,对应的 .c 需要包含
#include "stdio.h"	
#include "led.h"		//	使用到相关函数,就需要包含头文件

//	串口1 初始化(bps 参数控制,8位数据,1位停止位,无校验,无流控,收发功能,接收中断)
//	USART1 TX(PA9) RX(PA10)
void Uart1_Init(uint32_t bps)
{
	//	1、初始化 GPIO 控制器
	//	a.使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	//	TX 和 RX 都是 GPIOA 
	
	//	b.配置 GPIO 复用模式; TX 为复用推挽,RX 复用悬空
	GPIO_InitTypeDef GPIO_InitStruct;
  	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;					//	TX 对应引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;				//	复用
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;	//	速率
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;			//	复用推挽
	GPIO_Init(GPIOA,&GPIO_InitStruct);		

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;						//	RX 对应引脚	
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//	复用悬空
	GPIO_Init(GPIOA,&GPIO_InitStruct);	
	
	//	c.配置 GPIO 复用功能
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	//	2、初始化 USART 控制器
	//	a.使能时钟	USART1 的总线为 APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//	b.初始化 USART 结构体的赋值
	//	① 定义一个结构体保存对应 设置信息
	USART_InitTypeDef USART_InitStruct;   
	//	② 结构体对应的成员变量赋值
	USART_InitStruct.USART_BaudRate = bps;						//	波特率参数决定
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;	//	8位数据
	USART_InitStruct.USART_StopBits = USART_StopBits_1;				//	1位停止位
	USART_InitStruct.USART_Parity = USART_Parity_No;					//	无校验
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//	收发功能
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//	③ 调用接口 GPIO_Init 进行初始化操作     
	USART_Init(USART1,&USART_InitStruct);
	
	//	3、接收使用中断
	//	a.串口中断使能	USART1 开启触发 RXNE 中断
	 USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	 
	//	b.NVIC 配置
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;    			//	指定中断通道 USART1_IRQn
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; 	//	抢占优先级 2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2; 				//	响应优先级 2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   			 		//	使能
	NVIC_Init(&NVIC_InitStruct);
	
	//	4、使能串口
	USART_Cmd(USART1,ENABLE);   
}

uint16_t recv = '0';  //	用来保存从串口接收到的字节,也可以为全局变量
//	USAR1 接收中断
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)	//	USART1 接收到数据
	{
		recv = USART_ReceiveData(USART1);				//	读取数据	
		//	可以有其它操作
		Usart_send_byte(USART1,recv);						//	接收中断获取的数据通过 USART1 发回去
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	//	清除接收标志
		Uart1_Ctrl_LED();
	}
}

//	自定义串口发送函数
void Usart_send_byte(USART_TypeDef* USARTx,uint16_t data)
{
			//	确保发送前,TXE被设置; 发送数据寄存器为空
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) != SET); 
			//	TDR 为空,发送数据
	USART_SendData(USARTx,data);
}			

//	重载可以将 printf 输出到 USART1
int fputc(int c, FILE *stream)
{
	USART_SendData(USART1, (uint16_t)c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return c;
}

//	根据 USART1 获取到的数据控制 LED
void Uart1_Ctrl_LED(void)
{
	switch(recv)		//	判断接收中断接收到的数据
	{
		case '1':		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);		break;
		case '2':		GPIO_ToggleBits(GPIOF, GPIO_Pin_10);	break;
		case '3':		GPIO_ToggleBits(GPIOE, GPIO_Pin_13);	break;
		case '4':		GPIO_ToggleBits(GPIOE, GPIO_Pin_14);	break;
		default:		printf("error\r\n");
								break;
	}
}
