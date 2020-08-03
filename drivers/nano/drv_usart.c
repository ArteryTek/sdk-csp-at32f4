/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-10     shelton      first version
 */

#include "stdlib.h"
#include "drv_common.h"

#define DBG_TAG              "drv.usart"

#ifdef DRV_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif

#include <rtdbg.h>

#ifdef RT_USING_CONSOLE

/* at32 config class */
struct at32_uart_config
{
    const char *name;
    USART_Type* Instance;
    IRQn_Type irq_type;

    const char *tx_pin_name;
    const char *rx_pin_name;
};

static struct at32_uart_config *_uart_config = NULL;

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
    switch ((uint32_t)config->Instance)
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

static rt_err_t at32_configure(struct at32_uart_config *config)
{
    USART_InitType USART_InitStructure;

    at32_uart_clk_enable(config);

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

    USART_Init(config->Instance, &USART_InitStructure);
    USART_INTConfig(config->Instance, USART_INT_RDNE, ENABLE);
    USART_Cmd(config->Instance, ENABLE);

    return RT_EOK;
}

int rt_hw_usart_init(void)
{
    _uart_config = &uart_config[0];

    at32_gpio_configure(_uart_config);

    at32_configure(_uart_config);

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_usart_init);

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            while(!USART_GetFlagStatus(_uart_config->Instance, USART_FLAG_TDE));
            USART_SendData(_uart_config->Instance, a);
        }
        while(!USART_GetFlagStatus(_uart_config->Instance, USART_FLAG_TDE));
        USART_SendData(_uart_config->Instance, *(uint8_t *)(str + i));
    }
}

#ifdef RT_USING_FINSH
char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (USART_GetFlagStatus(_uart_config->Instance, USART_FLAG_RDNE) != RESET)
    {
        ch = _uart_config->Instance->DT & 0xff;
    }
    else
    {
        if(USART_GetFlagStatus(_uart_config->Instance, USART_FLAG_ORERR) != RESET)
        {
            /* Clear Overrun Flag */
			_uart_config->Instance->STS;
			_uart_config->Instance->DT;
        }
        rt_thread_mdelay(10);
    }
    return ch;
}

#endif /* RT_USING_FINSH */
#endif /* RT_USING_CONSLONE */
