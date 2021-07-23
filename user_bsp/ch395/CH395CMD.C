/********************************** (C) COPYRIGHT *******************************
* File Name          : CH395CMD.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片命令接口文件
*
*******************************************************************************/

/* 头文件包含*/
#include "ch395cmd.h"

/***********************************************************************************/
/**
  CH395_OP_INTERFACE_MODE可以为1-5
  1：硬件总线并口连接方式
  2：软件模拟并口连接方式
  3: 硬件SPI连接方式
  4: 软件模拟SPI方式
  5: 硬件异步串口连接方式
	**: 我这里只保留了SPI连接模式 (硬件SPI)
*/

/***********************************************************************************/


/********************************************************************************
* Function Name  : CH395CMDReset
* Description    : 复位CH395芯片
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDReset(CH395_HandleTypedef* pCH395Handle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD00_RESET_ALL);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395CMDSleep
* Description    : 使CH395进入睡眠状态
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDSleep(CH395_HandleTypedef* pCH395Handle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD00_ENTER_SLEEP);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDGetVer
* Description    : 获取芯片以及固件版本号，1字节，高四位表示芯片版本，
                   低四位表示固件版本
* Input          : None
* Output         : None
* Return         : 1字节芯片及固件版本号
*******************************************************************************/
UINT8 CH395CMDGetVer(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD01_GET_IC_VER);
    i = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return i;
}

/********************************************************************************
* Function Name  : CH395CMDCheckExist
* Description    : 测试命令，用于测试硬件以及接口通讯
* Input          : testdata 1字节测试数据
* Output         : None
* Return         : 硬件OK，返回 testdata按位取反
*******************************************************************************/
UINT8 CH395CMDCheckExist(CH395_HandleTypedef* pCH395Handle,UINT8 testdata)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD11_CHECK_EXIST);
    xWriteCH395Data(pCH395Handle,testdata);
    i = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return i;
}

/********************************************************************************
* Function Name  : CH395CMDSetPHY
* Description    : 设置PHY，主要设置CH395 PHY为100/10M 或者全双工半双工，CH395默
                    为自动协商。
* Input          : phystat 参考PHY 命令参数/状态
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDSetPHY(CH395_HandleTypedef* pCH395Handle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD10_SET_PHY);
    xWriteCH395Data(pCH395Handle,pCH395Handle->PHYStat);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395CMDGetPHYStatus
* Description    : 获取PHY的状态
* Input          : None
* Output         : None
* Return         : 当前CH395PHY状态，参考PHY参数/状态定义
*******************************************************************************/
UINT8 CH395CMDGetPHYStatus(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD01_GET_PHY_STATUS);
    i = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return i;
}

/*******************************************************************************
* Function Name  : CH395CMDGetGlobIntStatus
* Description    : 获取全局中断状态，收到此命令CH395自动取消中断，0x43及以下版本使用
* Input          : None
* Output         : None
* Return         : 返回当前的全局中断状态
*******************************************************************************/
UINT8 CH395CMDGetGlobIntStatus(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 init_status;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD01_GET_GLOB_INT_STATUS);
    init_status = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return  init_status;
}

/********************************************************************************
* Function Name  : CH395CMDInitCH395
* Description    : 初始化CH395芯片。
* Input          : None
* Output         : None
* Return         : 返回执行结果
*******************************************************************************/
UINT8 CH395CMDInitCH395(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i = 0;
    UINT8 s = 0;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD0W_INIT_CH395);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(10);                                                 /* 延时查询，建议2MS以上*/
        s = CH395GetCmdStatus(pCH395Handle);                                     /* 不能过于频繁查询*/
        if(s != CH395_ERR_BUSY)break;                                 /* 如果CH395芯片返回忙状态*/
        if(i++ > 200)return CH395_ERR_UNKNOW;                        /* 超时退出,本函数需要500MS以上执行完毕 */
    }
    return s;
}

/*******************************************************************************
* Function Name  : CH395GetCmdStatus
* Description    : 获取命令执行状态，某些命令需要等待命令执行结果
* Input          : None
* Output         : None
* Return         : 返回上一条命令执行状态
*******************************************************************************/
UINT8 CH395GetCmdStatus(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD01_GET_CMD_STATUS);
    i = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return i;
}

