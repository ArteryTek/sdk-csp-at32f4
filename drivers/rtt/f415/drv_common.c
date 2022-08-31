/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-08     shelton      first version
 */

#include "board.h"
#include "drv_common.h"

#ifdef RT_USING_SERIAL
#include "drv_usart.h"
#endif

#define DBG_TAG                         "drv_common"
#define DBG_LVL                         DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */

extern __IO uint32_t uwTick;
static uint32_t _systick_ms = 1;

/* systick configuration */
void rt_hw_systick_init(void)
{
    systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
    SysTick_Config(system_core_clock / RT_TICK_PER_SECOND);

    nvic_irq_enable(SysTick_IRQn, 0, 0);

    _systick_ms = 1000u / RT_TICK_PER_SECOND;
    if(_systick_ms == 0)
        _systick_ms = 1;
}

/**
 * this is the timer interrupt service routine.
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
  * @brief  this function is executed in case of error occurrence.
  * @param  none
  * @retval none
  */
void _Error_Handler(char *s, int num)
{
    /* User can add his own implementation to report the HAL error return state */
    LOG_E("Error_Handler at file:%s num:%d", s, num);
    while (1)
    {
    }
}

/**
 * this function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

/**
 * this function will initial at32 board.
 */
void hw_board_init(char *clock_src, int32_t clock_src_freq, int32_t clock_target_freq)
{
    extern void rt_hw_systick_init(void);
    extern void clk_init(char *clk_source, int source_freq, int target_freq);

#ifdef SCB_EnableICache
    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();
#endif

#ifdef SCB_EnableDCache
    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();
#endif

    /* configure nvic priority group */
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

    /* enable interrupt */
    __set_PRIMASK(0);

    /* System clock initialization */
    clk_init(clock_src, clock_src_freq, clock_target_freq);

    /* disbale interrupt */
    __set_PRIMASK(1);

    /* systick init */
    rt_hw_systick_init();

    /* pin driver initialization is open by default */
#ifdef RT_USING_PIN
    extern int rt_hw_pin_init(void);
    rt_hw_pin_init();
#endif

    /* usart driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif
}
