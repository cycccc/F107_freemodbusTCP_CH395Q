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
 * 文件名称: ch395spi_hw.h
 * 创建人员: CY
 * 创建日期: 2021-06-15
 * 文档描述: 
 *
 *----------------------------------版本信息------------------------------------
 * 实验平台
 *          |--
 * 版本代号: V1.0
 * 版本说明: 
 *          |-1.0
 * 	         |-2021-06-15
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __CH395SPI_HW_H_
#define __CH395SPI_HW_H_

#include "main.h"
#include "spi.h"

//变量相关的宏定义
#define BUFF_MAX     512



/* 硬件相关宏定义 */
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚    CH395芯片的引脚
			PA12                INT#
  ---------------------------------
      PA4                 CS#
      PA5                 SCK
      PA6                 SDO
      PA7                 SDI      
	---------------------------------
      hspi1	              SPI_Handle
*/
typedef struct{
	  /* 下面是ch395芯片引脚设置	*/
	  SPI_HandleTypeDef* HSPI;     																   /* spi总线号 */
    GPIO_TypeDef* CS_PORT;       																   /* 片选线 端口 */
    uint16_t CS_PIN;                  													   /* 片选线 脚号 */
	  GPIO_TypeDef* INT_PORT;       															   /* 中断线 端口 */
    uint16_t INT_PIN;                  													   /* 中断线 脚号 */
	  GPIO_TypeDef* RST_PORT;                                        /* 复位线 端口 */
	  uint16_t RST_PIN;                                              /* 复位线 脚号 */
	  /* 下面是ch395芯片参数配置	*/
	  uint8_t   CH395Index;                                          /* 芯片序号 */
    uint8_t   IPAddr[4];                                           /* CH395IP地址 32bit*/
    uint8_t   GWIPAddr[4];                                         /* CH395网关地址 32bit*/
    uint8_t   MASKAddr[4];                                         /* CH395子网掩码 32bit*/
    uint8_t   MacAddr[6];                                          /* CH395MAC地址 48bit*/
    uint8_t   PHYStat;                                             /* CH395 PHY状态码 8bit*/
    uint8_t   MackFilt;                                            /* CH395 MAC过滤，默认为接收广播，接收本机MAC 8bit*/
	  uint8_t  RetranCount;                                          /* 重试次数 默认为10次 最大为20次*/
    uint16_t  RetranPeriod;                                        /* 重试周期,单位MS,默认200MS   最大1000MS*/
    uint8_t   IntfMode;                                            /* 接口模式 */
}
CH395_HandleTypedef;

typedef struct{
	  uint8_t  SocketIndex;																					/* socket 编号 一个芯片只有8个socket */
    uint8_t  IPAddr[4];                                           /* socket目标IP地址 32bit*/
    uint8_t  MacAddr[6];                                          /* socket目标地址 48bit*/
    uint8_t  ProtoType;                                           /* 协议类型 */
    uint8_t  ScokStatus;                                          /* socket状态，参考scoket状态定义 */
    uint8_t  TcpMode;                                             /* TCP模式 */
    uint32_t IPRAWProtoType;                                      /* IPRAW 协议类型 */
    uint16_t DesPort;                                             /* 目的端口 */
    uint16_t SourPort;                                            /* 源端口 */  
	  uint8_t* pTxBuff;                                             /* 发送缓存区指针 */
	  uint16_t len;                                                 /* 接数据的长度 */
	  uint8_t* pRxBuff;                                             /* 接收缓存区指针 */
}
SOCKET_HandleTypedef; 

//私人宏定义
#define CH395_INT_STAT(pCH395Handle)          HAL_GPIO_ReadPin(pCH395Handle->INT_PORT,pCH395Handle->INT_PIN)                              /* CH395的INT#引脚状态 */

#define xCH395CmdStart(pCH395Handle)         {HAL_GPIO_WritePin(pCH395Handle->CS_PORT,pCH395Handle->CS_PIN,GPIO_PIN_RESET);}              /* 命令开始 */
#define xEndCH395Cmd(pCH395Handle)           {HAL_GPIO_WritePin(pCH395Handle->CS_PORT,pCH395Handle->CS_PIN,GPIO_PIN_SET);}                /* 命令结束*/

#define CH395_ParamCheck(param)              {if(param == NULL)return 0xff;}

#define TCP_MODE_CLIENT														 0x00
#define TCP_MODE_SERVER                            0x01

//函数定义
void mDelayuS(uint8_t us);
void mDelaymS(uint8_t ms);
void CH395_Port_Init(CH395_HandleTypedef* pCH395Handle);
uint8_t Spi395Exchange(CH395_HandleTypedef* pCH395Handle, uint8_t d);
void xWriteCH395Cmd(CH395_HandleTypedef* pCH395Handle, uint8_t cmd);
void xWriteCH395Data(CH395_HandleTypedef* pCH395Handle, uint8_t mdata);
uint8_t xReadCH395Data(CH395_HandleTypedef* pCH395Handle);

#endif

/********************************End of Head************************************/