/********************************************************************************
* Function Name  : CH395CMDSetIPAddr
* Description    : 设置CH395的IP地址
* Input          : ipaddr 指IP地址
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDSetIPAddr(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD40_SET_IP_ADDR);
    for(i = 0; i < 4; i++)
    {
        xWriteCH395Data(pCH395Handle,pCH395Handle->IPAddr[i]);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDSetGWIPAddr
* Description    : 设置CH395的网关IP地址
* Input          : ipaddr 指向网关IP地址
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDSetGWIPAddr(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD40_SET_GWIP_ADDR);
    for(i = 0; i < 4; i++)
    {
        xWriteCH395Data(pCH395Handle,pCH395Handle->GWIPAddr[0]);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDSetMASKAddr
* Description    : 设置CH395的子网掩码，默认为255.255.255.0
* Input          : maskaddr 指子网掩码地址
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDSetMASKAddr(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD40_SET_MASK_ADDR);
    for(i = 0; i < 4; i++)
    {
        xWriteCH395Data(pCH395Handle,pCH395Handle->MASKAddr[i]);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDSetMACAddr
* Description    : 设置CH395的MAC地址。
* Input          : amcaddr MAC地址指针
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDSetMACAddr(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD60_SET_MAC_ADDR);
    for(i = 0; i < 6; i++)
    {
        xWriteCH395Data(pCH395Handle,pCH395Handle->MacAddr[i]);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    mDelaymS(100);
}

/********************************************************************************
* Function Name  : CH395CMDGetMACAddr
* Description    : 获取CH395的MAC地址。
* Input          : amcaddr MAC地址指针
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDGetMACAddr(CH395_HandleTypedef* pCH395Handle,UINT8 *amcaddr)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD06_GET_MAC_ADDR);
    for(i = 0; i < 6; i++)
    {
        *amcaddr++ = xReadCH395Data(pCH395Handle);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395CMDSetMACFilt
* Description    : 设置MAC过滤。
* Input          : table0 Hash0
                   table1 Hash1
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDSetMACFilt(CH395_HandleTypedef* pCH395Handle,UINT32 table0,UINT32 table1)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD90_SET_MAC_FILT);
    xWriteCH395Data(pCH395Handle, pCH395Handle->MackFilt);
    xWriteCH395Data(pCH395Handle,(UINT8)table0);
    xWriteCH395Data(pCH395Handle,(UINT8)((UINT16)table0 >> 8));
    xWriteCH395Data(pCH395Handle,(UINT8)(table0 >> 16));
    xWriteCH395Data(pCH395Handle,(UINT8)(table0 >> 24));

    xWriteCH395Data(pCH395Handle,(UINT8)table1);
    xWriteCH395Data(pCH395Handle,(UINT8)((UINT16)table1 >> 8));
    xWriteCH395Data(pCH395Handle,(UINT8)(table1 >> 16));
    xWriteCH395Data(pCH395Handle,(UINT8)(table1 >> 24));
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDGetUnreachIPPT
* Description    : 获取不可达信息 (IP,Port,Protocol Type)
* Input          : list 保存获取到的不可达
                        第1个字节为不可达代码，请参考 不可达代码(CH395INC.H)
                        第2个字节为IP包协议类型
                        第3-4字节为端口号
                        第4-8字节为IP地址
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDGetUnreachIPPT(CH395_HandleTypedef* pCH395Handle,UINT8 *list)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD08_GET_UNREACH_IPPORT);
    for(i = 0; i < 8; i++)
    {
        *list++ = xReadCH395Data(pCH395Handle);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDGetRemoteIPP
* Description    : 获取远端的IP和端口地址，一般在TCP Server模式下使用
* Input          : sockindex Socket索引
                   list 保存IP和端口
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDGetRemoteIPP(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 *list)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD06_GET_REMOT_IPP_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    for(i = 0; i < 6; i++)
    {
        *list++ = xReadCH395Data(pCH395Handle);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395SetSocketDesIP
* Description    : 设置socket n的目的IP地址
* Input          : sockindex Socket索引
                   ipaddr 指向IP地址
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetSocketDesIP(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD50_SET_IP_ADDR_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,pSocketHandle->IPAddr[0]);
    xWriteCH395Data(pCH395Handle,pSocketHandle->IPAddr[1]);
    xWriteCH395Data(pCH395Handle,pSocketHandle->IPAddr[2]);
    xWriteCH395Data(pCH395Handle,pSocketHandle->IPAddr[3]);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395SetSocketProtType
* Description    : 设置socket 的协议类型
* Input          : sockindex Socket索引
                   prottype 协议类型，请参考 socket协议类型定义(CH395INC.H)
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetSocketProtType(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD20_SET_PROTO_TYPE_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,pSocketHandle->ProtoType);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************

* Function Name  : CH395SetSocketDesPort
* Description    : 设置socket n的协议类型
* Input          : sockindex Socket索引
                   desprot 2字节目的端口
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetSocketDesPort(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD30_SET_DES_PORT_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,(UINT8)pSocketHandle->DesPort);
    xWriteCH395Data(pCH395Handle,(UINT8)(pSocketHandle->DesPort >> 8));
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395SetSocketSourPort
* Description    : 设置socket n的协议类型
* Input          : sockindex Socket索引
                   desprot 2字节源端口
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetSocketSourPort(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD30_SET_SOUR_PORT_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,(UINT8)pSocketHandle->SourPort);
    xWriteCH395Data(pCH395Handle,(UINT8)(pSocketHandle->SourPort>>8));
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/******************************************************************************
* Function Name  : CH395SetSocketIPRAWProto
* Description    : IP模式下，socket IP包协议字段
* Input          : sockindex Socket索引
                   prototype IPRAW模式1字节协议字段
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetSocketIPRAWProto(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD20_SET_IPRAW_PRO_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,pSocketHandle->ProtoType);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395EnablePing
* Description    : 开启/关闭 PING
* Input          : enable : 1  开启PING
                          ：0  关闭PING
* Output         : None
* Return         : None
*******************************************************************************/
void CH395EnablePing(CH395_HandleTypedef* pCH395Handle,UINT8 enable)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD01_PING_ENABLE);
    xWriteCH395Data(pCH395Handle,enable);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395SendData
