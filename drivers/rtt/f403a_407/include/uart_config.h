/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     shelton      first version
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
#define UART3_IRQHandler      USART3_IRQHandler
#define UART4_IRQHandler      UART4_IRQHandler
#define UART5_IRQHandler      UART5_IRQHandler
#define UART6_IRQHandler      USART6_IRQHandler
#define UART7_IRQHandler      UART7_IRQHandler
#define UART8_IRQHandler      UART8_IRQHandler

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

#if defined(BSP_USING_UART3)
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .uart_x = USART3,                                           \
        .irqn = USART3_IRQn,                                        \
        .tx_pin_name = BSP_UART3_TX_PIN,                            \
        .rx_pin_name = BSP_UART3_RX_PIN,                            \
    }

#if defined(BSP_UART3_RX_USING_DMA)
#define UART3_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART3_RX_DMA_CHANNEL,                        \
        .dma_clock = UART3_RX_DMA_CLOCK,                            \
        .dma_irqn = UART3_RX_DMA_IRQ,                               \
    }
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_UART3_TX_USING_DMA)
#define UART3_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART3_TX_DMA_CHANNEL,                        \
        .dma_clock = UART3_TX_DMA_CLOCK,                            \
        .dma_irqn = UART3_TX_DMA_IRQ,                               \
    }
#endif /* BSP_UART3_TX_USING_DMA */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#define UART4_CONFIG                                                \
    {                                                               \
        .name = "uart4",                                            \
        .uart_x = UART4,                                            \
        .irqn = UART4_IRQn,                                         \
        .tx_pin_name = BSP_UART4_TX_PIN,                            \
        .rx_pin_name = BSP_UART4_RX_PIN,                            \
    }

#if defined(BSP_UART4_RX_USING_DMA)
#define UART4_RX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART4_RX_DMA_CHANNEL,                        \
        .dma_clock = UART4_RX_DMA_CLOCK,                            \
        .dma_irqn = UART4_RX_DMA_IRQ,                               \
    }
#endif /* BSP_UART4_RX_USING_DMA */

#if defined(BSP_UART4_TX_USING_DMA)
#define UART4_TX_DMA_CONFIG                                         \
    {                                                               \
        .dma_channel = UART4_TX_DMA_CHANNEL,                        \
        .dma_clock = UART4_TX_DMA_CLOCK,                            \
        .dma_irqn = UART4_TX_DMA_IRQ,                               \
    }
#endif /* BSP_UART4_TX_USING_DMA */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#define UART5_CONFIG                                                \
    {                                                               \
        .name = "uart5",                                            \
        .uart_x = UART5,                                            \
        .irqn = UART5_IRQn,                                         \
        .tx_pin_name = BSP_UART5_TX_PIN,                            \
        .rx_pin_name = BSP_UART5_RX_PIN,                            \
    }
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#define UART6_CONFIG                                                \
    {                                                               \
        .name = "uart6",                                            \
        .uart_x = USART6,                                           \
        .irqn = USART6_IRQn,                                        \
        .tx_pin_name = BSP_UART6_TX_PIN,                            \
        .rx_pin_name = BSP_UART6_RX_PIN,                            \
    }
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
#define UART7_CONFIG                                                \
    {                                                               \
        .name = "uart7",                                            \
        .uart_x = UART7,                                            \
        .irqn = UART7_IRQn,                                         \
        .tx_pin_name = BSP_UART7_TX_PIN,                            \
        .rx_pin_name = BSP_UART7_RX_PIN,                            \
    }
#endif /* BSP_USING_UART7 */

#if defined(BSP_USING_UART8)
#define UART8_CONFIG                                                \
    {                                                               \
        .name = "uart8",                                            \
        .uart_x = UART8,                                            \
        .irqn = UART8_IRQn,                                         \
        .tx_pin_name = BSP_UART8_TX_PIN,                            \
        .rx_pin_name = BSP_UART8_RX_PIN,                            \
    }
#endif /* BSP_USING_UART8 */

#ifdef __cplusplus
}
#endif

#endif
