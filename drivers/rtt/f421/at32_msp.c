/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-16     shelton      first version
 */

#include <rtthread.h>
#include <stdlib.h>
#include "drv_common.h"
#include "drv_usart.h"
#include "at32_msp.h"

void at32_msp_usart_init(void *instance)
{
    gpio_init_type gpio_init_struct;
    usart_type *usart_x = (usart_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_UART1
    if(USART1 == usart_x)
    {
        crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_9;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_10;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE9, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE10, GPIO_MUX_1);
    }
#endif
#ifdef BSP_USING_UART2
    if(USART2 == usart_x)
    {
        crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_2;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_3;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE2, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE3, GPIO_MUX_1);
    }
#endif
    /* add others */
}

void at32_msp_spi_init(void *instance)
{
#if defined (BSP_USING_SPI1) || defined (BSP_USING_SPI2)
    gpio_init_type gpio_init_struct;
    spi_type *spi_x = (spi_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_SPI1
    if(SPI1 == spi_x)
    {
        crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_4;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_6 | GPIO_PINS_7;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE5, GPIO_MUX_0);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE6, GPIO_MUX_0);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE7, GPIO_MUX_0);
    }
#endif
#ifdef BSP_USING_SPI2
    if(SPI2 == spi_x)
    {
        crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_12;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE13, GPIO_MUX_0);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE14, GPIO_MUX_0);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE15, GPIO_MUX_0);
    }
#endif
    /* add others */
#endif
}

void at32_msp_tmr_init(void *instance)
{
#if defined (BSP_USING_PWM1)
    gpio_init_type gpio_init_struct;
    tmr_type *tmr_x = (tmr_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_PWM1
    if(tmr_x == TMR1)
    {
        /* tmr1 clock enable */
        crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
        /* gpioa clock enable */
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        /* gpioa configuration: tmr1 channel1 and channel4 as alternate function push-pull */
        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_11;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE8, GPIO_MUX_2);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE11, GPIO_MUX_2);
    }
#endif
    /* add others */
#endif
}

void at32_msp_adc_init(void *instance)
{
#if defined (BSP_USING_ADC1)
    gpio_init_type gpio_init_struct;
    adc_type *adc_x = (adc_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_ADC1
    if(adc_x == ADC1)
    {
        /* adc1 & gpio clock enable */
        crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        /* configure adc channel as analog input */
        gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_4 | GPIO_PINS_5 | GPIO_PINS_6;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init(GPIOA, &gpio_init_struct);
    }
#endif
    /* add others */
#endif
}

void at32_msp_hwtmr_init(void *instance)
{
#if defined (BSP_USING_HWTMR3)
    tmr_type *tmr_x = (tmr_type *)instance;

#ifdef BSP_USING_HWTMR3
    if(tmr_x == TMR3)
    {
        /* tmr3 clock enable */
        crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
    }
#endif
#endif
}

static rt_err_t at32_uart_clk_enable(usart_type *uart_x)
{
    /* uart clock enable */
    switch ((uint32_t)uart_x)
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
    default:
        return -RT_ERROR;
    }

    return RT_EOK;
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
#if defined(GPIOF)
    case (uint32_t)GPIOF:
        crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
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
    gpio_type *tx_port;
    gpio_type *rx_port;
    gpio_pins_source_type tx_pin_source;
    gpio_pins_source_type rx_pin_source;
    uint16_t tx_pin;
    uint16_t rx_pin;

    get_pin_by_name(config->rx_pin_name, &rx_port, &rx_pin, &rx_pin_source);
    get_pin_by_name(config->tx_pin_name, &tx_port, &tx_pin, &tx_pin_source);

    struct gpio_uart_mux {
        /* index get by GET_PIN */
        uint16_t pin_index;
        /* uart index and attribute */
        uint8_t uart_num;
        /* gpio mux number... */
        uint8_t mux_num;
    };

    static const struct gpio_uart_mux uart_muxs[] =
    {
        /* usart1 configure */
        { .pin_index = GET_PIN(A, 9),  .uart_num = UART_IS_TX|1, .mux_num = 1 },
        { .pin_index = GET_PIN(A, 10), .uart_num = UART_IS_RX|1, .mux_num = 1 },
        { .pin_index = GET_PIN(B, 6),  .uart_num = UART_IS_TX|1, .mux_num = 0 },
        { .pin_index = GET_PIN(B, 7),  .uart_num = UART_IS_RX|1, .mux_num = 0 },

        /* usart2 configure */
        { .pin_index = GET_PIN(A, 2),  .uart_num = UART_IS_TX|2, .mux_num = 1 },
        { .pin_index = GET_PIN(A, 3),  .uart_num = UART_IS_RX|2, .mux_num = 1 },
        { .pin_index = GET_PIN(A, 8),  .uart_num = UART_IS_TX|2, .mux_num = 4 },
        { .pin_index = GET_PIN(B, 0),  .uart_num = UART_IS_RX|2, .mux_num = 3 },
        { .pin_index = GET_PIN(A, 14), .uart_num = UART_IS_TX|2, .mux_num = 1 },
        { .pin_index = GET_PIN(A, 15), .uart_num = UART_IS_RX|2, .mux_num = 1 },
    };
    /* get tx/rx pin index */
    tx_pin_num = at32_get_pin(tx_port, tx_pin);
    rx_pin_num = at32_get_pin(rx_port, rx_pin);

    for (index = 0; index < sizeof(uart_muxs) / sizeof(struct gpio_uart_mux); index++)
    {
        if (uart_muxs[index].pin_index == tx_pin_num)
        {
            tx_index = index;
        }
        else if (uart_muxs[index].pin_index == rx_pin_num)
        {
            rx_index = index;
        }
    }

    uart_num = config->name[4] - '0';

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
        gpio_init_struct.gpio_pins = rx_pin;
        gpio_init(rx_port, &gpio_init_struct);

        /* config gpio mux */
        if(uart_muxs[tx_index].uart_num == (UART_IS_TX | uart_num))
        {
            gpio_pin_mux_config(tx_port, tx_pin_source, uart_muxs[tx_index].mux_num);
        }
        if(uart_muxs[rx_index].uart_num == (UART_IS_RX | uart_num))
        {
            gpio_pin_mux_config(rx_port, rx_pin_source, uart_muxs[rx_index].mux_num);
        }
    }

    return 0;
}

void at32_msp_usart_init(void *instance)
{
    at32_uart_clk_enable(((struct at32_uart *)instance)->uart_x);
    at32_gpio_configure(instance);
}