* Description    : 向发送缓冲区写数据
* Input          : sockindex Socket索引
                   databuf  数据缓冲区
                   len   长度
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SendData(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 *databuf,UINT16 len)
{
    UINT16 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD30_WRITE_SEND_BUF_SN);
    xWriteCH395Data(pCH395Handle,(UINT8)pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,(UINT8)len);
    xWriteCH395Data(pCH395Handle,(UINT8)(len>>8));

    for(i = 0; i < len; i++)
    {
        xWriteCH395Data(pCH395Handle,*databuf++);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395GetRecvLength
* Description    : 获取接收缓冲区长度
* Input          : sockindex Socket索引
* Output         : None
* Return         : 返回接收缓冲区有效长度
*******************************************************************************/
UINT16 CH395GetRecvLength(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    UINT16 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD12_GET_RECV_LEN_SN);
    xWriteCH395Data(pCH395Handle,(UINT8)pSocketHandle->SocketIndex);
    i = xReadCH395Data(pCH395Handle);
    i = (UINT16)(xReadCH395Data(pCH395Handle)<<8) + i;
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return i;
}

/*******************************************************************************
* Function Name  : CH395ClearRecvBuf
* Description    : 清除接收缓冲区
* Input          : sockindex Socket索引
* Output         : None
* Return         : None
*******************************************************************************/
void CH395ClearRecvBuf(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD10_CLEAR_RECV_BUF_SN);
    xWriteCH395Data(pCH395Handle,(UINT8)pSocketHandle->SocketIndex);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395GetRecvLength
* Description    : 读取接收缓冲区数据
* Input          : sockindex Socket索引
                   len   长度
                   pbuf  缓冲区
* Output         : None
* Return         : None
*******************************************************************************/
void CH395GetRecvData(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT16 len,UINT8 *pbuf)
{
    UINT16 i;

    if(!len)return;
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD30_READ_RECV_BUF_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,(UINT8)len);
    xWriteCH395Data(pCH395Handle,(UINT8)(len>>8));
    mDelayuS(1);
    for(i = 0; i < len; i++)
    {
        *pbuf = xReadCH395Data(pCH395Handle);
        pbuf++;
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDSetRetryCount
* Description    : 设置重试次数     最大为20次
* Input          : pCH395Handle      ch395句柄指针
* Output         : None
* Return         : None
********************************************************************************/
void CH395CMDSetRetryCount(CH395_HandleTypedef* pCH395Handle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD10_SET_RETRAN_COUNT);
    xWriteCH395Data(pCH395Handle,pCH395Handle->RetranCount);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDSetRetryPeriod
* Description    : 设置重试周期   重试周期单位为毫秒，最大1000ms
* Input          : pCH395Handle      ch395句柄指针
* Output         : None
* Return         : None
*******************************************************************************/
void CH395CMDSetRetryPeriod(CH395_HandleTypedef* pCH395Handle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD10_SET_RETRAN_COUNT);
    xWriteCH395Data(pCH395Handle,(UINT8)pCH395Handle->RetranPeriod);
    xWriteCH395Data(pCH395Handle,(UINT8)(pCH395Handle->RetranPeriod>>8));
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/********************************************************************************
* Function Name  : CH395CMDGetSocketStatus
* Description    : 获取socket
* Input          : None
* Output         : socket n的状态信息，第1字节为socket 打开或者关闭
                   第2字节为TCP状态
* Return         : None
*******************************************************************************/
void CH395CMDGetSocketStatus(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 *status)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD12_GET_SOCKET_STATUS_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    *status++ = xReadCH395Data(pCH395Handle);
    *status++ = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395OpenSocket
* Description    : 打开socket，此命令需要等待执行成功
* Input          : sockindex Socket索引
* Output         : None
* Return         : 返回执行结果
*******************************************************************************/
UINT8  CH395OpenSocket(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    UINT8 i = 0;
    UINT8 s = 0;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD1W_OPEN_SOCKET_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(5);                                                 /* 延时查询，建议2MS以上*/
        s = CH395GetCmdStatus(pCH395Handle);                                     /* 不能过于频繁查询*/
        if(s !=CH395_ERR_BUSY)break;                                 /* 如果CH395芯片返回忙状态*/
        if(i++ > 200)return CH395_ERR_UNKNOW;                        /* 超时退出*/
    }
    return s;
}

