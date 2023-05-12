/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-16     shelton      first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include "dma_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART1_IRQHandler      USART1_IRQHandler
#define UART2_IRQHandler      USART2_IRQHandler

#if defined(BSP_USING_UART1)
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .uart_x = USART1,                                           \
        .irqn = USART1_IRQn,                                        \
        .tx_pin_name = BSP_UART1_TX_PIN,                            \
        .rx_pin_name = BSP_UART1_RX_PIN,                            \
    }

#if defined(BSP_UART1_RX_USING_DMA)
#define UART1_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART1_RX_DMA_CHANNEL,                        \
        .dma_clock = UART1_RX_DMA_CLOCK,                            \
        .dma_irqn = UART1_RX_DMA_IRQ,                               \
    }
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#define UART1_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART1_TX_DMA_CHANNEL,                        \
        .dma_clock = UART1_TX_DMA_CLOCK,                            \
        .dma_irqn = UART1_TX_DMA_IRQ,                               \
    }
#endif /* BSP_UART1_TX_USING_DMA */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .uart_x = USART2,                                           \
        .irqn = USART2_IRQn,                                        \
        .tx_pin_name = BSP_UART2_TX_PIN,                            \
        .rx_pin_name = BSP_UART2_RX_PIN,                            \
    }

#if defined(BSP_UART2_RX_USING_DMA)
#define UART2_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART2_RX_DMA_CHANNEL,                        \
        .dma_clock = UART2_RX_DMA_CLOCK,                            \
        .dma_irqn = UART2_RX_DMA_IRQ,                               \
    }
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#define UART2_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART2_TX_DMA_CHANNEL,                        \
        .dma_clock = UART2_TX_DMA_CLOCK,                            \
        .dma_irqn = UART2_TX_DMA_IRQ,                               \
    }
#endif /* BSP_UART2_TX_USING_DMA */
#endif /* BSP_USING_UART2 */

#ifdef __cplusplus
}
#endif

#endif
