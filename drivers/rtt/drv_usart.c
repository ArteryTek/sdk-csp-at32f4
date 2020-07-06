/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-06     shelton      first version
 */

#include <board.h>
#include "stdlib.h"
#include "drv_usart.h"

#ifdef RT_USING_SERIAL
#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && \
	!defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
	!defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig ¡ú RT-Thread Components ¡ú Device Drivers */
#endif

struct at32_uart_config {
    char *name;
    USART_Type* usartx;
    IRQn_Type irqn;

    const char *tx_pin_name;
    const char *rx_pin_name;

    struct rt_serial_device serial;
};

enum
{
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
struct at32_uart_config uart_config[] =
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

static rt_err_t at32_uart_clk_enable(struct at32_uart_config *config)
{
    /* uart clock enable */
    switch ((uint32_t)config->usartx)
    {
#ifdef BSP_USING_UART1
    case (uint32_t)USART1:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_USART1, ENABLE);
        break;
#endif /* BSP_USING_UART1 */
#ifdef BSP_USING_UART2
    case (uint32_t)USART2:
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART2, ENABLE);
        break;
#endif /* BSP_USING_UART2 */
#ifdef BSP_USING_UART3
    case (uint32_t)USART3:
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART3, ENABLE);
        break;
#endif /* BSP_USING_UART3 */
#ifdef BSP_USING_UART4
    case (uint32_t)UART4:
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_UART4, ENABLE);
        break;
#endif /* BSP_USING_UART4 */
#ifdef BSP_USING_UART5
    case (uint32_t)UART5:
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_UART5, ENABLE);
        break;
#endif /* BSP_USING_UART5 */
#ifdef BSP_USING_UART6
    case (uint32_t)USART6:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_USART6, ENABLE);
        break;
#endif /* BSP_USING_UART6 */
#ifdef BSP_USING_UART7
    case (uint32_t)UART7:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_UART7, ENABLE);
        break;
#endif /* BSP_USING_UART7 */
#ifdef BSP_USING_UART8
    case (uint32_t)UART8:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_UART8, ENABLE);
        break;
#endif /* BSP_USING_UART8 */
    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static long at32_gpio_clk_enable(GPIO_Type *gpiox)
{
    /* gpio ports clock enable */
    switch ((uint32_t)gpiox)
    {
#if defined(GPIOA)
    case (uint32_t)GPIOA:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);
        break;
#endif
#if defined(GPIOB)
    case (uint32_t)GPIOB:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOB, ENABLE);
        break;
#endif
#if defined(GPIOC)
    case (uint32_t)GPIOC:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOC, ENABLE);
        break;
#endif
#if defined(GPIOD)
    case (uint32_t)GPIOD:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOD, ENABLE);
        break;
#endif
#if defined(GPIOE)
    case (uint32_t)GPIOE:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOE, ENABLE);
        break;
#endif
#if defined(GPIOF)
    case (uint32_t)GPIOF:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOF, ENABLE);
        break;
#endif
#if defined(GPIOG)
    case (uint32_t)GPIOG:
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOG, ENABLE);
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

static void get_pin_by_name(const char* pin_name, GPIO_Type **port, uint16_t *pin)
{
    int pin_num = atoi((char*) &pin_name[2]);
    char port_name = pin_name[1];
    up_char(&port_name);
    up_char(&port_name);
    *port = ((GPIO_Type *) ((uint32_t) GPIOA
            + (uint32_t) (port_name - 'A') * ((uint32_t) GPIOB - (uint32_t) GPIOA)));
    *pin = (GPIO_Pins_0 << pin_num);
}

static uint16_t at32_get_pin(GPIO_Type *pin_port, rt_uint32_t pin_num)
{
    return (uint16_t)((16 * (((rt_base_t)pin_port - (rt_base_t)GPIOA_BASE)/(0x0400UL))) + (__rt_ffs(pin_num) - 1));
}