/*******************************************************************************
* Function Name  : CH395CloseSocket
* Description    : 关闭socket，
* Input          : sockindex Socket索引
* Output         : None
* Return         : 返回执行结果
*******************************************************************************/
UINT8  CH395CloseSocket(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    UINT8 i = 0;
    UINT8 s = 0;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD1W_CLOSE_SOCKET_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(5);                                                 /* 延时查询，建议2MS以上*/
        s = CH395GetCmdStatus(pCH395Handle);                                     /* 不能过于频繁查询*/
        if(s !=CH395_ERR_BUSY)break;                                 /* 如果CH395芯片返回忙状态*/
        if(i++ > 200)return CH395_ERR_UNKNOW;                        /* 超时退出*/
    }
    return s;
}

/********************************************************************************
* Function Name  : CH395TCPConnect
* Description    : TCP连接，仅在TCP模式下有效，此命令需要等待执行成功
* Input          : sockindex Socket索引
* Output         : None
* Return         : 返回执行结果
*******************************************************************************/
UINT8 CH395TCPConnect(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    UINT8 i = 0;
    UINT8 s = 0;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD1W_TCP_CONNECT_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(5);                                                 /* 延时查询，建议2MS以上*/
        s = CH395GetCmdStatus(pCH395Handle);                                     /* 不能过于频繁查询*/
        if(s !=CH395_ERR_BUSY)break;                                 /* 如果CH395芯片返回忙状态*/
        if(i++ > 200)return CH395_ERR_UNKNOW;                        /* 超时退出*/
    }
    return s;
}

/******************************************************************************
* Function Name  : CH395TCPListen
* Description    : TCP监听，仅在TCP模式下有效，此命令需要等待执行成功
* Input          : sockindex Socket索引
* Output         : None
* Return         : 返回执行结果
*******************************************************************************/
UINT8 CH395TCPListen(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    UINT8 i = 0;
    UINT8 s = 0;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD1W_TCP_LISTEN_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(5);                                                 /* 延时查询，建议2MS以上*/
        s = CH395GetCmdStatus(pCH395Handle);                                     /* 不能过于频繁查询*/
        if(s !=CH395_ERR_BUSY)break;                                 /* 如果CH395芯片返回忙状态*/
        if(i++ > 200)return CH395_ERR_UNKNOW;                        /* 超时退出*/
    }
    return s;
}

/********************************************************************************
* Function Name  : CH395TCPDisconnect
* Description    : TCP断开，仅在TCP模式下有效，此命令需要等待执行成功
* Input          : sockindex Socket索引
* Output         : None
* Return         : None
*******************************************************************************/
UINT8 CH395TCPDisconnect(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    UINT8 i = 0;
    UINT8 s = 0;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD1W_TCP_DISNCONNECT_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(5);                                                 /* 延时查询，建议2MS以上*/
        s = CH395GetCmdStatus(pCH395Handle);                                     /* 不能过于频繁查询*/
        if(s !=CH395_ERR_BUSY)break;                                 /* 如果CH395芯片返回忙状态*/
        if(i++ > 200)return CH395_ERR_UNKNOW;                        /* 超时退出*/
    }
    return s;
}

/*******************************************************************************
* Function Name  : CH395GetSocketInt
* Description    : 获取socket n的中断状态
* Input          : sockindex   socket索引
* Output         : None
* Return         : 中断状态
*******************************************************************************/
UINT8 CH395GetSocketInt(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    UINT8 intstatus;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD11_GET_INT_STATUS_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    mDelayuS(2);
    intstatus = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return intstatus;
}

/*******************************************************************************
* Function Name  : CH395CRCRet6Bit
* Description    : 对多播地址进行CRC运算，并取高6位。
* Input          : mac_addr   MAC地址
* Output         : None
* Return         : 返回CRC32的高6位
*******************************************************************************/
UINT8 CH395CRCRet6Bit(UINT8 *mac_addr)
{
    INT32 perByte;
    INT32 perBit;
    const UINT32 poly = 0x04C11DB7;
    UINT32 crc_value = 0xFFFFFFFF;
    UINT8 c;

    for ( perByte = 0; perByte < 6; perByte ++ )
    {
        c = *(mac_addr++);
        for ( perBit = 0; perBit < 8; perBit++ )
        {
            crc_value = (crc_value<<1)^((((crc_value>>31)^c)&0x01)?poly:0);
            c >>= 1;
        }
    }
    crc_value=crc_value>>26;
    return ((UINT8)crc_value);
}

