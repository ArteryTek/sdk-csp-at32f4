/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-28     shelton      first version
 */

#include <rtthread.h>
#include <stdlib.h>
#include "drv_common.h"
#include "drv_usart.h"
#include "at32_msp.h"

void at32_msp_spi_init(void *instance)
{
#if defined (BSP_USING_SPI1) || defined (BSP_USING_SPI2)
    gpio_init_type gpio_init_struct;
    spi_type *spi_x = (spi_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_SPI1
    if(spi_x == SPI1)
    {
        crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_4;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_6 | GPIO_PINS_7;
        gpio_init(GPIOA, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE5, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE6, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE7, GPIO_MUX_5);
    }
#endif
#ifdef BSP_USING_SPI2
    if(spi_x == SPI2)
    {
        crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_12;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pins = GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE13, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE14, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE15, GPIO_MUX_5);
    }
#endif
    /* add others */
#endif
}

void at32_msp_i2c_init(void *instance)
{
#if defined (BSP_USING_HARD_I2C1) || defined (BSP_USING_HARD_I2C2) || \
    defined (BSP_USING_HARD_I2C3)
    gpio_init_type gpio_init_struct;
    i2c_type *i2c_x = (i2c_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_HARD_I2C1
    if(I2C1 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE7, GPIO_MUX_4);
    }
#endif
#ifdef BSP_USING_HARD_I2C2
    if(I2C2 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_10 | GPIO_PINS_11;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE10, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE11, GPIO_MUX_4);
    }
#endif
#ifdef BSP_USING_HARD_I2C3
    if(I2C3 == i2c_x)
    {
        crm_periph_clock_enable(CRM_I2C3_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8;
        gpio_init(GPIOA, &gpio_init_struct);
        gpio_init_struct.gpio_pins = GPIO_PINS_9;
        gpio_init(GPIOC, &gpio_init_struct);

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE8, GPIO_MUX_4);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE9, GPIO_MUX_4);
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

        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE8, GPIO_MUX_12);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE9, GPIO_MUX_12);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE10, GPIO_MUX_12);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE11, GPIO_MUX_12);
        gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE12, GPIO_MUX_12);

        gpio_init_struct.gpio_pins = GPIO_PINS_2;
        gpio_init(GPIOD, &gpio_init_struct);

        gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE2, GPIO_MUX_12);
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

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE8, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE11, GPIO_MUX_1);
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

        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE0, GPIO_MUX_1);
        gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE1, GPIO_MUX_1);
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
    if(can_x == CAN1)
    {
        crm_periph_clock_enable(CRM_CAN1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_9;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE8, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE9, GPIO_MUX_9);
    }
#endif
#ifdef BSP_USING_CAN2
    if(can_x == CAN2)
    {
        crm_periph_clock_enable(CRM_CAN2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_6;
        gpio_init(GPIOB, &gpio_init_struct);

        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE5, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_9);
    }
#endif
#endif
}

void at32_msp_emac_init(void *instance)
{
#if defined (BSP_USING_EMAC)
    gpio_init_type gpio_init_struct;

    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_pins = GPIO_PINS_1 | GPIO_PINS_2;
    gpio_init(GPIOA, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_1;
    gpio_init(GPIOC, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10;
    gpio_init(GPIOD, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_11 | GPIO_PINS_13 | GPIO_PINS_14;
    gpio_init(GPIOG, &gpio_init_struct);

    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE1, GPIO_MUX_11);
    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE2, GPIO_MUX_11);
    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE1, GPIO_MUX_11);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE8, GPIO_MUX_11);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE9, GPIO_MUX_11);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE10, GPIO_MUX_11);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE11, GPIO_MUX_11);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE13, GPIO_MUX_11);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE14, GPIO_MUX_11);
#endif
}

void at32_msp_qspi_init(void *instance)
{
#if defined (BSP_USING_QSPI1) || defined (BSP_USING_QSPI2)
    gpio_init_type gpio_init_struct;
    qspi_type *qspi_x = (qspi_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#ifdef BSP_USING_QSPI1
    if(qspi_x == QSPI1)
    {
        crm_periph_clock_enable(CRM_QSPI1_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7 | GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10;
        gpio_init(GPIOF, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_6;
        gpio_init(GPIOG, &gpio_init_struct);

        gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE6, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE7, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE8, GPIO_MUX_10);
        gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE9, GPIO_MUX_10);
        gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE10, GPIO_MUX_9);
        gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE6, GPIO_MUX_10);
    }
#endif
#ifdef BSP_USING_QSPI2
    if(qspi_x == QSPI2)
    {
        crm_periph_clock_enable(CRM_QSPI2_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);

        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_pins = GPIO_PINS_7 | GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10;
        gpio_init(GPIOE, &gpio_init_struct);

        gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_13;
        gpio_init(GPIOG, &gpio_init_struct);

        gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE7, GPIO_MUX_10);
        gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE8, GPIO_MUX_10);
        gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE9, GPIO_MUX_10);
        gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE10, GPIO_MUX_10);
        gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE8, GPIO_MUX_5);
        gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE13, GPIO_MUX_5);
    }
#endif
#endif
}

