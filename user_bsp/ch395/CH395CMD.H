/********************************** (C) COPYRIGHT *******************************
* File Name          : CH395CMD.H
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片命令接口文件,常用子程序外部调用
*******************************************************************************/

#ifndef __CH395CMD_H__
#define __CH395CMD_H__

#include "CH395INC.H"
#include "ch395spi_hw.h"


void CH395CMDReset(CH395_HandleTypedef* pCH395Handle);                                                 /* 复位 */

void CH395CMDSleep(CH395_HandleTypedef* pCH395Handle);                                                 /* 睡眠 */

UINT8 CH395CMDGetVer(CH395_HandleTypedef* pCH395Handle);                                               /* 获取芯片及固件版本号 */

UINT8 CH395CMDCheckExist(CH395_HandleTypedef* pCH395Handle,UINT8 testdata);                            /* 测试命令 */

void CH395CMDSetPHY(CH395_HandleTypedef* pCH395Handle);                                                /* 设置PHY状态  */

UINT8 CH395CMDGetPHYStatus(CH395_HandleTypedef* pCH395Handle);                                         /* 获取PHY状态 */

UINT8 CH395CMDGetGlobIntStatus(CH395_HandleTypedef* pCH395Handle);                                     /* 获取CH395全局中断状态 */

UINT8 CH395CMDInitCH395(CH395_HandleTypedef* pCH395Handle);                                            /* 初始化CH395 */

UINT8 CH395GetCmdStatus(CH395_HandleTypedef* pCH395Handle);                                            /* 获取命令执行状态 */

void CH395CMDSetIPAddr(CH395_HandleTypedef* pCH395Handle);                                             /* 设置CH395的IP地址 */

void CH395CMDSetGWIPAddr(CH395_HandleTypedef* pCH395Handle);                                           /* 设置CH395的网关IP地址 */

void CH395CMDSetMASKAddr(CH395_HandleTypedef* pCH395Handle);                                           /* 设置子网掩码 */

void CH395CMDSetMACAddr(CH395_HandleTypedef* pCH395Handle);                                            /* 设置CH395的MAC地址 */

void CH395CMDGetMACAddr(CH395_HandleTypedef* pCH395Handle,UINT8 *amcaddr);                             /* 获取MAC地址 */

void CH395CMDSetMACFilt(CH395_HandleTypedef* pCH395Handle,UINT32 table0,UINT32 table1);                /* 设置CH395的MAC过滤 */

void CH395CMDGetUnreachIPPT(CH395_HandleTypedef* pCH395Handle,UINT8 *list);                            /* 获取不可达地址以及端口 */

void CH395CMDGetRemoteIPP(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 *list);              /* 获取远端IP和端口，一般在TCP Server下使用 */

void CH395SetSocketDesIP(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);       /* 设置scoket n的目的IP地址 */

void CH395SetSocketProtType(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);    /* 设置socket n的协议类型 */

void CH395SetSocketDesPort(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);     /* 设置socket n的目的端口 */

void CH395SetSocketSourPort(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);    /* 设置socket n的源端口 */

void CH395SetSocketIPRAWProto(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);  /* 在IPRAW模式下，设置socket n的IP包协议字段 */

void CH395EnablePing(CH395_HandleTypedef* pCH395Handle,UINT8 enable);                                              /* 开启/关闭 PING */

void CH395SendData(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 *databuf,UINT16 len);       /* 向socket n的发送缓冲区写数据 */

UINT16 CH395GetRecvLength(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);                          /* 获取socket n的接收长度 */

void CH395ClearRecvBuf(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);                             /* 清除socket n的接收缓冲区 */

void CH395GetRecvData(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT16 len,UINT8 *pbuf);       /* 获取接收数据 */

void CH395CMDSetRetryCount(CH395_HandleTypedef* pCH395Handle);                                         /* 设置最大重试次数 */

