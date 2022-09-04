/*
 * xcmd_config.h
 *
 *  Created on: 2022-01-01
 *      Author: XinnZ & Pomin, Landian, HBUT
 *  XinnZ's Blog: https://blog.xinnz.cn/
 *  Pomin's Blog: https://www.pomin.top/
 */

#ifndef XCMD_CONFIG_H_
#define XCMD_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XCMD_LINE_MAX_LENGTH
#define XCMD_LINE_MAX_LENGTH 			(64)			/* ������֧�ֵ�����ַ��� */
#endif

#ifndef XCMD_PRINT_BUF_MAX_LENGTH
#define XCMD_PRINT_BUF_MAX_LENGTH	 	(256) 			/* xcmd_print ���� */
#endif

#if XCMD_PRINT_BUF_MAX_LENGTH < (XCMD_LINE_MAX_LENGTH + 32)
#undef XCMD_PRINT_BUF_MAX_LENGTH
#define XCMD_PRINT_BUF_MAX_LENGTH 		(XCMD_LINE_MAX_LENGTH + 32)			/* xcmd_print ���� */
#endif

#ifndef XCMD_HISTORY_MAX_NUM
#define XCMD_HISTORY_MAX_NUM 			(5) 			/* ֧�ֵ���ʷ��¼���� */
#endif

#ifndef XCMD_PARAM_MAX_NUM
#define XCMD_PARAM_MAX_NUM 				(6) 			/* ֧������Ĳ������� */
#endif

#ifndef XCMD_DEFAULT_PROMPT
#define XCMD_DEFAULT_PROMPT 			(">>> ")
#define XCMD_DEFAULT_PROMPT_LEN 		(4)
#endif
/*
#ifndef XCMD_DEFAULT_PROMPT_CLOLR
#define XCMD_DEFAULT_PROMPT_CLOLR   	TX_GREEN
#endif
*/
#ifdef __cplusplus
}
#endif

#endif /* XCMD_CONFIG_H_ */
