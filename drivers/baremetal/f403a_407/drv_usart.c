/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-10     shelton      first version
 */

#include <string.h>
#include <stdlib.h>
#include "at32f403a_407.h"
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

static void get_pin_by_name(const char* pin_name, gpio_type **port, uint16_t *pin)
{
    int pin_num = atoi((char*) &pin_name[2]);
    char port_name = pin_name[1];
    up_char(&port_name);
    up_char(&port_name);
    *port = ((gpio_type *) ((uint32_t) GPIOA
            + (uint32_t) (port_name - 'A') * ((uint32_t) GPIOB - (uint32_t) GPIOA)));
    *pin = (GPIO_PINS_0 << pin_num);
}

const uint8_t __lowest_bit_bitmap[] =
{
    /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
int __rt_ffs(int value)
{
    if (value == 0) return 0;

    if (value & 0xff)
        return __lowest_bit_bitmap[value & 0xff] + 1;

    if (value & 0xff00)
        return __lowest_bit_bitmap[(value & 0xff00) >> 8] + 9;

    if (value & 0xff0000)
        return __lowest_bit_bitmap[(value & 0xff0000) >> 16] + 17;

    return __lowest_bit_bitmap[(value & 0xff000000) >> 24] + 25;
}

static uint16_t at32_get_pin(gpio_type *pin_port, uint32_t pin_num)
{
    return (uint16_t)((16 * (((long)pin_port - (long)GPIOA_BASE)/(0x0400UL))) + (__rt_ffs(pin_num) - 1));
}
static long at32_gpio_configure(struct at32_uart *config)
{
#define UART_IS_TX        (1U<<7)
#define UART_IS_RX        (0U)

    uint16_t tx_pin_num = 0, rx_pin_num = 0;
    int __attribute__((unused)) rx_index = 0, tx_index = 0, index = 0;
    int uart_num = 0;
    int uart_is_remap = 0;
    gpio_type *tx_port;
    gpio_type *rx_port;
    uint16_t tx_pin;
    uint16_t rx_pin;
    get_pin_by_name(config->rx_pin_name, &rx_port, &rx_pin);
    get_pin_by_name(config->tx_pin_name, &tx_port, &tx_pin);

    struct gpio_uart_remap {
        /* index get by GET_PIN */
        uint16_t pin_index;
        /* -1: not uart, 1: uart1, 2: uart2 ... */
        int8_t normal_uart;
        /* -1: not uart, 1: uart1, 2: uart2 ... */
        int8_t remap_uart;
    };

    static const struct gpio_uart_remap uart_remaps[] =
    {
        /* usart1 configure */
        { .pin_index = GET_PIN(A, 9),  .normal_uart =  1, .remap_uart = -1 },
        { .pin_index = GET_PIN(A, 10), .normal_uart =  1, .remap_uart = -1 },
        { .pin_index = GET_PIN(B, 6),  .normal_uart = -1, .remap_uart =  1 },
        { .pin_index = GET_PIN(B, 7),  .normal_uart = -1, .remap_uart =  1 },

        /* usart2 configure */
        { .pin_index = GET_PIN(A, 2),  .normal_uart =  2, .remap_uart = -1 },
        { .pin_index = GET_PIN(A, 3),  .normal_uart =  2, .remap_uart = -1 },
        { .pin_index = GET_PIN(D, 5),  .normal_uart = -1, .remap_uart =  2 },
        { .pin_index = GET_PIN(D, 6),  .normal_uart = -1, .remap_uart =  2 },

        /* usart3 configure */
        { .pin_index = GET_PIN(B, 10), .normal_uart =  3, .remap_uart = -1 },
        { .pin_index = GET_PIN(B, 11), .normal_uart =  3, .remap_uart = -1 },
        { .pin_index = GET_PIN(D, 8),  .normal_uart = -1, .remap_uart =  3 },
        { .pin_index = GET_PIN(D, 9),  .normal_uart = -1, .remap_uart =  3 },

        /* uart4 configure */
        { .pin_index = GET_PIN(C, 10), .normal_uart =  4, .remap_uart = -1 },
        { .pin_index = GET_PIN(C, 11), .normal_uart =  4, .remap_uart = -1 },
        { .pin_index = GET_PIN(A, 0),  .normal_uart = -1, .remap_uart =  4 },
        { .pin_index = GET_PIN(A, 1),  .normal_uart = -1, .remap_uart =  4 },

        /* uart5 configure */
        { .pin_index = GET_PIN(C, 12), .normal_uart =  5, .remap_uart = -1 },
        { .pin_index = GET_PIN(D, 2),  .normal_uart =  5, .remap_uart = -1 },
        { .pin_index = GET_PIN(B, 9),  .normal_uart = -1, .remap_uart =  5 },
        { .pin_index = GET_PIN(B, 8),  .normal_uart = -1, .remap_uart =  5 },

        /* usart6 configure */
        { .pin_index = GET_PIN(C, 6),  .normal_uart =  6, .remap_uart = -1 },
        { .pin_index = GET_PIN(C, 7),  .normal_uart =  6, .remap_uart = -1 },
        { .pin_index = GET_PIN(A, 4),  .normal_uart = -1, .remap_uart =  6 },
        { .pin_index = GET_PIN(A, 5),  .normal_uart = -1, .remap_uart =  6 },

        /* uart7 configure */
        { .pin_index = GET_PIN(E, 8),  .normal_uart =  7, .remap_uart = -1 },
        { .pin_index = GET_PIN(E, 7),  .normal_uart =  7, .remap_uart = -1 },
        { .pin_index = GET_PIN(B, 4),  .normal_uart = -1, .remap_uart =  7 },
        { .pin_index = GET_PIN(B, 3),  .normal_uart = -1, .remap_uart =  7 },

        /* uart8 configure */
        { .pin_index = GET_PIN(E, 1),  .normal_uart =  8, .remap_uart = -1 },
        { .pin_index = GET_PIN(E, 0),  .normal_uart =  8, .remap_uart = -1 },
        { .pin_index = GET_PIN(C, 2),  .normal_uart = -1, .remap_uart =  8 },
        { .pin_index = GET_PIN(C, 3),  .normal_uart = -1, .remap_uart =  8 },
    };
    /* get tx/rx pin index */
    tx_pin_num = at32_get_pin(tx_port, tx_pin);
    rx_pin_num = at32_get_pin(rx_port, rx_pin);

    for (index = 0; index < sizeof(uart_remaps) / sizeof(struct gpio_uart_remap); index++)
    {
        if (uart_remaps[index].pin_index == tx_pin_num)
        {
            tx_index = index;
        }
        else if (uart_remaps[index].pin_index == rx_pin_num)
        {
            rx_index = index;
        }
    }

    uart_num = config->name[4] - '0';
    uart_is_remap = uart_remaps[tx_index].remap_uart == uart_num ? 1 : 0;

    {
        gpio_init_type gpio_init_struct;

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
        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pins = rx_pin;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init(rx_port, &gpio_init_struct);

        /* enable the remapping of usart alternate */
        if (uart_is_remap)
        {
            crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
            switch (uart_num)
            {
            case 1:
                gpio_pin_remap_config(USART1_MUX, TRUE);
                break;
            case 2:
                gpio_pin_remap_config(USART2_MUX, TRUE);
                break;
            case 3:
                gpio_pin_remap_config(USART3_MUX_11, TRUE);
                break;
            case 4:
                gpio_pin_remap_config(UART4_GMUX_0010, TRUE);
                break;
            case 5:
                gpio_pin_remap_config(UART5_GMUX_0001, TRUE);
                break;
            case 6:
                gpio_pin_remap_config(USART6_GMUX, TRUE);
                break;
            case 7:
                gpio_pin_remap_config(SWJTAG_GMUX_010, TRUE);
                gpio_pin_remap_config(UART7_GMUX, TRUE);
                break;
            case 8:
                gpio_pin_remap_config(UART8_GMUX, TRUE);
                break;
            default:
               break;
            }
        }
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
