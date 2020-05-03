#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "config.h"

#define abs(a,b) \
((a > b) ? (a-b) : (b-a))

class Motor {
	public:
		double rpm;

		Motor(Motor_TypeDef _motor);
		void spin(int16_t pwm);	//�������
		void updateSpeed();	//ͨ���������������ǰ�ٶ�
		uint32_t get_last_tick();	//��ȡ��������һʱ�̵Ŀ̶�ֵ
	
	private:
		Motor_TypeDef motor;	//���ID

		int32_t tick_last;	//��������һʱ�̶̿�ֵ
		int32_t last_milli_time;	//��һ�ζ�ȡ��������ֵ��ʱ��
		double delta_mins_time;	//���α�������ȡʱ����
		
};

#endif //_MOTOR_H_