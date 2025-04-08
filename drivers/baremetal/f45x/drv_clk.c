/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-18     shelton      first version
 */

#include <stdio.h>
#include "at32f45x.h"

volatile uint32_t Ticks;

void system_clock_config(int target_freq_Mhz)
{
    /* reset crm */
    crm_reset();

    /* set the flash clock divider */
    flash_psr_set(FLASH_WAIT_CYCLE_5);

    /* enable pwc periph clock */
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

    /* config ldo voltage */
    pwc_ldo_output_voltage_set(PWC_LDO_OUTPUT_1V3);

    crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

    /* wait till hext is ready */
    while(crm_hext_stable_wait() == ERROR)
    {
    }

    /* config pll clock resource */
    crm_pll_config(CRM_PLL_SOURCE_HEXT, 96, 1, CRM_PLL_FP_4);

    /* config pllu divider */
    crm_pllu_div_set(CRM_PLL_FU_16);

    /* pllu enable  */
    crm_pllu_output_set(TRUE);

    /* enable pll */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

    /* wait till pll is ready */
    while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
    {
    }

    /* config ahbclk */
    crm_ahb_div_set(CRM_AHB_DIV_1);

    /* config apb3clk, the maximum frequency of APB3 clock is 90 MHz */
    crm_apb3_div_set(CRM_APB3_DIV_4);

    /* config apb2clk, the maximum frequency of APB2 clock is 192 MHz */
    crm_apb2_div_set(CRM_APB2_DIV_1);

    /* config apb1clk, the maximum frequency of APB1 clock is 192 MHz */
    crm_apb1_div_set(CRM_APB1_DIV_1);

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

    printf("System Clock information\n");
    printf("SYSCLK_Frequency = %d\n", (int) crm_clocks.sclk_freq);
    printf("HCLK_Frequency   = %d\n", (int) crm_clocks.ahb_freq);
    printf("PCLK1_Frequency  = %d\n", (int) crm_clocks.apb1_freq);
    printf("PCLK2_Frequency  = %d\n", (int) crm_clocks.apb2_freq);

    return 0;
}

void IncTick(void)
{
    Ticks ++;
}

uint32_t GetTicks(void)
{
    return Ticks;
}

void wait_ms(unsigned long ms_time)
{
    uint32_t tickstart = GetTicks();
    uint32_t wait = ms_time;

    /* Add a freq to guarantee minimum wait */
    if (wait < 0xFFFFFFFFU)
    {
        wait += 1;
    }

    while ((GetTicks() - tickstart) < wait)
    {
    }
}
