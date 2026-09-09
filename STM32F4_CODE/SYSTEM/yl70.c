#include "yl70.h"
void yl70_Init()
{
    // 1. 使能 GPIOC 时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    // 2. 配置 PE5 和 PE6 为浮空输入模式
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; // 选择 PE5 和 PE6
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;         // 输入模式
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;      // 浮空模式（无上拉/下拉）
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;     // 输入模式下速度可选（无实际影响）
    GPIO_Init(GPIOE, &GPIO_InitStruct);                // 初始化 GPIOE

}

uint8_t yl70_Read(void)//灯灭，输入高电平，灯亮，输入低电平
{
    uint8_t status = 0;

    // 读取 PE5 的状态
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == 1)
    {
        status |= (1 << 0); // 如果 PE5 为低电平，设置 Bit 0
    }

    // 读取 PE6 的状态
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == 1)
    {
        status |= (1 << 1); // 如果 PE6 为低电平，设置 Bit 1
    }

    return status;
}
