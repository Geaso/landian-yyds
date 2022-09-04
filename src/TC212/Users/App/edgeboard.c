/*
 * edgeboard.c
 *
 *  Created on: 2022-04-01
 *      Author: XinnZ & Pomin, Landian, HBUT
 *  XinnZ's Blog: https://blog.xinnz.cn/
 *  Pomin's Blog: https://www.pomin.top/
 */

#include "edgeboard.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "icm20602.h"
#include "pid.h"
#include "run.h"
#include "uart.h"

/**
 * @brief  �������� Edgeboard ��λ��������
 * @param  byte:
 */
static void ReceTask(char byte) {
#define FRAME_LENGTH_RECE 10

    static uint8 data[FRAME_LENGTH_RECE] = {0};
    static uint8 counter = 0;

    uint16 check = 0;

    data[counter++] = (uint8)byte;

    if (0xF1 != data[0]) {
        counter = 0;
        return;
    }
    if (0xE1 != data[1] && counter >= 2) {
        counter = 0;
        return;
    }
    if ((FRAME_LENGTH_RECE - 1) < counter) {
        if (0xF2 == data[(FRAME_LENGTH_RECE - 1)]) {
            check = (uint16)(((uint16)data[FRAME_LENGTH_RECE - 3] << 8) | data[FRAME_LENGTH_RECE - 2]);
            if (check == CRC_CHECK(&data[2], 5)) {
                Run_Params.TargetSpeed = (sint16)(((sint16)data[2] << 8) | data[3]);
                Run_Params.TargetAngle = (sint16)(((sint16)data[4] << 8) | data[5]);

                /* ����λ�������� PID ��� */
                Run_Params.CtServoPwm = (sint32)Run_Params.TargetAngle + (sint32)Servo.median;
                Run_Params.CtServoPwm = PID.Limiter(Run_Params.CtServoPwm, SERVO_MIN, SERVO_MAX);
                Servo.Duty(Run_Params.CtServoPwm);

                Run_Params.Edge_Tran = true;  // ���յ�����
                Run_Params.Edge_HBP = 0;      // ����������

                Run_Params.Element = (uint8)data[6];  // �Ƿ�ʶ��Ԫ��
                if (Run_Params.Element != 0) {
                    Run_Params.Buzzer = 2;
                }
            }
        }

        counter = 0;
    }
}

/**
 * @brief  �������� Edgeboard ��λ��������
 */
static void Rece(void) {
    char i = 0;
    short count = 0;
    short readCount = 64;
    char receiveDatas[64];

    UART_EdgeBoard.Receive(receiveDatas, &readCount);

    count += readCount;
    for (i = 0; i < count; i++) {
        ReceTask(receiveDatas[i]);
    }
}

#define BYTE0(dwTemp) (*((char *)(&dwTemp) + 0))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

/**
 * @brief  �������ݵ� Edgeboard ��λ��
 */
static void Tran() {
    uint8 data[12] = {0};
    sint16 length = 0;
    sint16 _temp1 = 0;
    sint32 _temp2 = 0;

    data[length++] = 0x32;  // ������
    data[length++] = 0xf2;  // ͷ���� 1
    data[length++] = 0xe2;  // ͷ���� 2

    // ������
    // ICM.GetPhysicalUnit();
    // _temp1 = (sint16)(ICM.Gyro_PU.z * 100);

    // ��ʵ�ٶ�
    _temp1 = (sint16)(Run_Params.CtSpeed * 100);

    data[length++] = BYTE1(_temp1);
    data[length++] = BYTE0(_temp1);

    // ��ʵ·��
    _temp2 = (sint32)(Run_Params.CtRoute);
    data[length++] = BYTE3(_temp2);
    data[length++] = BYTE2(_temp2);
    data[length++] = BYTE1(_temp2);
    data[length++] = BYTE0(_temp2);

    // У��
    uint16 CRC16 = CRC_CHECK(&data[3], 6);
    data[length++] = (uint8_t)(CRC16 >> 8);
    data[length++] = (uint8_t)(CRC16 & 0xff);
    data[length++] = 0xe3;  // β����

    UART_EdgeBoard.Transmit((const char *)data, &length);
}

Edge_TypeDef Edge =
    {
        .Rece = Rece,
        .Tran = Tran};
