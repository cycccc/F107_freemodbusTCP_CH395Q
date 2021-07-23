/**
 *******************************Copyright (c)************************************
 *
 *                   (c) Copyright 2021, CY, China, QD.
 *                           All Rights Reserved
 *
 *                           By(南京万福祥电子科技有限公司)
 *                           http://www.njwfx.com
 *
 *----------------------------------文件信息------------------------------------
 * 文件名称: modbusTCP.h
 * 创建人员: CY
 * 创建日期: 2021-07-18
 * 文档描述: 
 *
 *----------------------------------版本信息------------------------------------
 * 实验平台
 *          |--
 * 版本代号: V1.0
 * 版本说明: 
 *          |-1.0
 * 	         |-2021-07-18
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __MODBUS_T_C_P_H_
#define __MODBUS_T_C_P_H_


#include "../ch395/ch395cmd.h"


/* 类型定义 ------------------------------------------------------------------*/

/* 宏定义 --------------------------------------------------------------------*/
#define  TCP_ALLSLAVEADDR    0x00FF
#define  TCP_MAX             BUFF_MAX

#define  COIL_D01		0x01



/* 扩展变量 ------------------------------------------------------------------*/
extern uint16_t P_RxCount;          // 接收字符计数
extern uint16_t P_TxCount;          // 发送字符计数
extern uint16_t P_Addr,P_RegNum,P_ByteNum;

/* 函数声明 ------------------------------------------------------------------*/

void MB_Parse_Data(void);       //mosbus TCP 解析数据








#endif

/********************************End of Head************************************/

