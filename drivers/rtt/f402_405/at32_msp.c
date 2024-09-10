/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-16     shelton      first version
 */

#include <rtthread.h>
#include <stdlib.h>
#include "drv_common.h"
#include "drv_usart.h"
#include "at32_msp.h"

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

        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_6 | GPIO_PINS_7;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE5, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE6, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE7, GPIO_MUX_5);
    }
#endif
#ifdef BSP_USING_SPI2
    if(SPI2 == spi_x)
    {
        crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_2 | GPIO_PINS_3 | GPIO_PINS_7;
        gpio_init(GPIOC, &gpio_init_struct);

        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE2, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE3, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE7, GPIO_MUX_5);
    }
#endif
    /* add others */
#endif
}

void at32_msp_i2c_init(void *instance)
{
#if defined (BSP_USING_HARD_I2C1) || defined (BSP_USING_HARD_I2C2) || \
    defined (BSP_USING_HARD_I2C3)
    gpio_init_type gpio_init_struct;
    i2c_type *i2c_x = (i2c_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_HARD_I2C1
    if(I2C1 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE7, GPIO_MUX_4);
    }
#endif
#ifdef BSP_USING_HARD_I2C2
    if(I2C2 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_3 | GPIO_PINS_10;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE3, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE10, GPIO_MUX_4);
    }
#endif
#ifdef BSP_USING_HARD_I2C3
    if(I2C3 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C3_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8;
        gpio_init(GPIOA, &gpio_init_struct);
        gpio_init_struct.gpio_pins = GPIO_PINS_9;
        gpio_init(GPIOC, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE8, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE9, GPIO_MUX_4);
    }
#endif
    /* add others */
#endif
}

void at32_msp_tmr_init(void *instance)
{
#if defined (BSP_USING_PWM1) || defined (BSP_USING_PWM2)
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

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE8, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE11, GPIO_MUX_1);
    }
#endif
#ifdef BSP_USING_PWM2
    if(tmr_x == TMR2)
    {
        /* tmr2 clock enable */
        crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
        /* gpioa clock enable */
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        /* gpioa configuration: tmr1 channel1 and channel2 as alternate function push-pull */
        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE0, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE1, GPIO_MUX_1);
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
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

        /* configure adc channel as analog input */
        gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_2 | GPIO_PINS_3 | GPIO_PINS_4 | GPIO_PINS_5;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init(GPIOC, &gpio_init_struct);
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

void at32_msp_qspi_init(void *instance)
{
#if defined (BSP_USING_QSPI1)
    gpio_init_type gpio_init_struct;
    qspi_type *qspi_x = (qspi_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_QSPI1
    if(qspi_x == QSPI1)
    {
        crm_periph_clock_enable(CRM_QSPI1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_2 | GPIO_PINS_7;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_11;
        gpio_init(GPIOC, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE2, GPIO_MUX_11);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE7, GPIO_MUX_11);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE5, GPIO_MUX_11);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE8, GPIO_MUX_11);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE9, GPIO_MUX_11);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE11, GPIO_MUX_11);
    }
#endif
#endif
}

