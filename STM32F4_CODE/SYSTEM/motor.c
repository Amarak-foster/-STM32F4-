#include "motor.h"

void motor_Init(void)
{
    // 1. 使能GPIOA、GPIOB、GPIOD的时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE);
    
    // 2. 初始化电机引脚为推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 配置左轮电机引脚：PB7（左轮使能/速度控制），PD6（左轮方向控制）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;         // PB7 - 左轮使能/速度
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     // 输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 高速输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // 无上下拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         // PD6 - 左轮方向
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    // 配置右轮电机引脚：PA4（右轮使能/速度控制），PD7（右轮方向控制）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;         // PA4 - 右轮使能/速度
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;         // PD7 - 右轮方向
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    // 3. 初始化电机状态：停止状态
    // 根据描述，电机停止时两个引脚都置0
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);   // 左轮使能引脚置0
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);   // 右轮使能引脚置0
    GPIO_ResetBits(GPIOD, GPIO_Pin_6);   // 左轮方向置0
    GPIO_ResetBits(GPIOD, GPIO_Pin_7);   // 右轮方向置0
}

void Motor_Left_SetSpeed(uint8_t speed, uint8_t direction)
{
    // 设置方向
    if(speed > 10)speed = 10;
    if (direction == MOTOR_DIR_FORWARD) {
        GPIO_ResetBits(GPIOD, GPIO_Pin_6); // PD6置0（正转）
        GPIO_SetBits(GPIOB, GPIO_Pin_7);
        Mdelay_Lib(speed);
        GPIO_SetBits(GPIOD, GPIO_Pin_6);
        Mdelay_Lib(10-speed);
    } else if (direction == MOTOR_DIR_BACKWARD) {
        GPIO_SetBits(GPIOD, GPIO_Pin_6);   // PD6置1（反转）
        GPIO_ResetBits(GPIOB, GPIO_Pin_7);
        Mdelay_Lib(speed);
        GPIO_ResetBits(GPIOD, GPIO_Pin_6);
        Mdelay_Lib(10-speed);
    }
    
}

void Motor_Right_SetSpeed(uint8_t speed, uint8_t direction)
{
    // 设置方向
    if(speed > 10)speed = 10;
    if (direction == MOTOR_DIR_FORWARD) {
        GPIO_ResetBits(GPIOD, GPIO_Pin_7); // PD7置0（正转）
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        Mdelay_Lib(speed);
        GPIO_SetBits(GPIOD, GPIO_Pin_7);
        Mdelay_Lib(10-speed);
    } else if (direction == MOTOR_DIR_BACKWARD) {
        GPIO_SetBits(GPIOD, GPIO_Pin_7);   // PD7置1（反转）
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        Mdelay_Lib(speed);
        GPIO_ResetBits(GPIOD, GPIO_Pin_7);
        Mdelay_Lib(10-speed);
    }
    
}


