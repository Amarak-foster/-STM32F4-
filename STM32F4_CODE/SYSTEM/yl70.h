#ifndef __YL70_H
#define __YL70_H
#include "head.h"

// 初始化 YL70 红外循迹模块
void yl70_Init(void);

// 读取 YL70 模块的状态
uint8_t yl70_Read(void);
#endif