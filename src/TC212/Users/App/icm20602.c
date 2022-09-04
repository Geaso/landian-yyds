/*
 * icm20602.c
 *
 *  Created on: 2022-01-01
 *      Author: XinnZ & Pomin, Landian, HBUT
 *  XinnZ's Blog: https://blog.xinnz.cn/
 *  Pomin's Blog: https://www.pomin.top/
 */

#include "icm20602.h"

#include "gpio.h"
#include "qspi.h"

QSPI_Moudle QSPI_ICM;
static uint16 ICM_InitOK;

static void icm_spi_w_reg_byte(uint8 cmd, uint8 val) {
    uint8 dat[2];

    dat[0] = cmd | ICM20602_SPI_W;
    dat[1] = val;

    QSPI.MOSI(&QSPI_ICM, dat, dat, 2, 1);
}

static void icm_spi_r_reg_byte(uint8 cmd, uint8 *val) {
    uint8 dat[2];

    dat[0] = cmd | ICM20602_SPI_R;
    dat[1] = *val;

    QSPI.MOSI(&QSPI_ICM, dat, dat, 2, 1);

    *val = dat[1];
}

static void icm_spi_r_reg_bytes(uint8 *val, uint8 num) {
    QSPI.MOSI(&QSPI_ICM, val, val, num, 1);
}

static void icm20602_self_check(void) {
    uint8 dat = 0;
    uint8 time = 0;

    delay_ms(10);
    icm_spi_r_reg_byte(ICM20602_WHO_AM_I, &dat);

    while (0x12 != dat)  // ICM20602 ID
    {
        GPIO.Toggle(IFXCFG_PORT_LED2);
        GPIO.Toggle(IFXCFG_PORT_BUZZ);

        if (time++ > 60) {
            GPIO.Low(IFXCFG_PORT_LED2);
            GPIO.Low(IFXCFG_PORT_BUZZ);
            break;
        }

        delay_ms(50);
        icm_spi_r_reg_byte(ICM20602_WHO_AM_I, &dat);
        // ��������ԭ�������¼���
        // 1 ICM20602���ˣ�������µ������ĸ��ʼ���
        // 2 ���ߴ������û�нӺ�
        // 3 ��������Ҫ����������裬������3.3V
    }
    if (time < 60) {
        ICM_InitOK = true;
    }
}

static void icm20602_init(void) {
    uint8 val = 0x0;
    uint8 time = 0;

    delay_ms(10);

    QSPI.Init(SPI_NUM, &QSPI_ICM, 3, 10 * 1000 * 1000,
              &SPI_SCK_PIN, &SPI_MOSI_PIN, &SPI_MISO_PIN, &SPI_CS_PIN);

    icm20602_self_check();                          // ���
    icm_spi_w_reg_byte(ICM20602_PWR_MGMT_1, 0x80);  // ��λ
    delay_ms(2);

    do  // �ȴ���λ�ɹ�
    {
        icm_spi_r_reg_byte(ICM20602_PWR_MGMT_1, &val);
        delay_ms(10);
        if (time++ > 100)
            break;
    } while (0x41 != val);

    icm_spi_w_reg_byte(ICM20602_PWR_MGMT_1, 0x01);      // ʱ������
    icm_spi_w_reg_byte(ICM20602_PWR_MGMT_2, 0x00);      // ���������Ǻͼ��ٶȼ�
    icm_spi_w_reg_byte(ICM20602_CONFIG, 0x02);          // 92HZ 1KHZ
    icm_spi_w_reg_byte(ICM20602_SMPLRT_DIV, 0x07);      // �������� SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    icm_spi_w_reg_byte(ICM20602_GYRO_CONFIG, 0x18);     // ��2000 dps
    icm_spi_w_reg_byte(ICM20602_ACCEL_CONFIG, 0x10);    // ��8g
    icm_spi_w_reg_byte(ICM20602_ACCEL_CONFIG_2, 0x03);  // Average 4 samples   44.8HZ   //0x23 Average 16 samples

    // ICM20602_GYRO_CONFIG �Ĵ���
    // ����Ϊ:0x00 ����������Ϊ:��250 dps     ��ȡ�������������ݳ���131           ����ת��Ϊ������λ�����ݣ���λΪ����/s
    // ����Ϊ:0x08 ����������Ϊ:��500 dps     ��ȡ�������������ݳ���65.5          ����ת��Ϊ������λ�����ݣ���λΪ����/s
    // ����Ϊ:0x10 ����������Ϊ:��1000dps     ��ȡ�������������ݳ���32.8          ����ת��Ϊ������λ�����ݣ���λΪ����/s
    // ����Ϊ:0x18 ����������Ϊ:��2000dps     ��ȡ�������������ݳ���16.4          ����ת��Ϊ������λ�����ݣ���λΪ����/s

    // ICM20602_ACCEL_CONFIG �Ĵ���
    // ����Ϊ:0x00 ���ٶȼ�����Ϊ:��2g          ��ȡ���ļ��ٶȼ����� ����16384      ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
    // ����Ϊ:0x08 ���ٶȼ�����Ϊ:��4g          ��ȡ���ļ��ٶȼ����� ����8192       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
    // ����Ϊ:0x10 ���ٶȼ�����Ϊ:��8g          ��ȡ���ļ��ٶȼ����� ����4096       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
    // ����Ϊ:0x18 ���ٶȼ�����Ϊ:��16g         ��ȡ���ļ��ٶȼ����� ����2048       ����ת��Ϊ������λ�����ݣ���λ��g(m/s^2)
}

