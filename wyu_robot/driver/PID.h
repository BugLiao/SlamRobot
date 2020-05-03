#ifndef PID_H
#define PID_H

#include "config.h"

//����ת����ֵ
#define constrain(amt,low,high) \
	((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

class PID
{
  public:
    PID(float min_val, float max_val, float kp, float ki, float kd);
    int16_t compute(double setpoint, double measured_value);	//�����PWM��
//    void updateConstants(float kp, float ki, float kd);

  private:
    float min_val_;
    float max_val_;

		float kp_;
    float ki_;
    float kd_;
	
    double integral_;	//���Ļ���ֵ
    double derivative_;	//�������Ĳ�ֵ������̫�������������������壩
    double prev_error_;	//��һ�����
};

#endif