static rt_err_t at32_gpio_configure(struct at32_uart_config *config)
{
#define UART_IS_TX        (1U<<7)
#define UART_IS_RX        (0U)

    rt_uint16_t tx_pin_num = 0, rx_pin_num = 0;
    int rx_index = 0, tx_index = 0, index = 0;
    int uart_num = 0;
    rt_bool_t uart_is_remap = 0;
    GPIO_Type *tx_port;
    GPIO_Type *rx_port;
    uint16_t tx_pin;
    uint16_t rx_pin;
    get_pin_by_name(config->rx_pin_name, &rx_port, &rx_pin);
    get_pin_by_name(config->tx_pin_name, &tx_port, &tx_pin);

    struct gpio_uart_remap {
        /* index get by GET_PIN */
        rt_uint16_t pin_index;
        /* -1: not uart, 1: uart1, 2: uart2 ... */
        rt_int8_t normal_uart;
        /* -1: not uart, 1: uart1, 2: uart2 ... */
        rt_int8_t remap_uart;
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
        { .pin_index = GET_PIN(C, 10), .normal_uart =  4, .remap_uart =  3 },
        { .pin_index = GET_PIN(C, 11), .normal_uart =  4, .remap_uart =  3 },
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

    RT_ASSERT(uart_remaps[tx_index].normal_uart == uart_remaps[rx_index].normal_uart);
    RT_ASSERT(uart_remaps[tx_index].remap_uart == uart_remaps[rx_index].remap_uart);

    uart_num = config->name[4] - '0';
    uart_is_remap = uart_remaps[tx_index].remap_uart == uart_num ? 1 : 0;

    {

        GPIO_InitType GPIO_InitStruct = {0};

        /* gpio ports clock enable */
        at32_gpio_clk_enable(tx_port);
        if (tx_port != rx_port)
        {
            at32_gpio_clk_enable(rx_port);
        }

        /* tx pin initialize */
        GPIO_InitStruct.GPIO_Pins = tx_pin;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
        GPIO_Init(tx_port, &GPIO_InitStruct);

        /* rx pin initialize */
        GPIO_InitStruct.GPIO_Pins = rx_pin;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(rx_port, &GPIO_InitStruct);

        /* enable the remapping of usart alternate */
        if (uart_is_remap)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_AFIO, ENABLE);
            switch (uart_num)
            {
            case 1:
                GPIO_PinsRemapConfig(GPIO_Remap_USART1, ENABLE);
                break;
            case 2:
                GPIO_PinsRemapConfig(GPIO_Remap_USART2, ENABLE);
                break;
            case 3:
                if (uart_remaps[tx_index].normal_uart < 0)
                {
#ifdef GPIO_FullRemap_USART3
                    GPIO_PinsRemapConfig(GPIO_FullRemap_USART3, ENABLE);
#endif
                }
                else
                {
#ifdef GPIO_PartialRemap_USART3
                    GPIO_PinsRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
#endif
                }
                break;
            default:
               RT_ASSERT(0);
            }
        }
    }

    return RT_EOK;
}

static rt_err_t at32_configure(struct rt_serial_device *serial,
        struct serial_configure *cfg) {

    USART_InitType USART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    struct at32_uart_config *usart_instance = (struct at32_uart_config *) serial->parent.user_data;

    RT_ASSERT(usart_instance != RT_NULL);

	at32_uart_clk_enable(usart_instance);

    at32_gpio_configure(usart_instance);

    USART_StructInit(&USART_InitStructure);

    USART_Reset(usart_instance->usartx);
    USART_InitStructure.USART_BaudRate = cfg->baud_rate;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    switch (cfg->data_bits) {
    case DATA_BITS_8:
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        break;

    case DATA_BITS_9:
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
        break;
    default:
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        break;
    }

    switch (cfg->stop_bits) {
    case STOP_BITS_1:
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        break;
    case STOP_BITS_2:
        USART_InitStructure.USART_StopBits = USART_StopBits_2;
        break;
    default:
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        break;
    }

    switch (cfg->parity) {
    case PARITY_NONE:
        USART_InitStructure.USART_Parity = USART_Parity_No;
        break;
    case PARITY_ODD:
        USART_InitStructure.USART_Parity = USART_Parity_Odd;
        break;
    case PARITY_EVEN:
        USART_InitStructure.USART_Parity = USART_Parity_Even;
        break;
    default:
        USART_InitStructure.USART_Parity = USART_Parity_No;
        break;
    }
    USART_Init(usart_instance->usartx, &USART_InitStructure);
    USART_Cmd(usart_instance->usartx, ENABLE);

    return RT_EOK;
}

