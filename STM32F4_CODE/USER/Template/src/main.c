#include "main.h"
#include "head.h"

// 按键状态变量
uint8_t key_pressed_count = 0;
uint8_t last_key_state = 0;
uint8_t flow_led_active = 0;

// 按键状态去抖变量
uint8_t key_stable_count[4] = {0};
uint8_t key_stable_state[4] = {1, 1, 1, 1}; // 初始状态为未按下(1)
//电机状态变量
uint8_t motor_r = 0;

//小车运动状态变量
uint8_t car_state = 0;
// void key_Press()
// {
// 读取当前按键状态（不去抖，用于计数）
// uint8_t current_key_state[4] = {0};
        
// // KEY1 (PA0)
// current_key_state[0] = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) ? 1 : 0;

// // KEY2 (PE2)
// current_key_state[1] = (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0) ? 1 : 0;

// // KEY3 (PE3)
// current_key_state[2] = (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0) ? 1 : 0;

// // KEY4 (PE4)
// current_key_state[3] = (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0) ? 1 : 0;

// // 简单去抖处理：连续3次读取到相同状态才认为是稳定状态
// for (int i = 0; i < 4; i++) 
// {
//     if (current_key_state[i] == key_stable_state[i]) 
//     {
//         if (key_stable_count[i] < 3) 
//         {
//             key_stable_count[i]++;
//         }
//     } 
//     else 
//     {
//         key_stable_count[i] = 0;
//         key_stable_state[i] = current_key_state[i];
//     }
// }


// // 计算稳定按下的按键数量0
// key_pressed_count = 0;
// for (int i = 0; i < 4; i++) 
// {
//     if (key_stable_count[i] >= 3 && key_stable_state[i] == 1) 
//     {
//         key_pressed_count++;
//     }
// }

// // 处理蜂鸣器：两个及以上按键按下时响
// if (key_pressed_count >= 2) 
// {
//     beep_On();
// } 
// else 
// {
//     beep_Off();
// }
// Motor_Forward(0);
// // 处理单个按键功能
// if (key_pressed_count == 1) 
// {
//     // 检查是哪个按键被按下
//     for (int i = 0; i < 4; i++) 
//     {
//         if (key_stable_count[i] >= 3 && key_stable_state[i] == 1) 
//         {
//             // 单个按键按下，关闭流水灯模式
//             flow_led_active = 0;
//             switch (i) 
//             {
//                 case 0: // KEY1 - 控制D1 (PF9)
//                     GPIO_ResetBits(GPIOF, GPIO_Pin_9);  // D1亮
//                     GPIO_SetBits(GPIOF, GPIO_Pin_10);   // D2灭
//                     GPIO_SetBits(GPIOE, GPIO_Pin_13);   // D3灭
//                     GPIO_SetBits(GPIOE, GPIO_Pin_14);   // D4灭
//                     break;
                    
//                 case 1: // KEY2 - 控制D2 (PF10)
//                     GPIO_SetBits(GPIOF, GPIO_Pin_9);    // D1灭
//                     GPIO_ResetBits(GPIOF, GPIO_Pin_10); // D2亮
//                     GPIO_SetBits(GPIOE, GPIO_Pin_13);   // D3灭
//                     GPIO_SetBits(GPIOE, GPIO_Pin_14);   // D4灭
//                     break;
                    
//                 case 2: // KEY3 - 控制D3 (PE13)
//                     GPIO_SetBits(GPIOF, GPIO_Pin_9);    // D1灭
//                     GPIO_SetBits(GPIOF, GPIO_Pin_10);   // D2灭
//                     GPIO_ResetBits(GPIOE, GPIO_Pin_13); // D3亮
//                     GPIO_SetBits(GPIOE, GPIO_Pin_14);   // D4灭
//                     break;
                    