/******************************************************************************
* Function Name  : CH395DHCPEnable
* Description    : 启动/停止DHCP
* Input          : flag   1:启动DHCP;0：停止DHCP
* Output         : None
* Return         : 执行状态
*******************************************************************************/
UINT8  CH395DHCPEnable(CH395_HandleTypedef* pCH395Handle,UINT8 flag)
{
    UINT8 i = 0;
    UINT8 s;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD10_DHCP_ENABLE);
    xWriteCH395Data(pCH395Handle,flag);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(20);
        s = CH395GetCmdStatus(pCH395Handle);                                     /* 不能过于频繁查询*/
        if(s !=CH395_ERR_BUSY)break;                                 /* 如果CH395芯片返回忙状态*/
        if(i++ > 200)return CH395_ERR_UNKNOW;                        /* 超时退出*/
    }
    return s;
}

/******************************************************************************
* Function Name  : CH395GetDHCPStatus
* Description    : 获取DHCP状态
* Input          : None
* Output         : None
* Return         : DHCP状态，0为成功，其他值表示错误
*******************************************************************************/
UINT8 CH395GetDHCPStatus(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 status;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD01_GET_DHCP_STATUS);
    status = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return status;
}

/*******************************************************************************
* Function Name  : CH395GetIPInf
* Description    : 获取IP，子网掩码和网关地址
* Input          : None
* Output         : 12个字节的IP,子网掩码和网关地址
* Return         : None
*******************************************************************************/
void CH395GetIPInf(CH395_HandleTypedef* pCH395Handle,UINT8 *addr)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD014_GET_IP_INF);
    for(i = 0; i < 20; i++)
    {
        *addr++ = xReadCH395Data(pCH395Handle);
    }
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395WriteGPIOAddr
* Description    : 写GPIO寄存器
* Input          : regadd   寄存器地址
*                ：regval   寄存器值
* Output         : None
* Return         : None
*******************************************************************************/
void CH395WriteGPIOAddr(CH395_HandleTypedef* pCH395Handle,UINT8 regadd,UINT8 regval)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD20_WRITE_GPIO_REG);
    xWriteCH395Data(pCH395Handle,regadd);
    xWriteCH395Data(pCH395Handle,regval);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395ReadGPIOAddr
* Description    : 读GPIO寄存器
* Input          : regadd   寄存器地址
* Output         : None
* Return         : 寄存器的值
*******************************************************************************/
UINT8 CH395ReadGPIOAddr(CH395_HandleTypedef* pCH395Handle,UINT8 regadd)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD10_READ_GPIO_REG);
    xWriteCH395Data(pCH395Handle,regadd);
    mDelaymS(1);
    i = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return i;
}

/*******************************************************************************
* Function Name  : CH395EEPROMErase
* Description    : 擦除EEPROM
* Input          : None
* Output         : None
* Return         : 执行状态
*******************************************************************************/
UINT8 CH395EEPROMErase(CH395_HandleTypedef* pCH395Handle)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD00_EEPROM_ERASE);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(20);
        i = CH395GetCmdStatus(pCH395Handle);
        if(i == CH395_ERR_BUSY)continue;
        break;
    }
    return i;
}

/*******************************************************************************
* Function Name  : CH395EEPROMWrite
* Description    : 写EEPROM
* Input          : eepaddr  EEPROM地址
*                ：buf      缓冲区地址
*                ：len      长度
* Output         : None
* Return         : 执行状态
*******************************************************************************/
UINT8 CH395EEPROMWrite(CH395_HandleTypedef* pCH395Handle,UINT16 eepaddr,UINT8 *buf,UINT8 len)
{
    UINT8 i;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD30_EEPROM_WRITE);
    xWriteCH395Data(pCH395Handle,(UINT8)(eepaddr));
    xWriteCH395Data(pCH395Handle,(UINT8)(eepaddr >> 8));
    xWriteCH395Data(pCH395Handle,len);
    while(len--)xWriteCH395Data(pCH395Handle,*buf++);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    while(1)
    {
        mDelaymS(20);
        i = CH395GetCmdStatus(pCH395Handle);
        if(i == CH395_ERR_BUSY)continue;
        break;
    }
    return i;
}

/*******************************************************************************
* Function Name  : CH395EEPROMRead
* Description    : 读EEPROM
* Input          : eepaddr  EEPROM地址
*                ：buf      缓冲区地址
*                ：len      长度
* Output         : None
* Return         : None
*******************************************************************************/
void CH395EEPROMRead(CH395_HandleTypedef* pCH395Handle,UINT16 eepaddr,UINT8 *buf,UINT8 len)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD30_EEPROM_READ);
    xWriteCH395Data(pCH395Handle,(UINT8)(eepaddr));
    xWriteCH395Data(pCH395Handle,(UINT8)(eepaddr >> 8));
    xWriteCH395Data(pCH395Handle,len);
    mDelaymS(1);
    while(len--)*buf++ = xReadCH395Data(pCH395Handle);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395SetTCPMss
