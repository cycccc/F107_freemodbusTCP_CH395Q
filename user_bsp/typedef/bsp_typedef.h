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
 * 文件名称: bsp_typedef.h
 * 创建人员: CY
 * 创建日期: 2021-02-10
 * 文档描述: 自己的宏定义归总
 *
 *----------------------------------版本信息------------------------------------
 * 版本代号: V1.0
 * 版本说明:
 *          |-1.0
 * 	         |-2021-02-10
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __BSP_TYPEDEF_H_
#define __BSP_TYPEDEF_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//#ifdef STM32F103xE
//    #include "core_cm3.h"
//    #include "stm32f1xx_hal.h"
//#endif /* STM32F103xE */

//#ifdef STM32F107xC
//    #include "core_cm3.h"
//    #include "stm32f1xx_hal.h"
//#endif /* STM32F107xC */

//#ifdef STM32F429xx
//   #include "core_cm4.h"
//   #include "stm32f4xx_hal.h"
//#endif /* STM32F429xx */

#ifndef s32
#define s32         int32_t
#endif
#ifndef s16
#define s16         int16_t
#endif
#ifndef s8
#define s8          int8_t
#endif

//typedef int32_t  s32;
//typedef int16_t s16;
//typedef int8_t  s8;

#ifndef sc32
#define sc32         const int32_t    /*!< Read Only */
#endif
#ifndef sc16
#define sc16         const int16_t    /*!< Read Only */
#endif
#ifndef sc8
#define sc8          const int8_t     /*!< Read Only */
#endif

//typedef const int32_t sc32;  /*!< Read Only */
//typedef const int16_t sc16;  /*!< Read Only */
//typedef const int8_t sc8;   /*!< Read Only */

#ifndef vc32
#define vs32        __IO int32_t
#endif
#ifndef vc16
#define vs16        __IO int16_t
#endif
#ifndef vc8
#define vs8         __IO int8_t
#endif

//typedef __IO int32_t  vs32;
//typedef __IO int16_t  vs16;
//typedef __IO int8_t   vs8;

#ifndef vsc32
#define vsc32        __I int32_t   /*!< Read Only */
#endif
#ifndef vsc16
#define vsc16        __I int16_t   /*!< Read Only */
#endif
#ifndef vsc8
#define vsc8         __I int8_t   /*!< Read Only */
#endif

//typedef __I int32_t vsc32;  /*!< Read Only */
//typedef __I int16_t vsc16;  /*!< Read Only */
//typedef __I int8_t vsc8;   /*!< Read Only */

#ifndef u32
#define u32        uint32_t
#endif
#ifndef u16
#define u16        uint16_t
#endif
#ifndef u8
#define u8         uint8_t
#endif

//typedef uint32_t  u32;
//typedef uint16_t u16;
//typedef uint8_t  u8;

#ifndef uc32
#define uc32        const uint32_t   /*!< Read Only */
#endif
#ifndef uc16
#define uc16        const uint16_t   /*!< Read Only */
#endif
#ifndef uc8
#define uc8         const uint8_t   /*!< Read Only */
#endif

//typedef const uint32_t uc32;  /*!< Read Only */
//typedef const uint16_t uc16;  /*!< Read Only */
//typedef const uint8_t uc8;   /*!< Read Only */

#ifndef vu32
#define vu32        __IO uint32_t
#endif
#ifndef vu16
#define vu16        __IO uint16_t
#endif
#ifndef vu8
#define vu8         __IO uint8_t
#endif

//typedef __IO uint32_t  vu32;
//typedef __IO uint16_t vu16;
//typedef __IO uint8_t  vu8;

#ifndef vuc32
#define vuc32        __I uint32_t   /*!< Read Only */
#endif
#ifndef vuc16
#define vuc16        __I uint16_t   /*!< Read Only */
#endif
#ifndef vuc8
#define vuc8         __I uint8_t   /*!< Read Only */
#endif

//typedef __I uint32_t vuc32;  /*!< Read Only */
//typedef __I uint16_t vuc16;  /*!< Read Only */
//typedef __I uint8_t vuc8;   /*!< Read Only */

#define USER_WARNING_REF(x) (void)x; // 防止编译出现未使用警告

// gpio函数重定义 ---> 方便标准库移植
#define GPIO_ReadInputDataBit(gbio_x, gbio_pin_x)  HAL_GPIO_ReadPin(gbio_x, gbio_pin_x)
#define GPIO_SetBits(gbio_x, gbio_pin_x)           HAL_GPIO_WritePin(gbio_x, gbio_pin_x, GPIO_PIN_SET)
#define GPIO_ResetBits(gbio_x, gbio_pin_x)         HAL_GPIO_WritePin(gbio_x, gbio_pin_x, GPIO_PIN_RESET)

// 引脚重定义 ---> 方便标准库移植
#define GPIO_Pin_0   GPIO_PIN_0
#define GPIO_Pin_1   GPIO_PIN_1
#define GPIO_Pin_2   GPIO_PIN_2
#define GPIO_Pin_3   GPIO_PIN_3
#define GPIO_Pin_4   GPIO_PIN_4
#define GPIO_Pin_5   GPIO_PIN_5
#define GPIO_Pin_6   GPIO_PIN_6
#define GPIO_Pin_7   GPIO_PIN_7
#define GPIO_Pin_8   GPIO_PIN_8
#define GPIO_Pin_9   GPIO_PIN_9
#define GPIO_Pin_10  GPIO_PIN_10
#define GPIO_Pin_11  GPIO_PIN_11
#define GPIO_Pin_12  GPIO_PIN_12
#define GPIO_Pin_13  GPIO_PIN_13
#define GPIO_Pin_14  GPIO_PIN_14
#define GPIO_Pin_15  GPIO_PIN_15
#define GPIO_Pin_16  GPIO_PIN_16
#define GPIO_Pin_17  GPIO_PIN_17





#endif

/********************************End of Head************************************/

