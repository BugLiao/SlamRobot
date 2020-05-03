#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"

#define PI      3.1415926

//�ٶ�
#define MAX_RPM         366 //motor's maximum RPM

//PID����
#define K_P    0.2 // P constant
#define K_I    0.2 // I constant
#define K_D    0.2 // D constant

//����
#define WHEEL_DIAMETER  0.0762 //����ֱ��
#define LR_WHEELS_DISTANCE  0.28 //�������ּ��
#define FR_WHEELS_DISTANCE  0.23 //ǰ�����ּ��
#define COUNTS_PER_REV  19100  //���ٱ�20����Ȧ955

/** Motor Config **/ 
#define MOTORn						4

typedef enum {
	MOTORA = 0, //A��  ǰ�� 
	MOTORB = 1, //B��  ǰ�� 
	MOTORC = 2, //C��  ���� 
	MOTORD = 3	//D��  ���� 
}Motor_TypeDef; 


#endif // _CONFIG_H_