void at32_msp_sdram_init(void *instance)
{
#ifdef BSP_USING_SDRAM
    gpio_init_type gpio_init_struct;

    gpio_default_para_init(&gpio_init_struct);

    /* enable the gpio clock */
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);

    /* enable the xmc clock */
    crm_periph_clock_enable(CRM_XMC_PERIPH_CLOCK, TRUE);

    /* address lines configuration */
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;

    gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_6;
    gpio_init(GPIOB, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_2 | GPIO_PINS_3;
    gpio_init(GPIOC, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10 | GPIO_PINS_14 | GPIO_PINS_15;
    gpio_init(GPIOD, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_7 | GPIO_PINS_8 | GPIO_PINS_10 |
                                 GPIO_PINS_9 | GPIO_PINS_11 | GPIO_PINS_11 | GPIO_PINS_12 |
                                 GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15;
    gpio_init(GPIOE, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_2 | GPIO_PINS_3 |
                                 GPIO_PINS_4 | GPIO_PINS_5 | GPIO_PINS_11 | GPIO_PINS_12 |
                                 GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15;
    gpio_init(GPIOF, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_2 | GPIO_PINS_4 |
                                 GPIO_PINS_5 | GPIO_PINS_8 | GPIO_PINS_15;
    gpio_init(GPIOG, &gpio_init_struct);

    /* gpio mux configuration */
    gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE5, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_12);

    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE0, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE2, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOC, GPIO_PINS_SOURCE3, GPIO_MUX_12);

    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE0, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE1, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE8, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE9, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE10, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE14, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE15, GPIO_MUX_12);

    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE0, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE1, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE7, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE8, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE9, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE10, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE11, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE12, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE13, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE14, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE15, GPIO_MUX_12);

    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE0, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE1, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE2, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE3, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE4, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE5, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE11, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE12, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE13, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE14, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOF, GPIO_PINS_SOURCE15, GPIO_MUX_12);

    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE0, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE1, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE2, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE4, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE5, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE8, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOG, GPIO_PINS_SOURCE15, GPIO_MUX_12);
#endif
}


static rt_err_t at32_uart_clk_enable(usart_type *uart_x)
{
    /* uart clock enable */
    switch ((uint32_t)uart_x)
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
        ;
    }

    return RT_EOK;
}

static rt_err_t at32_gpio_clk_enable(gpio_type *gpio_x)
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
        ;
    }

    return RT_EOK;
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

void at32_msp_usart_init(void *instance)
{
    at32_uart_clk_enable(((struct at32_uart *)instance)->uart_x);
    at32_gpio_configure(instance);
}

void at32_msp_usb_init(void *instance)
{
#if defined (BSP_USING_HOST_USBOTG1) || defined (BSP_USING_DEVICE_USBOTG1) || \
    defined (BSP_USING_HOST_USBOTG2) || defined (BSP_USING_DEVICE_USBOTG2)
    /* defalut usb clock from hick */
    usb_clk48_s clk_s = USB_CLK_HICK;

#if defined (BSP_USING_HOST_USBOTG1) || defined (BSP_USING_DEVICE_USBOTG1)
    crm_periph_clock_enable(CRM_OTGFS1_PERIPH_CLOCK, TRUE);
#endif

#if defined (BSP_USING_HOST_USBOTG2) || defined (BSP_USING_DEVICE_USBOTG2)
    crm_periph_clock_enable(CRM_OTGFS2_PERIPH_CLOCK, TRUE);
#endif

    if(clk_s == USB_CLK_HICK)
    {
        crm_usb_clock_source_select(CRM_USB_CLOCK_SOURCE_HICK);
        /* enable the acc calibration ready interrupt */
        crm_periph_clock_enable(CRM_ACC_PERIPH_CLOCK, TRUE);

        /* update the c1\c2\c3 value */
        acc_write_c1(7980);
        acc_write_c2(8000);
        acc_write_c3(8020);

        /* open acc calibration */
        acc_calibration_mode_enable(ACC_CAL_HICKTRIM, TRUE);
    }
    else
    {
        switch(system_core_clock)
        {
            /* 48MHz */
            case 48000000:
                crm_usb_clock_div_set(CRM_USB_DIV_1);
                break;

            /* 72MHz */
            case 72000000:
                crm_usb_clock_div_set(CRM_USB_DIV_1_5);
                break;

            /* 96MHz */
            case 96000000:
                crm_usb_clock_div_set(CRM_USB_DIV_2);
                break;

            /* 120MHz */
            case 120000000:
                crm_usb_clock_div_set(CRM_USB_DIV_2_5);
                break;

            /* 144MHz */
            case 144000000:
                crm_usb_clock_div_set(CRM_USB_DIV_3);
                break;

            /* 168MHz */
            case 168000000:
                crm_usb_clock_div_set(CRM_USB_DIV_3_5);
                break;

            /* 192MHz */
            case 192000000:
              crm_usb_clock_div_set(CRM_USB_DIV_4);
              break;

            /* 216MHz */
            case 216000000:
                crm_usb_clock_div_set(CRM_USB_DIV_4_5);
                break;

            /* 240MHz */
            case 240000000:
                crm_usb_clock_div_set(CRM_USB_DIV_5);
                break;

            /* 264MHz */
            case 264000000:
                crm_usb_clock_div_set(CRM_USB_DIV_5_5);
                break;

            /* 288MHz */
            case 288000000:
                crm_usb_clock_div_set(CRM_USB_DIV_6);
                break;

            default:
                break;
        }
    }
#endif
}

void at32_msp_dac_init(void *instance)
{
#ifdef BSP_USING_DAC1
    gpio_init_type gpio_init_struct;
    dac_type *dac_x = (dac_type *)instance;

    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
#endif
#ifdef BSP_USING_DAC1
    if(dac_x == DAC)
    {
        /* dac & gpio clock enable */
        crm_periph_clock_enable(CRM_DAC_PERIPH_CLOCK, TRUE);
        crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

        /* configure adc channel as analog output */
        gpio_init_struct.gpio_pins = GPIO_PINS_4 | GPIO_PINS_5;
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init(GPIOA, &gpio_init_struct);
    }
#endif
}
