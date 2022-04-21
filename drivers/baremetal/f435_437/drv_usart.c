/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-18     shelton      first version
 */

#include <string.h>
#include <stdlib.h>
#include "at32f435_437.h"
#include "board.h"

#define __AT32_PORT(port)  GPIO##port##_BASE
#define GET_PIN(PORTx,PIN) (long)((16 * ( ((long)__AT32_PORT(PORTx) - (long)GPIOA_BASE)/(0x0400UL) )) + PIN)

/* at32 config class */
struct at32_uart
{
    const char *name;
    usart_type *uart_x;
    IRQn_Type irqn;

    const char *tx_pin_name;
    const char *rx_pin_name;
};

static struct at32_uart *_uart_config = NULL;

struct at32_uart uart_config[] =
{
#ifdef BSP_USING_UART1
        { "uart1",
        USART1,
        USART1_IRQn, 
        BSP_UART1_TX_PIN,
        BSP_UART1_RX_PIN },
#endif
#ifdef BSP_USING_UART2
        { "uart2",
        USART2,
        USART2_IRQn, 
        BSP_UART2_TX_PIN,
        BSP_UART2_RX_PIN },
#endif
#ifdef BSP_USING_UART3
        { "uart3",
        USART3,
        USART3_IRQn, 
        BSP_UART3_TX_PIN,
        BSP_UART3_RX_PIN },
#endif
#ifdef BSP_USING_UART4
        { "uart4",
        UART4,
        UART4_IRQn, 
        BSP_UART4_TX_PIN,
        BSP_UART4_RX_PIN },
#endif
#ifdef BSP_USING_UART5
        { "uart5",
        UART5,
        UART5_IRQn, 
        BSP_UART5_TX_PIN,
        BSP_UART5_RX_PIN },
#endif
#ifdef BSP_USING_UART6
        { "uart6",
        USART6,
        USART6_IRQn, 
        BSP_UART6_TX_PIN,
        BSP_UART6_RX_PIN },
#endif
#ifdef BSP_USING_UART7
        { "uart7",
        UART7,
        UART7_IRQn, 
        BSP_UART7_TX_PIN,
        BSP_UART7_RX_PIN },
#endif
#ifdef BSP_USING_UART8
        { "uart8",
        UART8,
        UART8_IRQn, 
        BSP_UART8_TX_PIN,
        BSP_UART8_RX_PIN },
#endif
};