static Axis3d get_icm20602_accdata(void) {
    Axis3d datas;

    struct
    {
        uint8 reg;
        uint8 dat[6];
    } buf;

    if (!ICM_InitOK)
        return (Axis3d){
            0,
            0,
            0,
        };

    buf.reg = ICM20602_ACCEL_XOUT_H | ICM20602_SPI_R;

    icm_spi_r_reg_bytes(&buf.reg, 7);

    datas.x = (sint16)((((uint16)buf.dat[0] << 8) | buf.dat[1]));
    datas.y = (sint16)((((uint16)buf.dat[2] << 8) | buf.dat[3]));
    datas.z = (sint16)((((uint16)buf.dat[4] << 8) | buf.dat[5]));

    return datas;
}

static Axis3d get_icm20602_gyro(void) {
    Axis3d datas;

    struct
    {
        uint8 reg;
        uint8 dat[6];
    } buf;

    if (!ICM_InitOK)
        return (Axis3d){
            0,
            0,
            0,
        };

    buf.reg = ICM20602_GYRO_XOUT_H | ICM20602_SPI_R;

    icm_spi_r_reg_bytes(&buf.reg, 7);

    datas.x = (sint16)((((uint16)buf.dat[0] << 8) | buf.dat[1]));
    datas.y = (sint16)((((uint16)buf.dat[2] << 8) | buf.dat[3]));
    datas.z = (sint16)((((uint16)buf.dat[4] << 8) | buf.dat[5]));

    return datas;
}

static float fffff(float com) {
    static float iLastData = 0.0f;
    float iData;

    iData = (com * 0.35f) + ((1 - 0.35f) * iLastData);
    iLastData = iData;

    return iData;
}

static void get_physical_unit(void) {
    /*
    ICM.Accel = ICM.GetAccel();
    ICM.Accel_PU.x = (float)ICM.Accel.x / 4096.0f;
    ICM.Accel_PU.y = (float)ICM.Accel.y / 4096.0f;
    ICM.Accel_PU.z = (float)ICM.Accel.z / 4096.0f;
     */

    ICM.Gyro = ICM.GetGyro();
    // ICM.Gyro_PU.x = (float)ICM.Gyro.x * M_PI / 180 / 16.4f;
    // ICM.Gyro_PU.y = (float)ICM.Gyro.y * M_PI / 180 / 16.4f;
    ICM.Gyro_PU.z = fffff(((float)ICM.Gyro.z * M_PI / 180.0f / 16.4f));
}

ICM_TypeDef ICM =
    {
        .Init = icm20602_init,

        .GetAccel = get_icm20602_accdata,
        .GetGyro = get_icm20602_gyro,

        .GetPhysicalUnit = get_physical_unit,

        .Accel = {0},
        .Gyro = {0},

        .Accel_PU = {0},
        .Gyro_PU = {0}};