* Description    : 设置TCP MSS值
* Input          : tcpmss
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetTCPMss(CH395_HandleTypedef* pCH395Handle,UINT16 tcpmss)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD20_SET_TCP_MSS);
    xWriteCH395Data(pCH395Handle,(UINT8)(tcpmss));
    xWriteCH395Data(pCH395Handle,(UINT8)(tcpmss >> 8));
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395SetSocketRecvBuf
* Description    : 设置Socket接收缓冲区
* Input          : sockindex  socket索引
                 ：startblk   起始地址
                 ：blknum     单位缓冲区个数 ，单位为512字节
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetSocketRecvBuf(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 startblk,UINT8 blknum)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD30_SET_RECV_BUF);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,startblk);
    xWriteCH395Data(pCH395Handle,blknum);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395SetSocketSendBuf
* Description    : 设置Socket发送缓冲区
* Input          : sockindex  socket索引
                 ：startblk   起始地址
                 ：blknum     单位缓冲区个数,单位为512字节
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetSocketSendBuf(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 startblk,UINT8 blknum)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD30_SET_SEND_BUF);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,startblk);
    xWriteCH395Data(pCH395Handle,blknum);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395UDPSendTo
* Description    : UDP向指定的IP和端口发送数据
* Input          : buf     : 发送数据缓冲区
                   len     : 发送数据长度
				   ip      : 目标IP
				   port    : 目标端口
				   sockeid : socket索引值
* Output         : None
* Return         : None
*******************************************************************************/
void CH395UDPSendTo(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 *buf,UINT32 len)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    CH395SetSocketDesIP(pCH395Handle,pSocketHandle);                            /* 设置socket 0目标IP地址 */
    CH395SetSocketDesPort(pCH395Handle,pSocketHandle);
    CH395SendData(pCH395Handle,pSocketHandle,buf,len);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395SetStartPara
* Description    : 设置CH395启动参数
* Input          : mdata
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetStartPara(CH395_HandleTypedef* pCH395Handle,UINT32 mdata)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD40_SET_FUN_PARA);
    xWriteCH395Data(pCH395Handle,(UINT8)mdata);
    xWriteCH395Data(pCH395Handle,(UINT8)((UINT16)mdata>>8));
    xWriteCH395Data(pCH395Handle,(UINT8)(mdata >> 16));
    xWriteCH395Data(pCH395Handle,(UINT8)(mdata >> 24));
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395CMDGetGlobIntStatus_ALL
* Description    : 获取全局中断状态，收到此命令CH395自动取消中断,0x44及以上版本使用
* Input          : None
* Output         : None
* Return         : 返回当前的全局中断状态
*******************************************************************************/
UINT16 CH395CMDGetGlobIntStatus_ALL(CH395_HandleTypedef* pCH395Handle)
{
    UINT16 init_status;

    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD02_GET_GLOB_INT_STATUS_ALL);
    mDelayuS(2);
    init_status = xReadCH395Data(pCH395Handle);
    init_status = (UINT16)(xReadCH395Data(pCH395Handle)<<8) + init_status;
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
    return 	init_status;
}

/*******************************************************************************
* Function Name  : CH395SetKeepLive
* Description    : 设置keepalive功能
* Input          : sockindex Socket号
*                  cmd 0：关闭 1：开启
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetKeepLive(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 cmd)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD20_SET_KEEP_LIVE_SN);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,cmd);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395KeepLiveCNT
* Description    : 设置keepalive重试次数
* Input          : cnt 重试次数（）
* Output         : None
* Return         : None
*******************************************************************************/
void CH395KeepLiveCNT(CH395_HandleTypedef* pCH395Handle,UINT8 cnt)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD10_SET_KEEP_LIVE_CNT);
    xWriteCH395Data(pCH395Handle,cnt);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395KeepLiveIDLE
* Description    : 设置KEEPLIVE空闲
* Input          : idle 空闲时间（单位：ms）
* Output         : None
* Return         : None
*******************************************************************************/
void CH395KeepLiveIDLE(CH395_HandleTypedef* pCH395Handle,UINT32 idle)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD40_SET_KEEP_LIVE_IDLE);
    xWriteCH395Data(pCH395Handle,(UINT8)idle);
    xWriteCH395Data(pCH395Handle,(UINT8)((UINT16)idle>>8));
    xWriteCH395Data(pCH395Handle,(UINT8)(idle >> 16));
    xWriteCH395Data(pCH395Handle,(UINT8)(idle >> 24));
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395KeepLiveINTVL
* Description    : 设置KeepLive间隔时间
* Input          : intvl 间隔时间（单位：ms）
* Output         : None
* Return         : None
*******************************************************************************/
void CH395KeepLiveINTVL(CH395_HandleTypedef* pCH395Handle,UINT32 intvl)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD40_SET_KEEP_LIVE_INTVL);
    xWriteCH395Data(pCH395Handle,(UINT8)intvl);
    xWriteCH395Data(pCH395Handle,(UINT8)((UINT16)intvl>>8));
    xWriteCH395Data(pCH395Handle,(UINT8)(intvl >> 16));
    xWriteCH395Data(pCH395Handle,(UINT8)(intvl >> 24));
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/*******************************************************************************
* Function Name  : CH395SetTTLNum
* Description    : 设置TTL
* Input          : sockindex Socket号
*                  TTLnum:TTL数
* Output         : None
* Return         : None
*******************************************************************************/
void CH395SetTTLNum(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle,UINT8 TTLnum)
{
    xCH395CmdStart(pCH395Handle);                                                  /* 命令开始 */
    xWriteCH395Cmd(pCH395Handle,CMD20_SET_TTL);
    xWriteCH395Data(pCH395Handle,pSocketHandle->SocketIndex);
    xWriteCH395Data(pCH395Handle,TTLnum);
    xEndCH395Cmd(pCH395Handle);                                                  /* 命令结束*/
}

