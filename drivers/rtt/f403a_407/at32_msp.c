/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-08     shelton      first version
 */

#include <rtthread.h>
#include "board.h"
#include "drv_common.h"
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

        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_4;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_7;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pins = GPIO_PINS_6;
        gpio_init(GPIOA, &gpio_init_struct);
    }
#endif
#ifdef BSP_USING_SPI2
    if(SPI2 == spi_x)
    {
        crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_12;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_13 | GPIO_PINS_15;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pins = GPIO_PINS_14;
        gpio_init(GPIOB, &gpio_init_struct);
    }
#endif
    /* add others */
#endif
}

void at32_msp_sdio_init(void *instance)
{
#if defined (BSP_USING_SDIO)
    gpio_init_type gpio_init_struct;
    sdio_type *sdio_x = (sdio_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    if(sdio_x == SDIO1)
    {
        /* if used dma ... */
        crm_periph_clock_enable(CRM_DMA2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_SDIO1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10 | GPIO_PINS_11 | GPIO_PINS_12;
        gpio_init(GPIOC, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_2;
        gpio_init(GPIOD, &gpio_init_struct);
    }
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
    }
#endif
    /* add others */
#endif
}

void at32_msp_adc_init(void *instance)
{
#if defined (BSP_USING_ADC1) || defined (BSP_USING_ADC2)
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

#ifdef BSP_USING_ADC2
    if(adc_x == ADC2)
    {
        /* adc2 & gpio clock enable */
        crm_periph_clock_enable(CRM_ADC2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

        /* configure adc channel as analog input */
        gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_2 | GPIO_PINS_3 | GPIO_PINS_4 | GPIO_PINS_5;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init(GPIOC, &gpio_init_struct);
    }
#endif
#endif
}

void at32_msp_hwtmr_init(void *instance)
{
#if defined (BSP_USING_HWTMR3) || defined (BSP_USING_HWTMR4) || \
    defined (BSP_USING_HWTMR5)
    tmr_type *tmr_x = (tmr_type *)instance;

#ifdef BSP_USING_HWTMR3
    if(tmr_x == TMR3)
    {
        /* tmr3 clock enable */
        crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
    }
#endif

#ifdef BSP_USING_HWTMR4
    if(tmr_x == TMR4)
    {
        /* tmr4 clock enable */
        crm_periph_clock_enable(CRM_TMR4_PERIPH_CLOCK, TRUE);
    }
#endif

#ifdef BSP_USING_HWTMR5
    if(tmr_x == TMR5)
    {
        /* tmr5 clock enable */
        crm_periph_clock_enable(CRM_TMR5_PERIPH_CLOCK, TRUE);
    }
#endif
#endif
}

void at32_msp_can_init(void *instance)
{
#if defined (BSP_USING_CAN1) || defined (BSP_USING_CAN2)
    gpio_init_type gpio_init_struct;
    can_type *can_x = (can_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_CAN1
    if(CAN1 == can_x)
    {
        crm_periph_clock_enable(CRM_CAN1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_9;
        gpio_init(GPIOB, &gpio_init_struct);
        gpio_pin_remap_config(CAN1_GMUX_0010, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8;
        gpio_init(GPIOB, &gpio_init_struct);
    }
#endif
#ifdef BSP_USING_CAN2
    if(CAN2 == can_x)
    {
        crm_periph_clock_enable(CRM_CAN2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_6;
        gpio_init(GPIOB, &gpio_init_struct);
        gpio_pin_remap_config(CAN2_GMUX_0001, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_5;
        gpio_init(GPIOB, &gpio_init_struct);
    }
#endif
#endif
}

void at32_msp_emac_init(void *instance)
{
#if defined (BSP_USING_EMAC)
    gpio_init_type gpio_init_struct;

    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

    gpio_pin_remap_config(EMAC_MUX, TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_pins = GPIO_PINS_2;
    gpio_init(GPIOA, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_11 | GPIO_PINS_12 | GPIO_PINS_13;
    gpio_init(GPIOB, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_1;
    gpio_init(GPIOC, &gpio_init_struct);

    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_pins = GPIO_PINS_1;
    gpio_init(GPIOA, &gpio_init_struct);

    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10;
    gpio_init(GPIOD, &gpio_init_struct);
#endif
}
