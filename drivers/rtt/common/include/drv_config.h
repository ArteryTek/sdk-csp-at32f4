/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     shelton      first version
 * 2023-01-31     shelton      add support f421/f425
 * 2023-04-08     shelton      add support f423
 * 2023-10-18     shelton      add support f402/f405
 * 2024-04-12     shelton      add support a403a and a423
 * 2024-07-31     shelton      add support hwi2c driver
 * 2024-08-30     shelton      add support m412 and m416
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <board.h>
#include <rtthread.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_AT32A403A)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#include "dac_config.h"
#elif defined(SOC_SERIES_AT32A423)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#include "dac_config.h"
#elif defined(SOC_SERIES_AT32F402) || defined (SOC_SERIES_AT32F405)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#elif defined(SOC_SERIES_AT32F403A) || defined (SOC_SERIES_AT32F407)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#include "dac_config.h"
#elif defined(SOC_SERIES_AT32F413)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#elif defined(SOC_SERIES_AT32F415)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#elif defined(SOC_SERIES_AT32F421)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#elif defined(SOC_SERIES_AT32F423)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#include "dac_config.h"
#elif defined(SOC_SERIES_AT32F425)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#elif defined(SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437)
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#include "dac_config.h"
#elif defined(SOC_SERIES_AT32F455) || defined (SOC_SERIES_AT32F456) || \
      defined(SOC_SERIES_AT32F457)
#include "can_config.h"
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "usb_config.h"
#include "dac_config.h"
#elif defined(SOC_SERIES_AT32M412) || defined (SOC_SERIES_AT32M416)
#include "can_config.h"
#include "dma_config.h"
#include "uart_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "dac_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
