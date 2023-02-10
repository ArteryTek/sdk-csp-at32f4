/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-13     shelton      first version
 */

#include <rtthread.h>
#include "at32f403a_407.h"
#include "board.h"
#include "drv_common.h"

#define DBG_TAG "board"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void system_clock_config(int target_freq_Mhz)
{
    /* reset crm */
    crm_reset();

    crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

     /* wait till hext is ready */
    while(crm_hext_stable_wait() == ERROR)
    {
    }

    /* config pll clock resource */
    crm_pll_config(CRM_PLL_SOURCE_HEXT_DIV, CRM_PLL_MULT_60, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

    /* config hext division */
    crm_hext_clock_div_set(CRM_HEXT_DIV_2);

    /* enable pll */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

    /* wait till pll is ready */
    while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
    {
    }

    /* config ahbclk */
    crm_ahb_div_set(CRM_AHB_DIV_1);

    /* config apb2clk */
    crm_apb2_div_set(CRM_APB2_DIV_2);

    /* config apb1clk */
    crm_apb1_div_set(CRM_APB1_DIV_2);

    /* enable auto step mode */
    crm_auto_step_mode_enable(TRUE);

    /* select pll as system clock source */
    crm_sysclk_switch(CRM_SCLK_PLL);

    /* wait till pll is used as system clock source */
    while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
    {
    }

    /* disable auto step mode */
    crm_auto_step_mode_enable(FALSE);

    /* update system_core_clock global variable */
    system_core_clock_update();
}

int clock_information(void)
{
    crm_clocks_freq_type crm_clocks;

    crm_clocks_freq_get(&crm_clocks);

    LOG_D("System Clock information\n");
    LOG_D("SYSCLK_Frequency = %d\n", (int) crm_clocks.sclk_freq);
    LOG_D("HCLK_Frequency   = %d\n", (int) crm_clocks.ahb_freq);
    LOG_D("PCLK1_Frequency  = %d\n", (int) crm_clocks.apb1_freq);
    LOG_D("PCLK2_Frequency  = %d\n", (int) crm_clocks.apb2_freq);

    return RT_EOK;
}

INIT_BOARD_EXPORT(clock_information);

void clk_init(char *clk_source, int source_freq, int target_freq)
{
    system_clock_config(target_freq);
}