void at32_msp_can_init(void *instance)
{
#if defined (BSP_USING_CAN1)
    gpio_init_type gpio_init_struct;
    can_type *can_x = (can_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_CAN1
    if(CAN1 == can_x)
    {
        crm_periph_clock_enable(CRM_CAN1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_9;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE8, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE9, GPIO_MUX_9);
    }
#endif
#ifdef BSP_USING_CAN2
    if(can_x == CAN2)
    {
        crm_periph_clock_enable(CRM_CAN2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_6;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE5, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_9);
    }
#endif
#endif
}

static long at32_uart_clk_enable(usart_type *uart_x)
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
#ifdef BSP_USING_UART3
    case (uint32_t)USART3:
        crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART3 */
#ifdef BSP_USING_UART4
    case (uint32_t)USART4:
        crm_periph_clock_enable(CRM_USART4_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART4 */
#ifdef BSP_USING_UART5
    case (uint32_t)USART5:
        crm_periph_clock_enable(CRM_USART5_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART5 */
#ifdef BSP_USING_UART6
    case (uint32_t)USART6:
        crm_periph_clock_enable(CRM_USART6_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART6 */
#ifdef BSP_USING_UART7
    case (uint32_t)USART7:
        crm_periph_clock_enable(CRM_USART7_PERIPH_CLOCK, TRUE);
        break;
#endif /* BSP_USING_UART7 */
#ifdef BSP_USING_UART8
    case (uint32_t)USART8:
        crm_periph_clock_enable(CRM_USART8_PERIPH_CLOCK, TRUE);
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
        { .pin_index = GET_PIN(A, 9),  .uart_num = UART_IS_TX|1, .mux_num = 7 },
        { .pin_index = GET_PIN(A, 10), .uart_num = UART_IS_RX|1, .mux_num = 7 },
        { .pin_index = GET_PIN(A, 15), .uart_num = UART_IS_TX|1, .mux_num = 7 },
        { .pin_index = GET_PIN(B, 3),  .uart_num = UART_IS_RX|1, .mux_num = 7 },
        { .pin_index = GET_PIN(B, 6),  .uart_num = UART_IS_TX|1, .mux_num = 7 },
        { .pin_index = GET_PIN(B, 7),  .uart_num = UART_IS_RX|1, .mux_num = 7 },
        { .pin_index = GET_PIN(B, 8),  .uart_num = UART_IS_TX|1, .mux_num = 7 },

        /* usart2 configure */
        { .pin_index = GET_PIN(A, 2),  .uart_num = UART_IS_TX|2, .mux_num = 7 },
        { .pin_index = GET_PIN(A, 0),  .uart_num = UART_IS_RX|2, .mux_num = 6 },
        { .pin_index = GET_PIN(A, 8),  .uart_num = UART_IS_TX|2, .mux_num = 8 },
        { .pin_index = GET_PIN(A, 3),  .uart_num = UART_IS_RX|2, .mux_num = 7 },
        { .pin_index = GET_PIN(A, 14), .uart_num = UART_IS_TX|2, .mux_num = 8 },
        { .pin_index = GET_PIN(B, 0),  .uart_num = UART_IS_RX|2, .mux_num = 7 },

        /* usart3 configure */
        { .pin_index = GET_PIN(A, 7),  .uart_num = UART_IS_TX|3, .mux_num = 7 },
        { .pin_index = GET_PIN(A, 6),  .uart_num = UART_IS_RX|3, .mux_num = 8 },
        { .pin_index = GET_PIN(B, 10), .uart_num = UART_IS_TX|3, .mux_num = 7 },
        { .pin_index = GET_PIN(B, 11), .uart_num = UART_IS_RX|3, .mux_num = 7 },
        { .pin_index = GET_PIN(C, 4),  .uart_num = UART_IS_TX|3, .mux_num = 7 },
        { .pin_index = GET_PIN(C, 5),  .uart_num = UART_IS_RX|3, .mux_num = 7 },

        /* usart4 configure */
        { .pin_index = GET_PIN(C, 10), .uart_num = UART_IS_TX|4, .mux_num = 8 },
        { .pin_index = GET_PIN(A, 1),  .uart_num = UART_IS_RX|4, .mux_num = 8 },
        { .pin_index = GET_PIN(C, 11), .uart_num = UART_IS_RX|4, .mux_num = 8 },

        /* usart5 configure */
        { .pin_index = GET_PIN(B, 9),  .uart_num = UART_IS_TX|5, .mux_num = 8 },
        { .pin_index = GET_PIN(B, 4),  .uart_num = UART_IS_RX|5, .mux_num = 10},
        { .pin_index = GET_PIN(C, 12), .uart_num = UART_IS_TX|5, .mux_num = 10},
        { .pin_index = GET_PIN(B, 5),  .uart_num = UART_IS_RX|5, .mux_num = 8 },

        /* usart6 configure */
        { .pin_index = GET_PIN(A, 4),  .uart_num = UART_IS_TX|6, .mux_num = 8 },
        { .pin_index = GET_PIN(A, 5),  .uart_num = UART_IS_RX|6, .mux_num = 8 },
        { .pin_index = GET_PIN(A, 11), .uart_num = UART_IS_TX|6, .mux_num = 8 },
        { .pin_index = GET_PIN(A, 12), .uart_num = UART_IS_RX|6, .mux_num = 8 },
        { .pin_index = GET_PIN(C, 7),  .uart_num = UART_IS_RX|6, .mux_num = 8 },

        /* usart7 configure */
        { .pin_index = GET_PIN(C, 0),  .uart_num = UART_IS_TX|7, .mux_num = 9 },
        { .pin_index = GET_PIN(C, 1),  .uart_num = UART_IS_RX|7, .mux_num = 9 },
        { .pin_index = GET_PIN(F, 7),  .uart_num = UART_IS_TX|7, .mux_num = 9 },
        { .pin_index = GET_PIN(F, 6),  .uart_num = UART_IS_RX|7, .mux_num = 9 },

        /* usart8 configure */
        { .pin_index = GET_PIN(C, 2),  .uart_num = UART_IS_TX|8, .mux_num = 8 },
        { .pin_index = GET_PIN(C, 3),  .uart_num = UART_IS_RX|8, .mux_num = 8 },
        { .pin_index = GET_PIN(C, 8),  .uart_num = UART_IS_TX|8, .mux_num = 7 },
        { .pin_index = GET_PIN(C, 9),  .uart_num = UART_IS_RX|8, .mux_num = 7 },
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

void at32_msp_usb_init(void *instance)
{
#if defined (BSP_USING_HOST_USBOTG1) || defined (BSP_USING_DEVICE_USBOTG1) || \
    defined (BSP_USING_HOST_USBOTG2) || defined (BSP_USING_DEVICE_USBOTG2)
    /* defalut usb clock from hext */
    usb_clk48_s clk_s = USB_CLK_HEXT;

    crm_periph_clock_enable(CRM_OTGFS1_PERIPH_CLOCK, TRUE);

#if defined (BSP_USING_HOST_USBOTG2) || defined (BSP_USING_DEVICE_USBOTG2)
    crm_periph_clock_enable(CRM_OTGHS_PERIPH_CLOCK, TRUE);
#endif

    if(clk_s == USB_CLK_HICK)
    {
        crm_usb_clock_source_select(CRM_USB_CLOCK_SOURCE_HICK);

        /* enable the acc calibration ready interrupt */
        crm_periph_clock_enable(CRM_ACC_PERIPH_CLOCK, TRUE);

        /* update the c1\c2\c3 value */
        acc_write_c1(7980);
        acc_write_c2(8000);
        acc_write_c3(8020);

        /* open acc calibration */
        acc_calibration_mode_enable(ACC_CAL_HICKTRIM, TRUE);
    }
    else
    {
        /* attention: pllu divider is set at board.c */
        /* enable pllu clock output */
        crm_pllu_output_set(TRUE);
        /* wait till pllu is ready */
        while(crm_flag_get(CRM_PLLU_STABLE_FLAG) == RESET)
        {
        }
        crm_usb_clock_source_select(CRM_USB_CLOCK_SOURCE_PLLU);
    }
#endif /* BSP_USING_USBOTG */
}