/**************************** endfile *************************************/

/****************************以下是自己添加的函数**********************************/
/**********************************************************************************
* Function Name  : CH395Init
* Description    : 配置CH395的IP,GWIP,MAC等参数，并初始化
* Input          : None
* Output         : None
* Return         : 函数执行结果
**********************************************************************************/
uint8_t CH395_Init(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    uint8_t i;

    //检查参数是否有效
    CH395_ParamCheck(pCH395Handle);

    CH395_Port_Init(pCH395Handle);                    // 初始化下片选引脚

    i = CH395CMDCheckExist(pCH395Handle,0x65);
    if(i != 0x9a)return CH395_ERR_UNKNOW;                            /* 测试命令，如果无法通过返回0XFA */
    /* 返回0XFA一般为硬件错误或者读写时序不对 */

    CH395CMDSetIPAddr(pCH395Handle);                            /* 设置CH395的IP地址 */
//  CH395CMDSetMACAddr(pCH395Handle);                           /* 设置CH395的MAC地址 */
    CH395CMDSetGWIPAddr(pCH395Handle);                          /* 设置网关地址 */
    CH395CMDSetMASKAddr(pCH395Handle);                          /* 设置子网掩码，默认为255.255.255.0*/
//    CH395SetStartPara(pCH395Handle,FUN_PARA_FLAG_TCP_SERVER);   /*TCP SERVER支持多连接时，需初始化此启动参数*/
    i = CH395CMDInitCH395(pCH395Handle);                        /* 初始化CH395芯片 */

    CH395SetSocketRecvBuf(pCH395Handle,pSocketHandle,0,(BUFF_MAX/512));
    CH395SetSocketSendBuf(pCH395Handle,pSocketHandle,(BUFF_MAX/512),(BUFF_MAX/512));
    return i;
}

/**********************************************************************************
* Function Name  : InitSocketParam
* Description    : 初始化socket
* Input          : _SOCK_INF socket结构体
* Output         : None
* Return         : 函数执行结果
**********************************************************************************/
uint8_t CH395_InitSocketParam(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    uint8_t retval;

    //检查参数是否有效
    CH395_ParamCheck(pCH395Handle);
    CH395_ParamCheck(pSocketHandle);

    /* ---初始化socket--- */
//    //socket 目标IP地址
//    CH395SetSocketDesIP(pCH395Handle,pSocketHandle);
    //socket 协议类型
    CH395SetSocketProtType(pCH395Handle,pSocketHandle);
    //socket 源端口
    CH395SetSocketSourPort(pCH395Handle,pSocketHandle);
//    //socket 目的端口
//    CH395SetSocketDesPort(pCH395Handle,pSocketHandle);
    /* ---结束初始化--- */

    //打开socket
    retval = CH395OpenSocket(pCH395Handle,pSocketHandle);
    if(retval == CH395_ERR_UNKNOW)
    {
        while(1);
    }

    //监听socket
    retval = CH395TCPListen(pCH395Handle,pSocketHandle);
    if(retval == CH395_ERR_UNKNOW)
    {
        while(1);
    }

    return retval;
}

/***
** 函数名称: CH395_SocketIRQReceive_CallBack
** 功能描述: ch395套接字处理中断接收回调函数
** 参数说明
**       pCH395Handle: [输入]   ch395芯片句柄
**			 pSocketHandle: [输入]  socket套接字句柄
** 返回说明: None
** 创建人员: CY
** 创建日期: 2021-07-18
 *------------------*
** 更多描述:
 *------------------*
 */
__weak void CH395_SocketIRQReceive_CallBack(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
}

/***
** 函数名称: CH395_SocketIRQTransmit_CallBack
** 功能描述: ch395套接字处理中断发送回调函数
** 参数说明
**       pCH395Handle: [输入]   ch395芯片句柄
**			 pSocketHandle: [输入]  socket套接字句柄
** 返回说明: None
** 创建人员: CY
** 创建日期: 2021-07-18
 *------------------*
** 更多描述:
 *------------------*
 */
__weak void CH395_SocketIRQTransmit_CallBack(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
}

