/*
 * xcmd_define.h
 *
 *  Created on: 2022-01-01
 *      Author: XinnZ & Pomin, Landian, HBUT
 *  XinnZ's Blog: https://blog.xinnz.cn/
 *  Pomin's Blog: https://www.pomin.top/
 */

#ifndef XCMD_DEFINE_H_
#define XCMD_DEFINE_H_

#ifdef __cplusplus
extern   "C" {
#endif

#define KEY_CTR_A       "\x01"
#define KEY_CTR_B       "\x02"
#define KEY_CTR_C       "\x03"
#define KEY_CTR_D       "\x04"
#define KEY_CTR_E       "\x05"
#define KEY_CTR_F       "\x06"
#define KEY_CTR_G       "\x07"
#define KEY_CTR_H       "\x08"
#define KEY_CTR_I       "\x09"
#define KEY_TAB         "\x09"
#define KEY_CTR_J       "\x0A"
#define KEY_CTR_K       "\x0B"
#define KEY_CTR_L       "\x0C"
#define KEY_CTR_M       "\x0D"
#define KEY_CTR_N       "\x0E"
#define KEY_CTR_O       "\x0F"
#define KEY_CTR_P       "\x10"
#define KEY_CTR_Q       "\x11"
#define KEY_CTR_R       "\x12"
#define KEY_CTR_S       "\x13"
#define KEY_CTR_T       "\x14"
#define KEY_CTR_U       "\x15"
#define KEY_CTR_V       "\x16"
#define KEY_CTR_W       "\x17"
#define KEY_CTR_X       "\x18"
#define KEY_CTR_Y       "\x19"
#define KEY_CTR_Z       "\x1A"
#define KEY_PAUSE       "\x1A"
#define KEY_ESC         "\x1B"
#define KEY_BACKSPACE   "\x7F"
#define KEY_UP          "\x1B[A"
#define KEY_DW          "\x1B[B"
#define KEY_RIGHT       "\x1B[C"
#define KEY_LEFT        "\x1B[D"
#define KEY_HOME        "\x1B[H"
#define KEY_EMD         "\x1B[F"
#define KEY_CTR_UP      "\x1B[1;5A"
#define KEY_CTR_DW      "\x1B[1;5B"
#define KEY_CTR_RIGHT   "\x1B[1;5C"
#define KEY_CTR_LEFT    "\x1B[1;5D"
#define KEY_INSERT      "\x1B[2~"
#define KEY_DELETE      "\x1B[3~"
#define KEY_PAGE_UP     "\x1B[5~"
#define KEY_PAGE_DOWN   "\x1B[6~"
#define KEY_F1          "\x1BOP"
#define KEY_F2          "\x1BOQ"
#define KEY_F3          "\x1BOR"
#define KEY_F4          "\x1BOS"
#define KEY_F5          "\x1B[15~"
#define KEY_F6          "\x1B[17~"
#define KEY_F7          "\x1B[18~"
#define KEY_F8          "\x1B[19~"
#define KEY_F9          "\x1B[20~"
#define KEY_F10         "\x1B[21~"
#define KEY_F11         "\x1B[23~"
#define KEY_F12         "\x1B[24~"

/* ��������������0x1B��ESC��ֻ������xcmd_print���� */
#define CUU(n)      "\x1B[%dA",n	    /* �������	������� <n> �� */
#define CUD(n)      "\x1B[%dB",n		/* �������	������� <n> �� */
#define CUF(n)      "\x1B[%dC",n		/* �����ǰ	�����ǰ���ң�<n> �� */
#define CUB(n)      "\x1B[%dD",n		/* ������	��������<n> �� */
#define CNL(n)      "\x1B[%dE",n		/* �����һ��	���ӵ�ǰλ������ <n> �� */
#define CPL(n)      "\x1B[%dF",n		/* ��굱ǰ��	���ӵ�ǰλ������ <n> �� */
#define CHA(n)      "\x1B[%dG",n		/* ���Թ��ˮƽ	����ڵ�ǰ����ˮƽ�ƶ����� <n> ��λ�� */
#define VPA(n)      "\x1B[%dd",n		/* ���Դ�ֱ��λ��	����ڵ�ǰ���д�ֱ�ƶ����� <n> ��λ�� */
#define CUP(y,x)    "\x1B[%d;%dH",y,x	/* ���λ��	*����ƶ��������е� <x>; <y> ���꣬���� <x> �� <y> �е��� */
#define HVP(y,x)    "\x1B[%d;%df",y,x	/* ˮƽ��ֱλ��	*����ƶ��������е� <x>; <y> ���꣬���� <x> �� <y> �е��� */

/* ���ɼ��� */
#define CU_START_BL "\x1B[?12h"	        /* ATT160	�ı����������˸	��ʼ�����˸ */
#define CU_STOP_BL  "\x1B[?12l"	        /* ATT160	�ı���������˸	ֹͣ��˸��� */
#define CU_SHOW     "\x1B[?25h"	        /* DECTCEM	�ı��������ģʽ��ʾ	��ʾ��� */
#define CU_HIDE     "\x1B[?25l"	        /* DECTCEM	�ı��������ģʽ����	���ع�� */

/* �ַ����� */
#define ICH(n)      "\x1B[%d@",n	    /* �����ַ�	�ڵ�ǰ���λ�ò��� <n> ���ո���Ὣ���������ı��Ƶ��Ҳࡣ ���������Ļ���ı��ᱻɾ����*/
#define DCH(n)      "\x1B[%dP",n	    /* ɾ���ַ�	ɾ����ǰ���λ�õ� <n> ���ַ���������Ļ�ұ�Ե�Կո��ַ��ƶ���*/
#define ECH(n)      "\x1B[%dX",n	    /* �����ַ�	������ǰ���λ�õ� <n> ���ַ���������ʹ�ÿո��ַ��������ǡ�*/
#define IL(n)       "\x1B[%dL",n	    /* ������	�� <n> �в�����λ�õĻ������� ������ڵ��м����·����н������ƶ���*/
#define DL(n)       "\x1B[%dM",n	    /* ɾ����	�ӻ�������ɾ�� <n> �У��ӹ�����ڵ��п�ʼ��*/

/* ��ӡ������ɫ���� */
#define TX_DEF          "\x1b[0m"
#define TX_BLACK        "\x1b[30m"
#define TX_RED          "\x1b[31m"
#define TX_GREEN        "\x1b[32m"
#define TX_YELLOW       "\x1b[33m"
#define TX_BLUE         "\x1b[34m"
#define TX_WHITE        "\x1b[37m"

/* ��ӡ������ɫ���� */
#define BK_DEF          "\x1b[0m"
#define BK_BLACK        "\x1b[40m"
#define BK_RED          "\x1b[41m"
#define BK_GREEN        "\x1b[42m"
#define BK_YELLOW       "\x1b[43m"
#define BK_BLUE         "\x1b[44m"
#define BK_WHITE        "\x1b[47m"

#ifdef __cplusplus
        }
#endif

#endif /* XCMD_DEFINE_H_ */
