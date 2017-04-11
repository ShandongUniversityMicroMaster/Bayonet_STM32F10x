#ifndef __DMP_H
#define __DMP_H
#include "Bayonet_UART.h"




  
// MotionApps 2.0 DMP implementation,
#define MPU6050_INCLUDE_DMP_MOTIONAPPS20

#define MPU6050_DMP_CODE_SIZE       1929    // dmpMemory[]
#define MPU6050_DMP_CONFIG_SIZE     192     // dmpConfig[]
#define MPU6050_DMP_UPDATES_SIZE    47      // dmpUpdates[]


/* ================================================================================================ *
 | Default MotionApps v2.0 42-byte FIFO packet structure:                                           |
 |                                                                                                  |
 | [QUAT W][      ][QUAT X][      ][QUAT Y][      ][QUAT Z][      ][GYRO X][      ][GYRO Y][      ] |
 |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  |
 |                                                                                                  |
 | [GYRO Z][      ][ACC X ][      ][ACC Y ][      ][ACC Z ][      ][      ]                         |
 |  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41                          |
 * ================================================================================================ */

struct DMP_FIFO_map{
int16_t qw;		 // DMP�������Ԫ��ֵ
int16_t null0;
int16_t qx;
int16_t null1;
int16_t qy;
int16_t null2;
int16_t qz;
int16_t null3;
int16_t GYROx;	// ������ X�� ���ٶ� ADCֵ
int16_t null4;
int16_t GYROy;  // ������ Y�� ���ٶ� ADCֵ
int16_t null5;
int16_t GYROz;	// ������ Z�� ���ٶ� ADCֵ
int16_t null6;
int16_t ACCx;   // ���ٶȼ� X�� ADCֵ
int16_t null7;
int16_t ACCy;	// ���ٶȼ� Y�� ADCֵ
int16_t null8;
int16_t ACCz;	// ���ٶȼ� Z�� ADCֵ
int16_t null9;
int16_t null10;

//���������� DMP_Routing ���¡�
float  dmp_pitch;  //DMP������ĸ�����	��λ����
float  dmp_roll;    //DMP��ת��		   ��λ����
float  dmp_yaw;		//DMP ����ǣ�����û�д����Ʋ��룬����ǻ�Ʈ  ��λ����
float  dmp_gyrox;	// ������ X�� ���ٶ�   ��λ����ÿ��
float  dmp_gyroy;   // ������ Y�� ���ٶ�   ��λ����ÿ��
float  dmp_gyroz;   // ������ Z�� ���ٶ�   ��λ����ÿ��
float  dmp_accx;	// ���ٶȼ� X��   ��λ��g  [9.8 m/S^2]
float  dmp_accy;	// ���ٶȼ� Y��   ��λ��g  [9.8 m/S^2]
float  dmp_accz;	// ���ٶȼ� Z��   ��λ��g  [9.8 m/S^2]
};

//------------------------------------------------------------------
extern struct DMP_FIFO_map DMP_DATA;  //��������				   -
//��ϣ����ȡ �����ǵ�X�����ʱ�������� DMP_DATA.dmp_gyrox		   -
//��ϣ����ȡ �����ǵ�Y�����ʱ�������� DMP_DATA.dmp_gyroy		   -
//��ϣ����ȡ ���ٶȼƵ�X�����ʱ�������� DMP_DATA.dmp_accx		   -
//���帩���ǵ� ������ DMP_DATA.dmp_pitch						   -
//�������� �ο� struct DMP_FIFO_map �ṹ��Ķ���				   -
//��д�ߣ�lisn3188												   -
//��ַ��www.chiplab7.net										   -
//����E-mail��lisn3188@163.com									   -
//------------------------------------------------------------------


//DMP API�ӳ���
uint8_t MPU6050_DMP_Initialize(void); //DMP��ʼ��
void DMP_Routing(void);	 //DMP �̣߳���Ҫ���ڶ�ȡ�ʹ���DMP�Ľ��   [��Ҫ��ʱ����]
void DMP_getYawPitchRoll(void);  //��ȡ�������̬��

#endif

//------------------End of File----------------------------
