/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-09     shelton      first version
 */

#include <at32f4xx.h>

extern int rt_hw_usart_init();
extern void system_clock_config(int);
extern int clock_information(void);
extern uint32_t Ticks;

void clk_init(char *clk_source, int source_freq, int target_freq)
{
    RCC_ClockType RCC_Clocks;
    NVIC_InitType NVIC_InitStructure = {0};

    /* disbale interrupt */
    __set_PRIMASK(1);

    /* system clock config */
    system_clock_config(target_freq);

    /* init system tick to 1KHz */
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_Config(RCC_Clocks.SYSCLK_Freq / 1000);

    NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
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

void _error_handler(char *s, int num)
{
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    while (1)
    {
    }
    /* USER CODE END Error_Handler */
}