void CH395CMDSetRetryPeriod(CH395_HandleTypedef* pCH395Handle);                                        /* 设置最大重试周期 单位 毫秒*/

void CH395CMDGetSocketStatus(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 *status) ;        /* 获取socket n的状态 */

UINT8  CH395OpenSocket(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);                             /* 打开socket n*/

UINT8  CH395CloseSocket(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);                             /* 关闭socket n*/

UINT8 CH395TCPConnect(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);                               /* TCP连接 */

UINT8 CH395TCPListen(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);                                /* TCP监听 */

UINT8 CH395TCPDisconnect(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);                            /* TCP断开连接 */

UINT8 CH395GetSocketInt(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);                            /* 获取socket n的中断状态 */
                                                                     
UINT8 CH395CRCRet6Bit(UINT8 *mac_addr);                              /* 多播地址CRC32，用于HASH过滤 */
                                                                     /*Function Count = 36 */	

UINT8  CH395DHCPEnable(CH395_HandleTypedef* pCH395Handle,UINT8 flag);           /* 启动/停止DHCP  */  

UINT8 CH395GetDHCPStatus(CH395_HandleTypedef* pCH395Handle);                  /* 获取DHCP状态 */

void CH395GetIPInf(CH395_HandleTypedef* pCH395Handle,UINT8 *addr);           /* 获取IP，子网掩码和网关地址 */       

void CH395WriteGPIOAddr(CH395_HandleTypedef* pCH395Handle,UINT8 regadd,UINT8 regval);         /* 写GPIO寄存器 */ 

UINT8 CH395ReadGPIOAddr(CH395_HandleTypedef* pCH395Handle,UINT8 regadd);                        /* 读GPIO寄存器 */

UINT8 CH395EEPROMErase(CH395_HandleTypedef* pCH395Handle);                                    /* 擦除EEPROM */

UINT8 CH395EEPROMWrite(CH395_HandleTypedef* pCH395Handle,UINT16 eepaddr,UINT8 *buf,UINT8 len);       /* 写EEPROM */

void CH395EEPROMRead(CH395_HandleTypedef* pCH395Handle,UINT16 eepaddr,UINT8 *buf,UINT8 len);          /* 读EEPROM */

void CH395SetTCPMss(CH395_HandleTypedef* pCH395Handle,UINT16 tcpmss);                      /* 设置TCP MSS值 */

void CH395SetSocketRecvBuf(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 startblk,UINT8 blknum);       /* 设置Socket接收缓冲区 */

void CH395SetSocketSendBuf(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 startblk,UINT8 blknum);       /* 设置Socket发送缓冲区 */

void CH395UDPSendTo(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 *buf,UINT32 len);                   /* UDP向指定的IP和端口发送数据 */

void CH395SetStartPara(CH395_HandleTypedef* pCH395Handle,UINT32 mdata);                 /* 设置CH395启动参数 */

UINT16 CH395CMDGetGlobIntStatus_ALL(CH395_HandleTypedef* pCH395Handle);                /* 获取全局中断状态，收到此命令CH395自动取消中断,0x44及以上版本使用 */

void CH395SetKeepLive(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 cmd);            /* keepalive 使能 */

void CH395KeepLiveCNT(CH395_HandleTypedef* pCH395Handle,UINT8 cnt);                                                /* keepalive 参数设置 */

void CH395KeepLiveIDLE(CH395_HandleTypedef* pCH395Handle,UINT32 idle);                                             /* keepalive 参数设置 */

void CH395KeepLiveINTVL(CH395_HandleTypedef* pCH395Handle,UINT32 intvl);                                           /* keepalive 参数设置 */

void CH395SetTTLNum(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 TTLnum);           /* TTL参数设置 */

/**************************** endfile *************************************/

/****************************以下是自己添加的函数**********************************/
uint8_t CH395_Init(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);
uint8_t CH395_InitSocketParam(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);
uint8_t CH395_SocketIRQ(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle);

/****************************以上是自己添加的函数**********************************/


#endif
