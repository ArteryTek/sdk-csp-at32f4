/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-10     shelton      first version
 */

#include <board.h>
#include <rtthread.h>
#include <at32f4xx.h>
#include "drv_common.h"

#define DBG_TAG "board"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void system_clock_config(int target_freq_Mhz)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
        StartUpCounter++;
    }
    while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* HCLK = SYSCLK */
        RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

        /* PCLK2 = HCLK/2 */
        RCC->CFG &= 0xFFFFC7FF;
        RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

        /* PCLK1 = HCLK/2 */
        RCC->CFG &= 0xFFFFF8FF;
        RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

        /*  PLL configuration: PLLCLK = HSE * 30 = 240 MHz */
        RCC->CFG &= RCC_CFG_PLLCFG_MASK;
        RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT30 | RCC_CFG_PLLRANGE_GT72MHZ);

        /* Enable PLL */
        RCC->CTRL |= RCC_CTRL_PLLEN;

        /* Wait till PLL is ready */
        while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
        {
        }

        RCC_StepModeCmd(ENABLE);

        /* Select PLL as system clock source */
        RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
        RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
        {
        }

        RCC_StepModeCmd(DISABLE);
    }
    else
    {
      /* If HSE fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */
    }
}

int clock_information(void)
{
    RCC_ClockType RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks);

    LOG_D("System Clock information\n");
    LOG_D("SYSCLK_Frequency = %d\n", (int) RCC_Clocks.SYSCLK_Freq);
    LOG_D("HCLK_Frequency   = %d\n", (int) RCC_Clocks.AHBCLK_Freq);
    LOG_D("PCLK1_Frequency  = %d\n", (int) RCC_Clocks.APB1CLK_Freq);
    LOG_D("PCLK2_Frequency  = %d\n", (int) RCC_Clocks.APB2CLK_Freq);

    return RT_EOK;
}

INIT_BOARD_EXPORT(clock_information);

void clk_init(char *clk_source, int source_freq, int target_freq)
{
    system_clock_config(target_freq);
}