static long at32_uart_clk_enable(struct at32_uart *config)
{
    /* uart clock enable */
    switch ((uint32_t)config->uart_x)
    {
#ifdef BSP_USING_UART1
    case (uint32_t)USART1:
        crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART1 */
#ifdef BSP_USING_UART2
    case (uint32_t)USART2:
        crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART2 */
#ifdef BSP_USING_UART3
    case (uint32_t)USART3:
        crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART3 */
#ifdef BSP_USING_UART4
    case (uint32_t)UART4:
        crm_periph_clock_enable(CRM_UART4_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART4 */
#ifdef BSP_USING_UART5
    case (uint32_t)UART5:
        crm_periph_clock_enable(CRM_UART5_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART5 */
#ifdef BSP_USING_UART6
    case (uint32_t)USART6:
        crm_periph_clock_enable(CRM_USART6_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART6 */
#ifdef BSP_USING_UART7
    case (uint32_t)UART7:
        crm_periph_clock_enable(CRM_UART7_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART7 */
#ifdef BSP_USING_UART8
    case (uint32_t)UART8:
        crm_periph_clock_enable(CRM_UART8_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART8 */
    default:
        return -1;
    }

    return 0;
}

static long at32_gpio_clk_enable(gpio_type *gpio_x)
{
    /* gpio ports clock enable */
    switch ((uint32_t)gpio_x)
    {
#if defined(GPIOA)
    case (uint32_t)GPIOA:
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
        break;
#endif
#if defined(GPIOB)
    case (uint32_t)GPIOB:
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
        break;
#endif
#if defined(GPIOC)
    case (uint32_t)GPIOC:
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
        break;
#endif
#if defined(GPIOD)
    case (uint32_t)GPIOD:
        crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
        break;
#endif
#if defined(GPIOE)
    case (uint32_t)GPIOE:
        crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
        break;
#endif
#if defined(GPIOF)
    case (uint32_t)GPIOF:
        crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
        break;
#endif
#if defined(GPIOG)
    case (uint32_t)GPIOG:
        crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);
        break;
#endif
#if defined(GPIOH)
    case (uint32_t)GPIOH:
        crm_periph_clock_enable(CRM_GPIOH_PERIPH_CLOCK, TRUE);
        break;
#endif
    default:
        return -1;
    }

    return 0;
}

static int up_char(char * c)
{
    if ((*c >= 'a') && (*c <= 'z'))
    {
        *c = *c - 32;
    }
    return 0;
}

static void get_pin_by_name(const char* pin_name, gpio_type **port, uint16_t *pin, gpio_pins_source_type *pin_source)
{
    int pin_num = atoi((char*) &pin_name[2]);
    char port_name = pin_name[1];
    up_char(&port_name);
    up_char(&port_name);
    *port = ((gpio_type *) ((uint32_t) GPIOA
            + (uint32_t) (port_name - 'A') * ((uint32_t) GPIOB - (uint32_t) GPIOA)));
    *pin = (GPIO_PINS_0 << pin_num);
    *pin_source = (gpio_pins_source_type)pin_num;
}

static long at32_gpio_configure(struct at32_uart *config)
{
    gpio_init_type gpio_init_struct;
    int uart_num = 0;
    gpio_type *tx_port;
    gpio_type *rx_port;
    gpio_pins_source_type tx_pin_source;
    gpio_pins_source_type rx_pin_source;
    uint16_t tx_pin;
    uint16_t rx_pin;

    get_pin_by_name(config->tx_pin_name, &tx_port, &tx_pin, &tx_pin_source);
    get_pin_by_name(config->rx_pin_name, &rx_port, &rx_pin, &rx_pin_source);

    uart_num = config->name[4] - '0';

    /* gpio ports clock enable */
    at32_gpio_clk_enable(tx_port);
    if (tx_port != rx_port)
    {
        at32_gpio_clk_enable(rx_port);
    }

    /* tx pin initialize */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = tx_pin;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(tx_port, &gpio_init_struct);

    /* rx pin initialize */
    gpio_init_struct.gpio_pins = rx_pin;
    gpio_init(rx_port, &gpio_init_struct);

    /* config gpio mux number */
    if(uart_num < 4)
    {
        gpio_pin_mux_config(tx_port, tx_pin_source, GPIO_MUX_7);
        gpio_pin_mux_config(rx_port, rx_pin_source, GPIO_MUX_7);
    }
    else
    {
        gpio_pin_mux_config(tx_port, tx_pin_source, GPIO_MUX_8);
        gpio_pin_mux_config(rx_port, rx_pin_source, GPIO_MUX_8);
    }

    return 0;
}

static long at32_configure(struct at32_uart *config)
{
    /* enable usart periph clock */
    at32_uart_clk_enable(config);

    /* config uart */
    usart_init(config->uart_x, 115200, USART_DATA_8BITS, USART_STOP_1_BIT);
    usart_hardware_flow_control_set(config->uart_x, USART_HARDWARE_FLOW_NONE);
    usart_transmitter_enable(config->uart_x, TRUE);
    usart_receiver_enable(config->uart_x, TRUE);
    usart_interrupt_enable(config->uart_x, USART_RDBF_INT, TRUE);

    /* enable uart */
    usart_enable(config->uart_x, TRUE);

    return 0;
}

int rt_hw_usart_init(void)
{
    _uart_config = &uart_config[0];

    at32_gpio_configure(_uart_config);

    at32_configure(_uart_config);

    return 0;
}


void print_char(char c)
{
    usart_data_transmit(_uart_config->uart_x, c);
    while(usart_flag_get(_uart_config->uart_x, USART_TDC_FLAG) == RESET);
}
