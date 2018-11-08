#include "motor_crl.h"


//typedef struct
//{
//  uint16_t speed[SPEED_levels];              // 速度级别
//	uint16_t steps[SPEED_levels];              // 每个速度级别走的步数
//}M1,M2,M3,M4;	
//M1 M1_SPEED;
//M2 M2_SPEED;
//M3 M3_SPEED;
//M4 M4_SPEED;

__IO uint16_t M1_speed[SPEED_levels] = {100,50,30,0,0};
__IO uint16_t M1_steps[SPEED_levels] = {200,200,200,200,200};
__IO uint16_t M2_speed[SPEED_levels] = {100,50,30,0,0};
__IO uint16_t M2_steps[SPEED_levels] = {200,200,200,200,200};
__IO uint16_t M3_speed[SPEED_levels] = {100,50,30,0,0};
__IO uint16_t M3_steps[SPEED_levels] = {200,200,200,200,200};
__IO uint16_t M4_speed[SPEED_levels] = {100,50,30,0,0};
__IO uint16_t M4_steps[SPEED_levels] = {200,200,200,200,200};



///*
//  说明： 比如  SPEED_levels = 5;但
//*/
//void SPEED_INIT(uint16_t motor,uint16_t *speed,uint16_t *steps)
//{
//  switch(motor)
//	{
//	  case 1:
//			for(uint8_t i = 0;i < SPEED_levels;i++){
//			  M1_SPEED.speed[i] = speed[i];
//				M1_SPEED.steps[i] = steps[i];
//			}
//			break;
//		case 2:
//			for(uint8_t i = 0;i < SPEED_levels;i++){
//			  M2_SPEED.speed[i] = speed[i];
//				M2_SPEED.steps[i] = steps[i];
//			}
//			break;
//		case 3:
//			for(uint8_t i = 0;i < SPEED_levels;i++){
//			  M3_SPEED.speed[i] = speed[i];
//				M3_SPEED.steps[i] = steps[i];
//			}
//			break;
//		case 4:
//			for(uint8_t i = 0;i < SPEED_levels;i++){
//			  M4_SPEED.speed[i] = speed[i];
//				M4_SPEED.steps[i] = steps[i];
//			}
//			break;
//	}
//}

/*speed
             ------ 
           --      -- 
        ---          ---  
*/
void Motor_3_on(void)
{
  EN_MOTOR3_on;
	for(uint16_t i = M3_steps[1];i > 0;i --){
		CLK_3_on;
//		osDelay(M3_speed[1]);
		CLK_3_off;
//		osDelay(M3_speed[1]);
	}
	for(uint16_t i = M3_steps[2];i > 0;i --){
		CLK_3_on
//		osDelay(M3_speed[2]);
		CLK_3_off
//		osDelay(M3_speed[2]);
	}
 	for(uint16_t i = M3_steps[3];i > 0;i --){
		CLK_3_on
//		osDelay(M3_speed[3]);
		CLK_3_off
//		osDelay(M3_speed[3]);
	}
	for(uint16_t i = M3_steps[2];i > 0;i --){
		CLK_3_on
//		osDelay(M3_speed[2]);
		CLK_3_on
//		osDelay(M3_speed[2]);
	}
	for(uint16_t i = M3_steps[1];i > 0;i --){
		CLK_3_on
//		osDelay(M3_speed[1]);
		CLK_3_on
//		osDelay(M3_speed[1]);
	}
}