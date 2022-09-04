/*
 * pid.c
 *
 *  Created on: 2022-01-01
 *      Author: XinnZ & Pomin, Landian, HBUT
 *  XinnZ's Blog: https://blog.xinnz.cn/
 *  Pomin's Blog: https://www.pomin.top/
 */

#include "pid.h"

static sint32 PID_Limiter(sint32 amt, sint32 low, sint32 high) {
    return ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)));
}

static float32 PID_Limiter_float32(float32 amt, float32 low, float32 high) {
    return ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)));
}

static void PID_Init(PID_Param_TypeDef* pid_param) {
    pid_param->kP = 0.0f;
    pid_param->kI = 0.0f;
    pid_param->kD = 0.0f;

    pid_param->last_out_d = 0.0f;
    pid_param->integrator = 0.0f;
    pid_param->integral_limit = 0;
    pid_param->last_error = 0;
    pid_param->prev_error = 0;
}

static void PID_Clear(PID_Param_TypeDef* pid_param) {
    pid_param->last_out_d = 0.0f;
    pid_param->integrator = 0.0f;
    pid_param->last_error = 0;
    pid_param->prev_error = 0;
}

static sint32 PID_Position(PID_Param_TypeDef* pid_param, sint32 actual, sint32 set) {
    /* ���㵱ǰ��� */
    sint32 iError = set - actual;

    /* ����ۻ� */
    pid_param->integrator += iError;

    /* ����޷� */
    pid_param->integrator = PID_Limiter_float32(pid_param->integrator,
                                                (float32)(0 - pid_param->integral_limit),
                                                (float32)(0 + pid_param->integral_limit));

    /* ����ȫ΢�� ΢�����ӵ�ͨ�˲��� */
    float out_d = (iError - pid_param->last_error) * 0.8 + pid_param->last_out_d * 0.2;

    /* ʵ����� */
    sint32 Position = (sint32)(pid_param->kP * iError +
                               pid_param->kI * pid_param->integrator +
                               pid_param->kD * out_d);

    /* ���²��� */
    pid_param->last_error = iError;
    pid_param->last_out_d = out_d;

    return Position;
}

static sint32 PID_Increase(PID_Param_TypeDef* pid_param, sint32 actual, sint32 set) {
    /* ���㵱ǰ��� */
    sint32 iError = set - actual;

    /* ʵ����� */
    sint32 Increase = (sint32)(pid_param->kP * (iError - pid_param->last_error) +
                               pid_param->kI * iError +
                               pid_param->kD * (iError - 2 * pid_param->last_error + pid_param->prev_error));

    /* ����ǰ����� */
    pid_param->prev_error = pid_param->last_error;

    /* �����ϴ���� */
    pid_param->last_error = iError;

    return Increase;
}

PID_TypeDef PID =
    {
        .Init = PID_Init,
        .Clear = PID_Clear,
        .Limiter = PID_Limiter,
        .Position = PID_Position,
        .Increase = PID_Increase};
