/********************************** (C) COPYRIGHT *******************************
* File Name          : CH395SPI_HW.C
* Author             : WCH
* Version            : V1.1
* Date               : 2014/8/1
* Description        : CH395芯片 硬件SPI串行连接的硬件抽象层 V1.0
*
*******************************************************************************/


#include "ch395spi_hw.h"

/*******************************************************************************
* Function Name  : mDelayuS
* Description    : 延时指定微秒时间,根据单片机主频调整,不精确
* Input          : us---延时时间值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS( uint8_t us )
{
    while(us--)
    {
        for(int i=0; i<180; i++); //简单延时 并不准确    F429@180MHZ
    }
}

/*******************************************************************************
* Function Name  : mDelaymS
* Description    : 延时指定毫秒时间,根据单片机主频调整,不精确
* Input          : ms---延时时间值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS( uint8_t ms )
{
		HAL_Delay(ms);
}

/******************************************************************************
* Function Name  : CH395_Port_Init
* Description    : 硬件初始化部分
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_Port_Init(CH395_HandleTypedef* pCH395Handle)
{
	//stm32cubeMX 已经在前面初始化好了，不需要在里面进行初始化
    xEndCH395Cmd(pCH395Handle);
}

/*******************************************************************************
* Function Name  : Spi395Exchange
* Description    : 硬件SPI输出且输入8个位数据
* Input          : d---将要送入到CH395的数据
* Output         : None
* Return         : None
*******************************************************************************/
uint8_t Spi395Exchange(CH395_HandleTypedef* pCH395Handle, uint8_t d)
{
	  uint8_t Rxdata;
	
    HAL_SPI_TransmitReceive(pCH395Handle->HSPI, &d, &Rxdata, 1, 1000);
    return Rxdata;          		     //返回收到的数据
}

/******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : cmd 8位的命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd(CH395_HandleTypedef* pCH395Handle, uint8_t cmd)
{
    Spi395Exchange(pCH395Handle,cmd);                                             /* SPI发送命令码 */
    mDelayuS(2);                                                     /* 必要延时,延时1.5uS确保读写周期不小于1.5uS */
}

/******************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395写数据
* Input          : mdata 8位数据
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Data(CH395_HandleTypedef* pCH395Handle, uint8_t mdata)
{
    Spi395Exchange(pCH395Handle,mdata);                                           /* SPI发送数据 */
}

/*******************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读数据
* Input          : None
* Output         : None
* Return         : 8位数据
*******************************************************************************/
uint8_t xReadCH395Data(CH395_HandleTypedef* pCH395Handle)
{
    uint8_t i;
	
    i = Spi395Exchange(pCH395Handle,0xff);                                        /* SPI读数据 */
    return i;
}

/**************************** endfile *************************************/