/**********************************************************************************
* Function Name  : CH395SocketInterrupt
* Description    : CH395 socket 中断,在全局中断中被调用  socket中断处理函数
* Input          : sockindex
* Output         : None
* Return         : None
**********************************************************************************/
void CH395SocketInterrupt(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    UINT8  sock_int_socket;
    UINT8  buf[10];

    sock_int_socket = CH395GetSocketInt(pCH395Handle,pSocketHandle);  /* 获取socket 的中断状态 */
    if(sock_int_socket & SINT_STAT_SENBUF_FREE)                       /* 发送缓冲区空闲，可以继续写入要发送的数据 */
    {
        CH395_SocketIRQTransmit_CallBack(pCH395Handle,pSocketHandle);
    }
    if(sock_int_socket & SINT_STAT_SEND_OK)                           /* 发送完成中断 */
    {
    }
    if(sock_int_socket & SINT_STAT_RECV)                              /* 接收中断 */
    {
        pSocketHandle->len = CH395GetRecvLength(pCH395Handle,pSocketHandle);         /* 获取当前缓冲区内数据长度 */
        if(pSocketHandle->len == 0)return;
        if(pSocketHandle->len > BUFF_MAX)pSocketHandle->len = BUFF_MAX;
        CH395GetRecvData(pCH395Handle,pSocketHandle,pSocketHandle->len,pSocketHandle->pRxBuff);    /* 读取数据 */
        //进入回调函数进行进一步处理
        CH395_SocketIRQReceive_CallBack(pCH395Handle,pSocketHandle);
    }
    if(sock_int_socket & SINT_STAT_CONNECT)                          /* 连接中断，仅在TCP模式下有效*/
    {
        if(pSocketHandle->TcpMode == TCP_MODE_SERVER)                       /* 如果socket 为服务器模式，用户可以获取远端的IP和端口*/
        {
            CH395CMDGetRemoteIPP(pCH395Handle,pSocketHandle,buf);
            pSocketHandle->DesPort = ((UINT16)buf[4]<<8) + (UINT16)buf[5];
            for(int i=0; i<4; i++)
            {
                pSocketHandle->IPAddr[i] = buf[i];
            }
        }
//        CH395SetKeepLive(pCH395Handle,pSocketHandle,1);							 /*打开KEEPALIVE保活定时器*/
//        CH395SetTTLNum(pCH395Handle,pSocketHandle,40); 							 /*设置TTL*/
    }
    /*
    **产生断开连接中断和超时中断时，CH395默认配置是内部主动关闭，用户不需要自己关闭该Socket，如果想配置成不主动关闭Socket需要配置
    **SOCK_CTRL_FLAG_SOCKET_CLOSE标志位（默认为0），如果该标志为1，CH395内部不对Socket进行关闭处理，用户在连接中断和超时中断时调用
    **CH395CloseSocket函数对Socket进行关闭，如果不关闭则该Socket一直为连接的状态（事实上已经断开），就不能再去连接了。
    */
    if((sock_int_socket & SINT_STAT_DISCONNECT) && pSocketHandle->ProtoType == PROTO_TYPE_TCP)   /* 断开中断，仅在TCP模式下有效 */
    {
        CH395CloseSocket(pCH395Handle,pSocketHandle);
        CH395OpenSocket(pCH395Handle,pSocketHandle);
        CH395TCPListen(pCH395Handle,pSocketHandle);
    }
    if(sock_int_socket & SINT_STAT_TIM_OUT)                           /* 超时中断 */
    {
        CH395CloseSocket(pCH395Handle,pSocketHandle);
        CH395OpenSocket(pCH395Handle,pSocketHandle);
        CH395TCPListen(pCH395Handle,pSocketHandle);
    }
}

/**
 * 函数名称: CH395_SocketIRQ
 * 功能描述: ch395芯片中断查询与处理函数
 * 参数说明: pCH395Handle: [输入]     ch395芯片句柄
 *			     pSocketHandle: [输入]    socket套接字句柄
 * 返回说明: IRQ_status:  中断状态
 * 创建人员: CY
 * 创建日期: 2021-07-18
 *------------------*
 * 更多描述:
 *------------------*
 */
uint8_t CH395_SocketIRQ(CH395_HandleTypedef* pCH395Handle,SOCKET_HandleTypedef* pSocketHandle)
{
    uint16_t IRQ_status;

    //检查参数是否有效
    CH395_ParamCheck(pCH395Handle);
    CH395_ParamCheck(pSocketHandle);

    IRQ_status = CH395CMDGetGlobIntStatus_ALL(pCH395Handle);
    if(IRQ_status & GINT_STAT_IP_CONFLI)                            /* 产生IP冲突中断，建议重新修改CH395的 IP，并初始化CH395*/
    {
    }
    if(IRQ_status & GINT_STAT_PHY_CHANGE)                           /* 产生PHY改变中断*/
    {
    }
    if(IRQ_status & GINT_STAT_SOCK0)
    {
        //处理socket 程序
        CH395SocketInterrupt(pCH395Handle,pSocketHandle);
    }
    return IRQ_status;
}

/****************************以上是自己添加的函数**********************************/
