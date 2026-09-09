#ifndef __MOTOR_H
#define __MOTOR_H
#include "head.h"

// 电机方向定义
#define MOTOR_DIR_FORWARD    0   // 前进
#define MOTOR_DIR_BACKWARD   1   // 后退

// 电机控制函数声明
void motor_Init(void);                     // 电机初始化
void Motor_Left_SetSpeed(uint8_t speed, uint8_t direction);  // 左轮控制
void Motor_Right_SetSpeed(uint8_t speed, uint8_t direction); // 右轮控制
#endif
