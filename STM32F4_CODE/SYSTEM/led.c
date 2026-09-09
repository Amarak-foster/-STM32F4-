#include "led.h"

void led_Init()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOE, ENABLE);
    //2. 初始化led0,1
    GPIO_InitTypeDef LED_InitStruct;
    LED_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    LED_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    LED_InitStruct.GPIO_OType = GPIO_OType_PP;
    LED_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &LED_InitStruct);

    // //2. 初始化led2,3
    LED_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOE, &LED_InitStruct);
    GPIO_SetBits(GPIOF, GPIO_Pin_9);
    GPIO_SetBits(GPIOF, GPIO_Pin_10);
    GPIO_SetBits(GPIOE, GPIO_Pin_13);
    GPIO_SetBits(GPIOE, GPIO_Pin_14);
}

void led_Liushui()
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_9);
    Mdelay_Lib(500);
    GPIO_SetBits(GPIOF, GPIO_Pin_9);
    GPIO_ResetBits(GPIOF, GPIO_Pin_10);
    Mdelay_Lib(500);
    GPIO_SetBits(GPIOF, GPIO_Pin_10);
    GPIO_ResetBits(GPIOE, GPIO_Pin_13);
    Mdelay_Lib(500);
    GPIO_SetBits(GPIOE, GPIO_Pin_13);
    GPIO_ResetBits(GPIOE, GPIO_Pin_14);
    Mdelay_Lib(500);
    GPIO_SetBits(GPIOE, GPIO_Pin_14);
}


