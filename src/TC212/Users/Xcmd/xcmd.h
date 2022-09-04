/*
 * xcmd.h
 *
 *  Created on: 2022-01-01
 *      Author: XinnZ & Pomin, Landian, HBUT
 *  XinnZ's Blog: https://blog.xinnz.cn/
 *  Pomin's Blog: https://www.pomin.top/
 */

#ifndef XCMD_H_
#define XCMD_H_

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "xcmd_define.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*cmd_func_t)(int argv, char *argc[]);
typedef int (*cmd_key_func_t)(void *data);

typedef struct __cmd {
    char *name;
    cmd_func_t func;
    char *help;
    struct __cmd *next;
} xcmd_t;

typedef struct __key {
    char *key;
    cmd_key_func_t func;
    char *help;
    struct __key *next;
} xcmd_key_t;

typedef struct
{
    void (*Init)(void);
    void (*Rece)(void);
} XCMD_TypeDef;

extern XCMD_TypeDef Xcmd;

/**
 * @description: ��ʱ�ڳ�ʼ��
 * @return {*}
 */
// void xcmd_init(void);

/**
 * @description: ��������������
 * @param {*}
 * @return {*}
 */
// void xcmd_task(void);

/**
 * @description: ע��һ��ָ��
 * @param {xcmd_t*} cmds��ָ�
 * @param {uint16_t} number��ָ�����
 * @return {int} �Ѿ�ע���ָ��ĸ���
 */
int xcmd_cmd_register(xcmd_t *cmds, uint16_t number);

/**
 * @description: ע��һ�鰴��
 * @param {xcmd_key_t*} keys����ݼ���
 * @param {uint16_t} number����ݼ��ĸ���
 * @return {int}���Ѿ�ע��Ŀ�ݼ��ĸ���
 */
int xcmd_key_register(xcmd_key_t *keys, uint16_t number);

/**
 * @description: ��ȡ�����б�����ͨ��nextָ����Ա�������ָ��
 * @param {xcmd_key_t*} keys����ݼ���
 * @param {uint16_t} number����ݼ��ĸ���
 * @return {int}���Ѿ�ע��Ŀ�ݼ��ĸ���
 */
xcmd_t *xcmd_cmdlist_get(void);

/**
 * @description: ��ȡ�����б�����ͨ��nextָ����Ա������а���
 * @param {xcmd_key_t*} keys����ݼ���
 * @param {uint16_t} number����ݼ��ĸ���
 * @return {int}���Ѿ�ע��Ŀ�ݼ��ĸ���
 */
xcmd_key_t *xcmd_keylist_get(void);

/**
 * @description: ɾ���Ѿ�ע���cmd
 * @param {char*} cmd��cmd��
 * @return {int}��0��success�� !0��failed
 */
int xcmd_unregister_cmd(char *cmd);

/**
 * @description:ɾ���Ѿ�ע���key
 * @param {char*} key��key��
 * @return {int}��0��success�� !0��failed
 */
int xcmd_unregister_key(char *key);

/**
 * @description: �ֶ�ִ������
 * @param {char* } str������
 * @return {uint16_t}  ����ִ�н��
 */
int xcmd_exec(char *str);

/**
 * @description: ��ӡ�ַ���
 * @param {char*} str
 * @return ��
 */
void xcmd_print(const char *fmt, ...);

/**
 * @description: ����ʾ������һ���ַ�
 * @param {char} c
 * @return ��
 */
void xcmd_display_insert_char(char c);

/**
 * @description: ɾ����ʾ����һ���ַ�
 * @param {*}
 * @return ��
 */
void xcmd_display_delete_char(void);

/**
 * @description: ���ع�굱ǰ���ַ�
 * @param {char*}cha�洢���ص��ַ�
 * @return {uint16_t}0���λ�����ַ���1���ַ�
 */
uint16_t xcmd_display_current_char(char *cha);

/**
 * @description: �����ʾ��
 * @param {*}
 * @return ��
 */
void xcmd_display_clear(void);

/**
 * @description: ��ȡ��ʾ��������
 * @param {*}
 * @return {char*} *��ʾ�������ݵ�ָ��
 */
char *xcmd_display_get(void);

/**
 * @description: ������ʾ��������
 * @param {char*} Ҫ��ʵ������
 * @return ��
 */
void xcmd_display_print(const char *msg);
void xcmd_display_write(const char *buf, uint16_t len);

/**
 * @description:
 * @param {*}
 * @return {*}
 */
char *xcmd_display_line_end(void);

/**
 * @description: ����������
 * @param {*}
 * @return {*}
 */
void xcmd_display_cursor_set(uint16_t pos);
uint16_t xcmd_display_cursor_get(void);

/**
 * @description: ������������ʾ�ַ������˺������������ַ�����ֻ�Ǽ�ס�˴����ָ��
 * @param {char*} prompt
 * @return {*}
 */
void xcmd_set_prompt(const char *prompt);
const char *xcmd_get_prompt(void);

/**
 * @description: ע����������պ����Ĺ��Ӻ���
 * @param {func_p} ���Ӻ���������0����յ������ݻ᷵�ظ�������������1�򲻻�
 * @return {*} ��
 */
void xcmd_register_rcv_hook_func(uint16_t (*func_p)(char *));

/**
 * @description: ��ȡ��ʷ��¼�ĸ���
 * @param {*}
 * @return {uint16_t} �Ѿ���¼����ʷ����
 */
uint16_t xcmd_history_len(void);

/**
 * @description: ����һ����ʷ��¼
 * @param {char*} str
 * @return ��
 */
void xcmd_history_insert(char *str);

/**
 * @description: ��ȡ��һ����ʷ��¼
 * @param {*}
 * @return ��ʷ����
 */
char *xcmd_history_next(void);

/**
 * @description: ��ȡ������ʷ��¼
 * @param {*}
 * @return ��ʷ����
 */
char *xcmd_history_prev(void);

/**
 * @description: ��ȡ��ǰ��ʷ��¼
 * @param {*}
 * @return ��ʷ����
 */
char *xcmd_history_current(void);

/**
 * @description: ����ʷ��¼ָ��ָ��ͷ��
 * @param {*}
 * @return ��
 */
void xcmd_history_slider_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* XCMD_H_ */
