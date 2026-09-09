#include "key.h"

void key_Init()
{
    // 1. 使能GPIOA和GPIOE时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);
    
    // 2. 初始化PA0为上拉输入
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 配置PA0（按键1）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      // 输入模式
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      // 上拉模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 输入模式下速度可选
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 配置PE2、PE3、PE4（按键2、3、4）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // 3. 配置EXTI线
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // 使能SYSCFG时钟

    // 配置PA0 (按键1) 连接到EXTI Line0
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
    // 配置PE2 (按键2) 连接到EXTI Line2
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
    // 配置PE3 (按键3) 连接到EXTI Line3
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);

    // 4. 配置EXTI触发模式
    EXTI_InitTypeDef EXTI_InitStruct;

    // 按键1 (PA0) - EXTI Line0
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    // 按键2 (PE2) - EXTI Line2
    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    // 按键3 (PE3) - EXTI Line3
    EXTI_InitStruct.EXTI_Line = EXTI_Line3;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    // 5. 配置NVIC优先级
    NVIC_InitTypeDef NVIC_InitStruct;

    // 按键1 (EXTI Line0)
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; // 最高优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 按键2 (EXTI Line2)
    NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 较低优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 按键3 (EXTI Line3)
    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 同按键2优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0;        // 定义变量，默认键码值为0
    
    // 检查PA0（按键1）
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)         // 读PA0输入寄存器的状态，如果为0，则代表按键1按下
    {
        Mdelay_Lib(20);                                           // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0); // 等待按键松手
        Mdelay_Lib(20);                                           // 延时消抖
        KeyNum = 1;                                             // 置键码为1
    }
    
    // 检查PE2（按键2）
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0)         // 读PE2输入寄存器的状态，如果为0，则代表按键2按下
    {
        Mdelay_Lib(20);                                           // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0); // 等待按键松手
        Mdelay_Lib(20);                                           // 延时消抖
        KeyNum = 2;                                             // 置键码为2
    }
    
    // 检查PE3（按键3）
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0)         // 读PE3输入寄存器的状态，如果为0，则代表按键3按下
    {
        Mdelay_Lib(20);                                           // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0); // 等待按键松手
        Mdelay_Lib(20);                                           // 延时消抖
        KeyNum = 3;                                             // 置键码为3
    }
    
    // 检查PE4（按键4）
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0)         // 读PE4输入寄存器的状态，如果为0，则代表按键4按下
    {
        Mdelay_Lib(20);                                           // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0); // 等待按键松手
        Mdelay_Lib(20);                                           // 延时消抖
        KeyNum = 4;                                             // 置键码为4
    }
    
    return KeyNum;           // 返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0
}