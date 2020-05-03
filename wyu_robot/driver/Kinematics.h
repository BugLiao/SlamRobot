#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "config.h"

class Kinematics
{
  public:
    struct rpm {
      double motorA_rpm;	//A��ת��
      double motorB_rpm;	//B��ת��
			double motorC_rpm;	//C��ת��
			double motorD_rpm;	//D��ת��		
    };
    struct velocities {
      float linear_x;
      float linear_y;
      float angular_z;
    };
    Kinematics(float wheel_diameter, float base_width,float _base_long);
    Kinematics::rpm Velocities_to_rpm(float liner_vel_x,float liner_vel_y,float angular_rad_z);//�����ٶ�ת���ɸ�������ת��
		Kinematics::velocities rpm_to_Velocities(double motor_a_rpm, double motor_b_rpm, double motor_c_rpm, double motor_d_rpm);//�Ӹ�����ת����������̵����ٶ�
//		int rpm_to_PWM(int rpm);
  private:
    float linear_vel_x_min;	//X�����ٶ�
    float linear_vel_y_min;	//Y�����ٶȣ��ò�����ʱY���ٶȺ�Ϊ�� ���������Ϊ�����ľ��׼���ģ�
    float angular_rad_z_min;	//Z����ٶ�
    float circumference;	//�����ܳ�
    float tangential_vel;	//���������ٶ�
    float wheel_diameter;	//����ֱ��
    float base_width;	//�������������ӵļ��
		float base_long;  //����ǰ�������ӵļ��
};

#endif
