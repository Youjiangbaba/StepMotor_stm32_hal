#include "stepmotor.h"
#include "time.h"
#include <math.h>
/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/

__IO uint8_t MOTOR_CHOOSE;        
Motor1_Data Mone;
Motor2_Data Mtwo;
Motor3_Data Mthree;
Motor4_Data Mfour;
/**
  * 电机 1 的加减速函数 
	*输入参数 ： max_speed ：最大速度   0xffff -- 0 越小越大
	*            target_steps： 目标步数
*/
void StepMotorRun_1(uint16_t max_speed,uint32_t target_steps)
{
  __IO static uint32_t rest = 0;
	__IO static uint8_t i = 0;
//	__IO static uint8_t state = STATE_ACC;
	__IO uint16_t last_accnums,last_decnums;
	__IO static uint32_t count_steps = 0;
	__IO uint16_t Step_nums;
	i ++;
	if(i==2)
	{
	  i = 0;
		switch(Mone.MOTOR_state)
		{
			case STATE_ACC:
			{
				 count_steps++;
				 last_accnums = Mone.ACC_nums;
				 Mone.ACC_nums = last_accnums- (((2 *last_accnums) + rest)/(4 * count_steps + 1));//计算新(下)一步脉冲周期(时间间隔)
				 rest = ((2 * last_accnums)+rest)%(4 * count_steps + 1);// 计算余数，下次计算补上余数，减少误差
				 Step_nums = Mone.ACC_nums;
				 if(max_speed/Mone.ACC_nums)
				 { 
					 rest = 0;
				   Mone.ACC_steps = count_steps;
					 Mone.MOTOR_state = STATE_RUN;
				 }
			}break;
			case STATE_RUN:
			{
			  count_steps ++; 
			  Step_nums = max_speed;
				if(count_steps / (target_steps - Mone.ACC_steps))             ///////
				{	 
				  Mone.RUN_steps = count_steps - Mone.ACC_steps;
					Mone.DEC_nums = max_speed;
				  Mone.MOTOR_state = STATE_DEC;
				}
			}break;
			case STATE_DEC:
			{
			  count_steps ++;
				last_decnums = Mone.DEC_nums ;
				Mone.DEC_nums = last_decnums + (((2*last_decnums) + rest)/(4 * (uint32_t)(target_steps - count_steps) - 1));//计算新(下)一步脉冲周期(时间间隔)
				rest = ((2 * last_decnums)+rest)%(4 * (uint32_t)(target_steps - count_steps) - 1);// 计算余数，下次计算补上余数，减少误差
				Step_nums = Mone.DEC_nums;
				if(count_steps/target_steps)
				{
					rest = 0;
				  Mone.MOTOR_state = STATE_STOP;
					Mone.DEC_steps = count_steps - Mone.RUN_steps - Mone.ACC_steps;
				}
			}break;
			case STATE_STOP:
			{
				count_steps = 0;
				HAL_TIM_OC_Stop_IT(&htimx_STEPMOTOR_1,STEPMOTOR_1_TIM_CHANNEL_x);
				Mone.MOTOR_state = STATE_NONE;
			}break;
		}
		STEPMOTOR_1_TIMx -> STEPMOTOR_1_CCRx = Step_nums;
	}
}
/**
  * 电机 2 的加减速函数 
	*输入参数 ： max_speed ：最大速度   0xffff -- 0 越小越大
	*            target_steps： 目标步数
*/
void StepMotorRun_2(uint16_t max_speed,uint32_t target_steps)
{
  __IO static uint32_t rest = 0;
	__IO static uint8_t i = 0;
//	__IO static uint8_t state = STATE_ACC;
	__IO uint16_t last_accnums,last_decnums;
	__IO static uint32_t count_steps = 0;
	__IO uint16_t Step_nums;
	i ++;
	if(i==2)
	{
	  i = 0;
		switch(Mtwo.MOTOR_state)
		{
			case STATE_ACC:
			{
				 count_steps++;
				 last_accnums = Mtwo.ACC_nums;
				 Mtwo.ACC_nums = last_accnums- (((2 *last_accnums) + rest)/(4 * count_steps + 1));//计算新(下)一步脉冲周期(时间间隔)
				 rest = ((2 * last_accnums)+rest)%(4 * count_steps + 1);// 计算余数，下次计算补上余数，减少误差
				 Step_nums = Mtwo.ACC_nums;
				 if(max_speed/Mtwo.ACC_nums)
				 { 
					 rest = 0;
				   Mtwo.ACC_steps = count_steps;
					 Mtwo.MOTOR_state = STATE_RUN;
				 }
			}break;
			case STATE_RUN:
			{
			  count_steps ++; 
			  Step_nums = max_speed;
				if(count_steps / (target_steps - Mtwo.ACC_steps))             ///////
				{	 
				  Mtwo.RUN_steps = count_steps - Mtwo.ACC_steps;
					Mtwo.DEC_nums = max_speed;
				  Mtwo.MOTOR_state = STATE_DEC;
				}
			}break;
			case STATE_DEC:
			{
			  count_steps ++;
				last_decnums = Mtwo.DEC_nums ;
				Mtwo.DEC_nums = last_decnums + (((2*last_decnums) + rest)/(4 * (uint32_t)(target_steps - count_steps) - 1));//计算新(下)一步脉冲周期(时间间隔)
				rest = ((2 * last_decnums)+rest)%(4 * (uint32_t)(target_steps - count_steps) - 1);// 计算余数，下次计算补上余数，减少误差
				Step_nums = Mtwo.DEC_nums;
				if(count_steps/target_steps)
				{
					rest = 0;
				  Mtwo.MOTOR_state = STATE_STOP;
					Mtwo.DEC_steps = count_steps - Mtwo.RUN_steps - Mtwo.ACC_steps;
				}
			}break;
			case STATE_STOP:
			{
				count_steps = 0;
				HAL_TIM_OC_Stop_IT(&htimx_STEPMOTOR_2,STEPMOTOR_2_TIM_CHANNEL_x);
				Mtwo.MOTOR_state = STATE_NONE;
			}break;
		}
		STEPMOTOR_2_TIMx -> STEPMOTOR_2_CCRx = Step_nums;
	}
}
/**
  * 电机 3 的加减速函数 
	*输入参数 ： max_speed ：最大速度   0xffff -- 0 越小越大
	*            target_steps： 目标步数
*/
void StepMotorRun_3(uint16_t max_speed,uint32_t target_steps)
{
  __IO static uint32_t rest = 0;
	__IO static uint8_t i = 0;
//	__IO static uint8_t state = STATE_ACC;
	__IO uint16_t last_accnums,last_decnums;
	__IO static uint32_t count_steps = 0;
	__IO uint16_t Step_nums;
	i ++;
	if(i==2)
	{
	  i = 0;
		switch(Mthree.MOTOR_state)
		{
			case STATE_ACC:
			{
				 count_steps++;
				 last_accnums = Mthree.ACC_nums;
				 Mthree.ACC_nums = last_accnums- (((2 *last_accnums) + rest)/(4 * count_steps + 1));//计算新(下)一步脉冲周期(时间间隔)
				 rest = ((2 * last_accnums)+rest)%(4 * count_steps + 1);// 计算余数，下次计算补上余数，减少误差
				 Step_nums = Mthree.ACC_nums;
				 if(max_speed/Mthree.ACC_nums)
				 { 
					 rest = 0;
				   Mthree.ACC_steps = count_steps;
					 Mthree.MOTOR_state = STATE_RUN;
				 }
			}break;
			case STATE_RUN:
			{
			  count_steps ++; 
			  Step_nums = max_speed;
				if(count_steps / (target_steps - Mthree.ACC_steps))             ///////
				{	 
				  Mthree.RUN_steps = count_steps - Mthree.ACC_steps;
					Mthree.DEC_nums = max_speed;
				  Mthree.MOTOR_state = STATE_DEC;
				}
			}break;
			case STATE_DEC:
			{
			  count_steps ++;
				last_decnums = Mthree.DEC_nums ;
				Mthree.DEC_nums = last_decnums + (((2*last_decnums) + rest)/(4 * (uint32_t)(target_steps - count_steps) - 1));//计算新(下)一步脉冲周期(时间间隔)
				rest = ((2 * last_decnums)+rest)%(4 * (uint32_t)(target_steps - count_steps) - 1);// 计算余数，下次计算补上余数，减少误差
				Step_nums = Mthree.DEC_nums;
				if(count_steps/target_steps)
				{
					rest = 0;
				  Mthree.MOTOR_state = STATE_STOP;
					Mthree.DEC_steps = count_steps - Mthree.RUN_steps - Mthree.ACC_steps;
				}
			}break;
			case STATE_STOP:
			{
				count_steps = 0;
				HAL_TIM_OC_Stop_IT(&htimx_STEPMOTOR_3,STEPMOTOR_3_TIM_CHANNEL_x);
				Mthree.MOTOR_state = STATE_NONE;
			}break;
		}
		STEPMOTOR_3_TIMx -> STEPMOTOR_3_CCRx = Step_nums;
	}
}
/**
  * 电机 3 的加减速函数 
	*输入参数 ： max_speed ：最大速度   0xffff -- 0 越小越大
	*            target_steps： 目标步数
*/
void StepMotorRun_4(uint16_t max_speed,uint32_t target_steps)
{
  __IO static uint32_t rest = 0;
	__IO static uint8_t i = 0;
//	__IO static uint8_t state = STATE_ACC;
	__IO uint16_t last_accnums,last_decnums;
	__IO static uint32_t count_steps = 0;
	__IO uint16_t Step_nums;
	i ++;
	if(i==2)
	{
	  i = 0;
		switch(Mfour.MOTOR_state)
		{
			case STATE_ACC:
			{
				 count_steps++;
				 last_accnums = Mfour.ACC_nums;
				 Mfour.ACC_nums = last_accnums- (((2 *last_accnums) + rest)/(4 * count_steps + 1));//计算新(下)一步脉冲周期(时间间隔)
				 rest = ((2 * last_accnums)+rest)%(4 * count_steps + 1);// 计算余数，下次计算补上余数，减少误差
				 Step_nums = Mfour.ACC_nums;
				 if(max_speed/Mfour.ACC_nums)
				 { 
					 rest = 0;
				   Mfour.ACC_steps = count_steps;
					 Mfour.MOTOR_state = STATE_RUN;
				 }
			}break;
			case STATE_RUN:
			{
			  count_steps ++; 
			  Step_nums = max_speed;
				if(count_steps / (target_steps - Mfour.ACC_steps))             ///////
				{	 
				  Mfour.RUN_steps = count_steps - Mfour.ACC_steps;
					Mfour.DEC_nums = max_speed;
				  Mfour.MOTOR_state = STATE_DEC;
				}
			}break;
			case STATE_DEC:
			{
			  count_steps ++;
				last_decnums = Mfour.DEC_nums ;
				Mfour.DEC_nums = last_decnums + (((2*last_decnums) + rest)/(4 * (uint32_t)(target_steps - count_steps) - 1));//计算新(下)一步脉冲周期(时间间隔)
				rest = ((2 * last_decnums)+rest)%(4 * (uint32_t)(target_steps - count_steps) - 1);// 计算余数，下次计算补上余数，减少误差
				Step_nums = Mfour.DEC_nums;
				if(count_steps/target_steps)
				{
					rest = 0;
				  Mfour.MOTOR_state = STATE_STOP;
					Mfour.DEC_steps = count_steps - Mfour.RUN_steps - Mfour.ACC_steps;
				}
			}break;
			case STATE_STOP:
			{
				count_steps = 0;
				HAL_TIM_OC_Stop_IT(&htimx_STEPMOTOR_3,STEPMOTOR_3_TIM_CHANNEL_x);
				Mfour.MOTOR_state = STATE_NONE;
			}break;
		}
		STEPMOTOR_3_TIMx -> STEPMOTOR_3_CCRx = Step_nums;
	}
}
/*
 * 四个通道，任意一个达到比较值进入中断，只处理该通道
 *
*/
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	  switch(MOTOR_CHOOSE)
		{
			case MOTOR_1:{
					StepMotorRun_1(Mone_max_speed,Mone_target_steps);
					STEPMOTOR_1_TIMx -> CNT = 0;
					__HAL_TIM_CLEAR_IT(&htimx_STEPMOTOR_1,STEPMOTOR_1_TIM_IT_CCx);
			}break ;
			case MOTOR_2:{
					StepMotorRun_2(Mtwo_max_speed,Mtwo_target_steps);
					STEPMOTOR_2_TIMx -> CNT = 0;
					__HAL_TIM_CLEAR_IT(&htimx_STEPMOTOR_2,STEPMOTOR_2_TIM_IT_CCx);
			}break ;
			case MOTOR_3:{
					StepMotorRun_3(Mthree_max_speed,Mthree_target_steps);
					STEPMOTOR_3_TIMx -> CNT = 0;
					__HAL_TIM_CLEAR_IT(&htimx_STEPMOTOR_3,STEPMOTOR_3_TIM_IT_CCx);
			}break ;
			case MOTOR_4:{
					StepMotorRun_4(Mfour_max_speed,Mfour_target_steps);
					STEPMOTOR_1_TIMx -> CNT = 0;
					__HAL_TIM_CLEAR_IT(&htimx_STEPMOTOR_1,STEPMOTOR_1_TIM_IT_CCx);
			}break ;
		}
}
/**电机初状态  
     **motor_choose :电机选择 MOTOR_1 MOTOR_2 MOTOR_3 MOTOR_4 
      *start_NUMS_1: 初始计数值 0 - 0xffff
*/ 
void StepMotor_Init(uint8_t motor_choose,uint16_t start_NUMS)
{
	  MOTOR_CHOOSE = motor_choose;
	  switch(MOTOR_CHOOSE)
		{
			case MOTOR_1:{
				HAL_TIM_OC_Start_IT(&htimx_STEPMOTOR_1,STEPMOTOR_1_TIM_CHANNEL_x);
				Mone.ACC_nums = start_NUMS;
				Mone.MOTOR_state = STATE_ACC;
			}break ;
			case MOTOR_2:{
				HAL_TIM_OC_Start_IT(&htimx_STEPMOTOR_2,STEPMOTOR_2_TIM_CHANNEL_x);
				Mtwo.ACC_nums = start_NUMS;
				Mtwo.MOTOR_state = STATE_ACC;
			}break ;
			case MOTOR_3:{
				HAL_TIM_OC_Start_IT(&htimx_STEPMOTOR_3,STEPMOTOR_3_TIM_CHANNEL_x);
				Mthree.ACC_nums = start_NUMS;
				Mthree.MOTOR_state = STATE_ACC;
			}break ;
			case MOTOR_4:{
				HAL_TIM_OC_Start_IT(&htimx_STEPMOTOR_2,STEPMOTOR_2_TIM_CHANNEL_x);
				Mone.ACC_nums = start_NUMS;
				Mone.MOTOR_state = STATE_ACC;
			}break ;
		}
}
