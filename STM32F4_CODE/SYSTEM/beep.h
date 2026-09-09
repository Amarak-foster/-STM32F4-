#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "head.h"

// 函数声明
void beep_Init(void);
void beep_On(void);
void beep_Off(void);
void beep_Toggle(void);
void beep_Voice(uint16_t duration_ms);

#endif /* __BEEP_H */
