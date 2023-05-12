/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-16     shelton      first version
 */

#include "at32f423.h"

extern int rt_hw_usart_init();
extern void system_clock_config(int);
extern int clock_information(void);
extern uint32_t Ticks;

void clk_init(char *clk_source, int source_freq, int target_freq)
{
    crm_clocks_freq_type crm_clocks;

    /* disbale interrupt */
    __set_PRIMASK(1);

    /* system clock config */
    system_clock_config(target_freq);

    /* init system tick to 1KHz */
    crm_clocks_freq_get(&crm_clocks);
    systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
    SysTick_Config(crm_clocks.sclk_freq / 1000);

    /* enable systick nvic */
    nvic_irq_enable(SysTick_IRQn, 0, 0);

    /* enable interrupt */
    __set_PRIMASK(0);
}

int uart_init()
{
    rt_hw_usart_init();
    clock_information();
    return 0;
}

void SysTick_Handler(void)
{
    Ticks ++;
}
