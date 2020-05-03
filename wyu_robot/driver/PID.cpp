#include "PID.h"

PID::PID(float min_val, float max_val, float kp, float ki, float kd)
{
  min_val_ = min_val;
  max_val_ = max_val;
  kp_ = kp;
  ki_ = ki;
  kd_ = kd;
}

//����PID�㷨������PWM���Ӷ����Ƶ��ת��
int16_t PID::compute(double setpoint, double measured_value)
{
  double error;	//ʵ��ֵ��Ŀ��ֵ�Ĳ��
  double pwm;

  //setpoint is constrained between min and max to prevent pid from having too much error
  error = setpoint - measured_value;
  integral_ += error;	//���Ļ���
  derivative_ = error - prev_error_;	//�������������������PID��΢������

  if(setpoint == 0 && error == 0){
    integral_ = 0;
  }

  pwm = (kp_ * error) + (ki_ * integral_) + (kd_ * derivative_);	//PID������
  prev_error_ = error;

  return (int16_t)constrain(pwm, min_val_, max_val_);	//�����������PWMռ�ձ�ֵ������Ԥ�����õ���ֵ���Ƚϣ����ó�����ֵ��Χ

}