//                 case 3: // KEY4 - 启动流水灯
//                     // 启动流水灯模式
//                     flow_led_active = 1;
//                     // 关闭所有LED，准备开始流水灯
//                     GPIO_SetBits(GPIOF, GPIO_Pin_9);
//                     GPIO_SetBits(GPIOF, GPIO_Pin_10);
//                     GPIO_SetBits(GPIOE, GPIO_Pin_13);
//                     GPIO_SetBits(GPIOE, GPIO_Pin_14);
//                     led_Liushui();
//                     break;
//             }
//             break; // 只处理一个按键
//         }
//     }
// } 
// else if (key_pressed_count == 0) 
// {
//     // 没有按键按下
//     if (!flow_led_active) 
//     {
//         // 关闭所有LED
//         GPIO_SetBits(GPIOF, GPIO_Pin_9);
//         GPIO_SetBits(GPIOF, GPIO_Pin_10);
//         GPIO_SetBits(GPIOE, GPIO_Pin_13);
//         GPIO_SetBits(GPIOE, GPIO_Pin_14);
//     }
// }
//}

void go_Front()
{
    switch (car_state)
    {
    case 0:
        Motor_Left_SetSpeed(0,1);
        Motor_Right_SetSpeed(0,1);
        break;
    case 1:
        uint8_t sensor_status = yl70_Read();

        // 根据状态执行相应逻辑
        if (sensor_status & (1 << 0))
        {
            // PE5 检测到低电平
            Motor_Left_SetSpeed(0,1);
            Motor_Right_SetSpeed(7,1);
        }
        if (sensor_status & (1 << 1))
        {
            // PE6 检测到低电平
        
            Motor_Left_SetSpeed(7,1);
            Motor_Right_SetSpeed(0,1); 
        }
        if(sensor_status == 0)
        {
            Motor_Left_SetSpeed(7,1);
            Motor_Right_SetSpeed(7,1); 
        }
        if(sensor_status & (1 << 0) && sensor_status & (1 << 1))
        {
            Motor_Left_SetSpeed(0,1);
            Motor_Right_SetSpeed(0,1);
        }
            break;
        default:
            break;
    }
}
int main()
{
    // 初始化各个模块
    led_Init();
    key_Init();
    beep_Init();
    motor_Init();
    yl70_Init();
    Uart1_Init(9600);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    while (1)
    {
        // 读取当前按键状态（不去抖，用于计数）
        // uint8_t current_key_state[4] = {0};
        
        // // KEY1 (PA0)
        // current_key_state[0] = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) ? 1 : 0;
        
        // // KEY2 (PE2)
        // current_key_state[1] = (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0) ? 1 : 0;
        
        // // KEY3 (PE3)
        // current_key_state[2] = (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0) ? 1 : 0;
        
        // // KEY4 (PE4)
        // current_key_state[3] = (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0) ? 1 : 0;
        
        // // 简单去抖处理：连续3次读取到相同状态才认为是稳定状态
        // for (int i = 0; i < 4; i++) 
        // {
        //     if (current_key_state[i] == key_stable_state[i]) 
        //     {
        //         if (key_stable_count[i] < 3) 
        //         {
        //             key_stable_count[i]++;
        //         }
        //     } 
        //     else 
        //     {
        //         key_stable_count[i] = 0;
        //         key_stable_state[i] = current_key_state[i];
        //     }
        // }
        
        
        // // 计算稳定按下的按键数量0
        // key_pressed_count = 0;
        // for (int i = 0; i < 4; i++) 
        // {
        //     if (key_stable_count[i] >= 3 && key_stable_state[i] == 1) 
        //     {
        //         key_pressed_count++;
        //     }
        // }
        
        // // 处理蜂鸣器：两个及以上按键按下时响
        // if (key_pressed_count >= 2) 
        // {
        //     beep_On();
        // } 
        // else 
        // {
        //     beep_Off();
        // }
        // // 处理单个按键功能
        // if (key_pressed_count == 1) 
        // {
        //     // 检查是哪个按键被按下
        //     for (int i = 0; i < 4; i++) 
        //     {
        //         if (key_stable_count[i] >= 3 && key_stable_state[i] == 1) 
        //         {
        //             // 单个按键按下，关闭流水灯模式
        //             flow_led_active = 0;
        //             switch (i) 
        //             {
        //                 case 0: // KEY1 - 控制D1 (PF9)
        //                     GPIO_ResetBits(GPIOF, GPIO_Pin_9);  // D1亮
        //                     GPIO_SetBits(GPIOF, GPIO_Pin_10);   // D2灭
        //                     GPIO_SetBits(GPIOE, GPIO_Pin_13);   // D3灭
        //                     GPIO_SetBits(GPIOE, GPIO_Pin_14);   // D4灭
        //                     break;
                            
        //                 case 1: // KEY2 - 控制D2 (PF10)
        //                     GPIO_SetBits(GPIOF, GPIO_Pin_9);    // D1灭
        //                     GPIO_ResetBits(GPIOF, GPIO_Pin_10); // D2亮
        //                     GPIO_SetBits(GPIOE, GPIO_Pin_13);   // D3灭
        //                     GPIO_SetBits(GPIOE, GPIO_Pin_14);   // D4灭
        //                     break;
                            
        //                 case 2: // KEY3 - 控制D3 (PE13)
        //                     GPIO_SetBits(GPIOF, GPIO_Pin_9);    // D1灭
        //                     GPIO_SetBits(GPIOF, GPIO_Pin_10);   // D2灭
        //                     GPIO_ResetBits(GPIOE, GPIO_Pin_13); // D3亮
        //                     GPIO_SetBits(GPIOE, GPIO_Pin_14);   // D4灭
        //                     break;
                            
        //                 case 3: // KEY4 - 启动流水灯
        //                     // 启动流水灯模式
        //                     flow_led_active = 1;
        //                     // 关闭所有LED，准备开始流水灯
        //                     GPIO_SetBits(GPIOF, GPIO_Pin_9);
        //                     GPIO_SetBits(GPIOF, GPIO_Pin_10);
        //                     GPIO_SetBits(GPIOE, GPIO_Pin_13);
        //                     GPIO_SetBits(GPIOE, GPIO_Pin_14);
        //                     led_Liushui();
        //                     break;
        //             }
        //             break; // 只处理一个按键
        //         }
        //     }
        // } 
        // else if (key_pressed_count == 0) 
        // {
        //     // 没有按键按下
        //     if (!flow_led_active) 
        //     {
        //         // 关闭所有LED
        //         GPIO_SetBits(GPIOF, GPIO_Pin_9);
        //         GPIO_SetBits(GPIOF, GPIO_Pin_10);
        //         GPIO_SetBits(GPIOE, GPIO_Pin_13);
        //         GPIO_SetBits(GPIOE, GPIO_Pin_14);
        //     }
        // }

        // if(flow_led_active)
        // {
        //     led_Liushui();
        // }

        // 读取传感器状态
        // uint8_t sensor_status = yl70_Read();

        // // 根据状态执行相应逻辑
        // if (sensor_status & (1 << 0))
        // {
        //     Motor_Left_SetSpeed(8,1);// PC6 检测到黑线
        //     //Motor_Right_SetSpeed(0,1);
        // }
        // if (sensor_status & (1 << 1))
        // {
        //     Motor_Left_SetSpeed(0,1);// PC7 检测到黑线
        //     //Motor_Right_SetSpeed(8,1);
        // }
        // 读取传感器状态
        go_Front();// 前进
        
    }
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) 
    {
        // 翻转LED状态
        delay_ms(20);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) 
        {
            // 翻转LED状态
            GPIO_ToggleBits(GPIOF, GPIO_Pin_9 | GPIO_Pin_10);
            GPIO_ToggleBits(GPIOE, GPIO_Pin_13 | GPIO_Pin_14);
            car_state = !car_state;
        }

        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET) 
    {

        // 控制蜂鸣器开关
        beep_Toggle();
        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}
void EXTI3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) 
    {
        // 启动流水灯
        flow_led_active = !flow_led_active;
        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

