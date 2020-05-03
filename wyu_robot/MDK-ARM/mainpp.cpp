#include <mainpp.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include "motor.h"
#include "Kinematics.h"
#include "PID.h"
//��ʼ���ĸ����ӵ�ʵ�������ڿ�������

Motor motorA(MOTORA);
Motor motorB(MOTORB);
Motor motorC(MOTORC);
Motor motorD(MOTORD);
//Ϊÿ�����ӽ���һ��PID���㣬���ڵ��������ٶ�
PID pidA(-500, 500, K_P, K_I, K_D);
PID pidB(-500, 500, K_P, K_I, K_D);
PID pidC(-500, 500, K_P, K_I, K_D);
PID pidD(-500, 500, K_P, K_I, K_D);

//��ʼ���˶�ѧ�����������ʵ�ֵ����ٶȺ͸�����ת�ٵ�ת��
Kinematics kinematics(WHEEL_DIAMETER,LR_WHEELS_DISTANCE,FR_WHEELS_DISTANCE);

void command_callback( const geometry_msgs::Twist& cmd_msg);
void motor_run();
void print_debug();


geometry_msgs::Twist raw_vel_msg;
Kinematics::rpm req_rpm; // ��λ��������cmd_vel��Ӧ�ĸ�����ת��

int16_t motorA_pwm;
int16_t motorB_pwm;
int16_t motorC_pwm;
int16_t motorD_pwm;

ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", command_callback);	//������λ�������Ŀ���ָ�ָ��Ϊ�ٶ�
ros::Publisher raw_vel_pub("raw_vel", &raw_vel_msg);	//����λ���������̵�ʵʱ�ٶȣ�������λ��������̼�

//��ȡ����λ��ָ���ͨ��ָ���ٶȼ����������ת��
void command_callback( const geometry_msgs::Twist& cmd_msg)
{
	req_rpm = kinematics.Velocities_to_rpm(cmd_msg.linear.x,cmd_msg.linear.y,cmd_msg.angular.z);
//	nh.loginfo("GET CMD !!!");
}

//����λ������ʵʱ�ٶȵľ���ʵ��
void publish_linear_velocity()
{
	Kinematics::velocities vel;
	vel = kinematics.rpm_to_Velocities(motorA.rpm,motorB.rpm,motorC.rpm,motorD.rpm);
  
  raw_vel_msg.linear.x = vel.linear_x;
  raw_vel_msg.linear.y = vel.linear_y;
  raw_vel_msg.angular.z = vel.angular_z;
	
  raw_vel_pub.publish(&raw_vel_msg);
}

void motor_run()
{	

	motorA_pwm += pidA.compute(req_rpm.motorA_rpm,motorA.rpm);
	motorB_pwm += pidB.compute(req_rpm.motorB_rpm,motorB.rpm);
	motorC_pwm += pidC.compute(req_rpm.motorC_rpm,motorC.rpm);
	motorD_pwm += pidD.compute(req_rpm.motorD_rpm,motorD.rpm);

	motorA.spin(motorA_pwm);
	motorB.spin(motorB_pwm);
	motorC.spin(motorC_pwm);
	motorD.spin(motorD_pwm);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == htim6.Instance)
    {
			motorA.updateSpeed();
			motorB.updateSpeed();
			motorC.updateSpeed();
			motorD.updateSpeed();
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    }
}

void setup(void)
{
  nh.initNode();
	nh.advertise(raw_vel_pub);
	nh.subscribe(cmd_sub);
	
	while (!nh.connected()){
    nh.spinOnce();
	}
	nh.loginfo("WYU_ROBOT CONNECTED SUCCESS !!!");
}

void loop(void)
{  
	HAL_Delay(20);
	motor_run();
	publish_linear_velocity();
//	nh.loginfo("AGIN !!!");
	nh.spinOnce();
}

