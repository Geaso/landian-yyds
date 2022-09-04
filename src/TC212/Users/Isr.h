/*
 * Isr.h
 *
 *  Created on: 2022-1-1
 *      Author: XinnZ & Pomin, Landian, HBUT
 *  XinnZ's Blog: https://blog.xinnz.cn/
 *  Pomin's Blog: https://www.pomin.top/
 */

#ifndef USERS_ISR_H_
#define USERS_ISR_H_

// ISR_PRIORITY:  0 ���ȼ���ʾ�������ж�, 255 Ϊ������ȼ�
// INT_SERVICE:   �궨������ж���˭����, Ҳ��Ϊ�����ṩ��(�жϱ���������), �����÷�Χ IfxSrc_Tos_cpu0, IfxSrc_Tos_dma ��������Ϊ����ֵ
// INT_SERVICE:   IfxSrc_Tos_dma �Ļ�, ISR_PRIORITY �Ŀ����÷�Χ���� 0-16


#define CCU6_0_CH0_INT_SERVICE IfxSrc_Tos_cpu0
#define CCU6_0_CH0_ISR_PRIORITY                 10

#define CCU6_0_CH1_INT_SERVICE IfxSrc_Tos_cpu0
#define CCU6_0_CH1_ISR_PRIORITY                 11

#define CCU6_1_CH0_INT_SERVICE IfxSrc_Tos_cpu0
#define CCU6_1_CH0_ISR_PRIORITY                 12

#define CCU6_1_CH1_INT_SERVICE IfxSrc_Tos_cpu0
#define CCU6_1_CH1_ISR_PRIORITY                 13


#define UART_Console_INT_SERVICE IfxSrc_Tos_cpu0
#define UART_Console_ISR_PRIORITY_TX            7                           /* Priority for interrupt ISR Transmit  */
#define UART_Console_ISR_PRIORITY_RX            5                           /* Priority for interrupt ISR Receive   */
#define UART_Console_ISR_PRIORITY_ER            41                          /* Priority for interrupt ISR Errors    */
#define UART_Console_BAUDRATE                   57600                       /* Define the UART baud rate            */
#define UART_Console_TX_Pin                     IfxAsclin0_TX_P14_0_OUT     /* Select the pin for TX connected to the USB port */
#define UART_Console_RX_Pin                     IfxAsclin0_RXA_P14_1_IN     /* Select the pin for RX connected to the USB port */
#define UART_Console_MODULE                     MODULE_ASCLIN0

#define UART_EdgeBoard_INT_SERVICE IfxSrc_Tos_cpu0
#define UART_EdgeBoard_ISR_PRIORITY_TX          6                           /* Priority for interrupt ISR Transmit  */
#define UART_EdgeBoard_ISR_PRIORITY_RX          4                           /* Priority for interrupt ISR Receive   */
#define UART_EdgeBoard_ISR_PRIORITY_ER          40                          /* Priority for interrupt ISR Errors    */
#define UART_EdgeBoard_BAUDRATE                 921600                      /* Define the UART baud rate            */
#define UART_EdgeBoard_TX_Pin                   IfxAsclin1_TX_P02_2_OUT     /* Select the pin for TX connected to the USB port */
#define UART_EdgeBoard_RX_Pin                   IfxAsclin1_RXG_P02_3_IN     /* Select the pin for RX connected to the USB port */
#define UART_EdgeBoard_MODULE                   MODULE_ASCLIN1


#endif /* USERS_ISR_H_ */
