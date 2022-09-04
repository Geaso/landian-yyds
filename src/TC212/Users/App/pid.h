/*
 * pid.h
 *
 *  Created on: 2022-01-01
 *      Author: XinnZ & Pomin, Landian, HBUT
 *  XinnZ's Blog: https://blog.xinnz.cn/
 *  Pomin's Blog: https://www.pomin.top/
 */

#ifndef USERS_APP_PID_H_
#define USERS_APP_PID_H_

#include "Ifx_Types.h"


typedef struct
{
    float32 kP;  // P
    float32 kI;  // I
    float32 kD;  // D

    float32 last_out_d;   	// �ϴ�΢�ֽ��
    float32 integrator;   	// ������ ����ۼ�
    sint32 integral_limit;	// �����޷�
    sint32 last_error;    	// �ϴ����
    sint32 prev_error;  	// ���ϴ����
} PID_Param_TypeDef;


typedef struct
{
    void (*Init)(void);
    void (*Save)(void);
    void (*Read)(void);

    PID_Param_TypeDef Angle;
    PID_Param_TypeDef Omega;
    PID_Param_TypeDef Speed;
} PID_Params_List;

extern PID_Params_List PID_Params;


typedef struct
{
    void (*Init)(PID_Param_TypeDef* pid_param);
    void (*Clear)(PID_Param_TypeDef* pid_param);
    sint32 (*Limiter)(sint32 amt, sint32 low, sint32 high);
    sint32 (*Position)(PID_Param_TypeDef* pid_param, sint32 actual, sint32 set);
    sint32 (*Increase)(PID_Param_TypeDef* pid_param, sint32 actual, sint32 set);
} PID_TypeDef;

extern PID_TypeDef PID;


#endif /* USERS_APP_PID_H_ */
