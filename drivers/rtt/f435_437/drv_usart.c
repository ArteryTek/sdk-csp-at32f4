/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-28     shelton      first version
 */

#include <stdlib.h>
#include "board.h"
#include "drv_usart.h"

#ifdef RT_USING_SERIAL
#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && \
    !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
    #error "Please define at least one BSP_USING_UARTx"
#endif

struct at32_uart {
    char *name;
    usart_type* uart_x;
    IRQn_Type irqn;

    const char *tx_pin_name;
    const char *rx_pin_name;

    struct rt_serial_device serial;
};

enum {
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
#ifdef BSP_USING_UART8
    UART8_INDEX,
#endif
};

static struct at32_uart usart_config[] = {
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

static rt_err_t at32_uart_clk_enable(struct at32_uart *config)
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

static rt_err_t at32_gpio_configure(struct at32_uart *config)
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

    return RT_EOK;
}

static rt_err_t at32_configure(struct rt_serial_device *serial,
    struct serial_configure *cfg) {
    struct at32_uart *uart_instance = (struct at32_uart *) serial->parent.user_data;
    usart_data_bit_num_type data_bit;
    usart_stop_bit_num_type stop_bit;
    usart_parity_selection_type parity_mode;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    RT_ASSERT(uart_instance != RT_NULL);

    at32_uart_clk_enable(uart_instance);
	at32_gpio_configure(uart_instance);

    usart_receiver_enable(uart_instance->uart_x, TRUE);
    usart_transmitter_enable(uart_instance->uart_x, TRUE);

    usart_hardware_flow_control_set(uart_instance->uart_x, USART_HARDWARE_FLOW_NONE);

    switch (cfg->data_bits) {
    case DATA_BITS_8:
        data_bit = USART_DATA_8BITS;
        break;
    case DATA_BITS_9:
        data_bit = USART_DATA_9BITS;
        break;
    default:
        data_bit = USART_DATA_8BITS;
        break;
    }

    switch (cfg->stop_bits) {
    case STOP_BITS_1:
        stop_bit = USART_STOP_1_BIT;
        break;
    case STOP_BITS_2:
        stop_bit = USART_STOP_2_BIT;
        break;
    default:
        stop_bit = USART_STOP_1_BIT;
        break;
    }

    switch (cfg->parity) {
    case PARITY_NONE:
        parity_mode = USART_PARITY_NONE;
        break;
    case PARITY_ODD:
        parity_mode = USART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        parity_mode = USART_PARITY_EVEN;
        break;
    default:
        parity_mode = USART_PARITY_NONE;
        break;
    }
    usart_parity_selection_config(uart_instance->uart_x, parity_mode);
    usart_init(uart_instance->uart_x, cfg->baud_rate, data_bit, stop_bit);
    usart_enable(uart_instance->uart_x, TRUE);

    return RT_EOK;
}

static rt_err_t at32_control(struct rt_serial_device *serial, int cmd, void *arg) {
    struct at32_uart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_uart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        nvic_irq_disable(usart->irqn);
        usart_interrupt_enable(usart->uart_x, USART_RDBF_INT, FALSE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        nvic_irq_enable(usart->irqn, 2, 1);
        usart_interrupt_enable(usart->uart_x, USART_RDBF_INT, TRUE);
        break;
    }

    return RT_EOK;
}

static int at32_putc(struct rt_serial_device *serial, char ch) {
    struct at32_uart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_uart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    usart_data_transmit(usart->uart_x, (uint8_t)ch);
    while (usart_flag_get(usart->uart_x, USART_TDC_FLAG) == RESET);

    return 1;
}

static int at32_getc(struct rt_serial_device *serial) {
    int ch;
    struct at32_uart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_uart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (usart_flag_get(usart->uart_x, USART_RDBF_FLAG) != RESET) {
        ch = usart_data_receive(usart->uart_x) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops at32_uart_ops = {
    at32_configure,
    at32_control,
    at32_putc,
    at32_getc,
    RT_NULL
};

static void usart_isr(struct rt_serial_device *serial) {
    struct at32_uart *uart_instance;

    RT_ASSERT(serial != RT_NULL);

    uart_instance = (struct at32_uart *) serial->parent.user_data;
    RT_ASSERT(uart_instance != RT_NULL);

    if (usart_flag_get(uart_instance->uart_x, USART_RDBF_FLAG) != RESET) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else
    {
        if (usart_flag_get(uart_instance->uart_x, USART_CTSCF_FLAG) != RESET) {
            usart_flag_clear(uart_instance->uart_x, USART_CTSCF_FLAG);
        }

        if (usart_flag_get(uart_instance->uart_x, USART_BFF_FLAG) != RESET) {
            usart_flag_clear(uart_instance->uart_x, USART_BFF_FLAG);
        }

        if (usart_flag_get(uart_instance->uart_x, USART_TDC_FLAG) != RESET) {
            usart_flag_clear(uart_instance->uart_x, USART_TDC_FLAG);
        }
    }
}

#ifdef BSP_USING_UART1
void USART1_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[UART1_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
void USART2_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[UART2_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART3
void USART3_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[UART3_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART4
void UART4_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[UART4_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART5
void UART5_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[UART5_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART6
void USART6_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[UART6_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART7
void UART7_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[UART7_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART8
void UART8_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[UART8_INDEX].serial);

    rt_interrupt_leave();
}
#endif

int rt_hw_usart_init(void) {
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(usart_config) / sizeof(struct at32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++) {
        usart_config[index].serial.ops = &at32_uart_ops;
        usart_config[index].serial.config = config;

        /* register uart device */
        result = rt_hw_serial_register(&usart_config[index].serial,
                 usart_config[index].name,
                 RT_DEVICE_FLAG_RDWR |
                 RT_DEVICE_FLAG_INT_RX |
                 RT_DEVICE_FLAG_INT_TX,
                 &usart_config[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* BSP_USING_SERIAL */
