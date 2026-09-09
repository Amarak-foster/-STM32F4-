#include "beep.h"

void beep_Init(void)
{
    // 开启GPIOF的时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    
    // GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           // 使用PF8引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       // 输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;    // 下拉
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    
    // 初始状态设为低电平，蜂鸣器关闭
    GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}

void beep_On(void)
{
    // 蜂鸣器打开（设为低电平）
    GPIO_SetBits(GPIOF, GPIO_Pin_8);
}

void beep_Off(void)
{
    // 蜂鸣器关闭（设为高电平）
    GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}

void beep_Toggle(void)
{
    // 翻转蜂鸣器状态
    GPIO_ToggleBits(GPIOF, GPIO_Pin_8);
}

void beep_Voice(uint16_t duration_ms)
{
    // 蜂鸣器发声指定时长
    beep_On();                     // 打开蜂鸣器
    Mdelay_Lib(duration_ms);         // 延时指定时间
    beep_Off();                    // 关闭蜂鸣器
}