static rt_err_t at32_control(struct rt_serial_device *serial, int cmd,
        void *arg) {
    struct at32_uart_config *usart;

    NVIC_InitType NVIC_InitStruct;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_uart_config *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    NVIC_InitStruct.NVIC_IRQChannel = usart->irqn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;

    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStruct);
        USART_INTConfig(usart->usartx, USART_INT_RDNE, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
        USART_INTConfig(usart->usartx, USART_INT_RDNE, ENABLE);
        break;
    }

    return RT_EOK;
}

static int at32_putc(struct rt_serial_device *serial, char ch) {
    struct at32_uart_config *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_uart_config *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    USART_SendData(usart->usartx, (uint8_t) ch);
    while (USART_GetFlagStatus(usart->usartx, USART_FLAG_TDE) == RESET);

    return 1;
}

static int at32_getc(struct rt_serial_device *serial) {
    int ch;
    struct at32_uart_config *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_uart_config *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (RESET != USART_GetFlagStatus(usart->usartx, USART_FLAG_RDNE)) {
        ch = USART_ReceiveData(usart->usartx) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops at32_usart_ops = {
        at32_configure,
        at32_control,
        at32_putc,
        at32_getc,
        RT_NULL };

static void usart_isr(struct rt_serial_device *serial) {
    struct at32_uart_config *usart_instance;

    RT_ASSERT(serial != RT_NULL);

    usart_instance = (struct at32_uart_config *) serial->parent.user_data;
    RT_ASSERT(usart_instance != RT_NULL);

    if ((USART_GetITStatus(usart_instance->usartx, USART_INT_RDNE) != RESET) \
        && (RESET != USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_RDNE))) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        USART_ClearITPendingBit(usart_instance->usartx, USART_INT_RDNE);
        USART_ClearFlag(usart_instance->usartx, USART_FLAG_RDNE);
    } else {
        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_CTSF) != RESET) {
            USART_ClearFlag(usart_instance->usartx, USART_FLAG_CTSF);
        }

        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_LBDF) != RESET) {
            USART_ClearFlag(usart_instance->usartx, USART_FLAG_LBDF);
        }

        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_TRAC) != RESET) {
            USART_ClearFlag(usart_instance->usartx, USART_FLAG_TRAC);
        }
    }
}

#ifdef BSP_USING_UART1
void USART1_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&uart_config[UART1_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
void USART2_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&uart_config[UART2_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART3
void USART3_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&uart_config[UART3_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART4
void UART4_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&uart_config[UART4_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART5
void UART5_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&uart_config[UART5_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART6
void USART6_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&uart_config[UART6_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART7
void UART7_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&uart_config[UART7_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART8
void UART8_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&uart_config[UART8_INDEX].serial);

    rt_interrupt_leave();
}
#endif

int rt_hw_usart_init(void) {
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(uart_config) / sizeof(struct at32_uart_config);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++) {
        uart_config[index].serial.ops = &at32_usart_ops;
        uart_config[index].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_config[index].serial,
                uart_config[index].name,
                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX
                        | RT_DEVICE_FLAG_INT_TX, &uart_config[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* BSP_USING_SERIAL */

/******************** end of file *******************/
