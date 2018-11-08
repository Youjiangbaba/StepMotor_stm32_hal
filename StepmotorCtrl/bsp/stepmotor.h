#ifndef __STEPMOTOR_H__
#define __STEPMOTOR_H__
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim1, htim2, htim8;

/* 类型定义 ------------------------------------------------------------------*/
typedef struct step{
	__IO uint8_t  MOTOR_state;
  __IO uint16_t ACC_nums;
  __IO uint16_t DEC_nums;
	__IO uint32_t ACC_steps;
	__IO uint32_t RUN_steps;
	__IO uint32_t	DEC_steps;
}Motor1_Data,Motor2_Data,Motor3_Data,Motor4_Data;

                       //电机选择
#define MOTOR_1     1
#define MOTOR_2     2
#define MOTOR_3     3
#define MOTOR_4     4
                                                   //状态选择
#define STATE_ACC   1
#define STATE_DEC   2
#define STATE_RUN   3
#define STATE_STOP  0
#define STATE_NONE  99

#define Mone_max_speed     1000
#define Mone_target_steps  0xffff
#define Mtwo_max_speed     1000
#define Mtwo_target_steps  0xffff
#define Mthree_max_speed     1000
#define Mthree_target_steps  0xffff
#define Mfour_max_speed     1000
#define Mfour_target_steps  0xffff

#define STEPMOTOR_TIM_Prescaler                   1
// 定义定时器周期，输出比较模式周期设置为0xFFFF
#define STEPMOTOR_TIM_PERIOD                   0xFFFF

#define STEPMOTOR_1_TIMx                      TIM1
#define htimx_STEPMOTOR_1                     htim1
#define STEPMOTOR_1_TIM_CHANNEL_x             TIM_CHANNEL_1
#define STEPMOTOR_1_TIM_IT_CCx                TIM_IT_CC1
#define STEPMOTOR_1_TIM_FLAG_CCx              TIM_FLAG_CC1
#define STEPMOTOR_1_CCRx                       CCR1

#define STEPMOTOR_2_TIMx                      TIM2
#define htimx_STEPMOTOR_2                     htim2
#define STEPMOTOR_2_TIM_CHANNEL_x             TIM_CHANNEL_1
#define STEPMOTOR_2_TIM_IT_CCx                TIM_IT_CC1
#define STEPMOTOR_2_TIM_FLAG_CCx              TIM_FLAG_CC1
#define STEPMOTOR_2_CCRx                      CCR1

#define STEPMOTOR_3_TIMx                      TIM8
#define htimx_STEPMOTOR_3                     htim8
#define STEPMOTOR_3_TIM_CHANNEL_x             TIM_CHANNEL_1
#define STEPMOTOR_3_TIM_IT_CCx                TIM_IT_CC1
#define STEPMOTOR_3_TIM_FLAG_CCx              TIM_FLAG_CC1
#define STEPMOTOR_3_CCRx                      CCR1

#define STEPMOTOR_4_TIMx                      
#define htimx_STEPMOTOR_4
#define STEPMOTOR_4_TIM_CHANNEL_x             
#define STEPMOTOR_4_TIM_IT_CCx                

#define FALSE                                 0
#define TRUE                                  1
#define CW                                    0                                 // 顺时针
#define CCW                                   1                                 // 逆时针
void StepMotor_Init(uint8_t motor_choose,uint16_t start_NUMS);






#endif