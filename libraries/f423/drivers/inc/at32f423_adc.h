/**
  **************************************************************************
  * @file     at32f423_adc.h
  * @brief    at32f423 adc header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F423_ADC_H
#define __AT32F423_ADC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f423.h"


/** @addtogroup AT32F423_periph_driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_interrupts_definition
  * @brief adc interrupt
  * @{
  */

#define ADC_OCCE_INT                     ((uint32_t)0x00000020) /*!< ordinary channels conversion end interrupt */
#define ADC_VMOR_INT                     ((uint32_t)0x00000040) /*!< voltage monitoring out of range interrupt */
#define ADC_PCCE_INT                     ((uint32_t)0x00000080) /*!< preempt channels conversion end interrupt */
#define ADC_OCCO_INT                     ((uint32_t)0x04000000) /*!< ordinary channel conversion overflow interrupt */

/**
  * @}
  */

/** @defgroup ADC_flags_definition
  * @brief adc flag
  * @{
  */

#define ADC_VMOR_FLAG                    ((uint8_t)0x01) /*!< voltage monitoring out of range flag */
#define ADC_OCCE_FLAG                    ((uint8_t)0x02) /*!< ordinary channels conversion end flag */
#define ADC_PCCE_FLAG                    ((uint8_t)0x04) /*!< preempt channels conversion end flag */
#define ADC_PCCS_FLAG                    ((uint8_t)0x08) /*!< preempt channel conversion start flag */
#define ADC_OCCS_FLAG                    ((uint8_t)0x10) /*!< ordinary channel conversion start flag */
#define ADC_OCCO_FLAG                    ((uint8_t)0x20) /*!< ordinary channel conversion overflow flag */
#define ADC_RDY_FLAG                     ((uint8_t)0x40) /*!< adc ready to conversion flag */

/**
  * @}
  */

/** @defgroup ADC_exported_types
  * @{
  */

/**
  * @brief adc division type
  */
typedef enum
{
  ADC_HCLK_DIV_2                         = 0x00, /*!< adcclk is hclk/2 */
  ADC_HCLK_DIV_3                         = 0x01, /*!< adcclk is hclk/3 */
  ADC_HCLK_DIV_4                         = 0x02, /*!< adcclk is hclk/4 */
  ADC_HCLK_DIV_5                         = 0x03, /*!< adcclk is hclk/5 */
  ADC_HCLK_DIV_6                         = 0x04, /*!< adcclk is hclk/6 */
  ADC_HCLK_DIV_7                         = 0x05, /*!< adcclk is hclk/7 */
  ADC_HCLK_DIV_8                         = 0x06, /*!< adcclk is hclk/8 */
  ADC_HCLK_DIV_9                         = 0x07, /*!< adcclk is hclk/9 */
  ADC_HCLK_DIV_10                        = 0x08, /*!< adcclk is hclk/10 */
  ADC_HCLK_DIV_11                        = 0x09, /*!< adcclk is hclk/11 */
  ADC_HCLK_DIV_12                        = 0x0A, /*!< adcclk is hclk/12 */
  ADC_HCLK_DIV_13                        = 0x0B, /*!< adcclk is hclk/13 */
  ADC_HCLK_DIV_14                        = 0x0C, /*!< adcclk is hclk/14 */
  ADC_HCLK_DIV_15                        = 0x0D, /*!< adcclk is hclk/15 */
  ADC_HCLK_DIV_16                        = 0x0E, /*!< adcclk is hclk/16 */
  ADC_HCLK_DIV_17                        = 0x0F  /*!< adcclk is hclk/17 */
} adc_div_type;


/**
  * @brief adc conversion resolution type
  */
typedef enum
{
  ADC_RESOLUTION_12B                     = 0x00, /*!< conversion resolution 12 bit */
  ADC_RESOLUTION_10B                     = 0x01, /*!< conversion resolution 10 bit */
  ADC_RESOLUTION_8B                      = 0x02, /*!< conversion resolution 8 bit */
  ADC_RESOLUTION_6B                      = 0x03  /*!< conversion resolution 6 bit */
} adc_resolution_type;

/**
  * @brief adc data align type
  */
typedef enum
{
  ADC_RIGHT_ALIGNMENT                    = 0x00, /*!< data right alignment */
  ADC_LEFT_ALIGNMENT                     = 0x01  /*!< data left alignment */
} adc_data_align_type;

/**
  * @brief adc channel select type
  */
typedef enum
{
  ADC_CHANNEL_0                          = 0x00, /*!< adc channel 0 */
  ADC_CHANNEL_1                          = 0x01, /*!< adc channel 1 */
  ADC_CHANNEL_2                          = 0x02, /*!< adc channel 2 */
  ADC_CHANNEL_3                          = 0x03, /*!< adc channel 3 */
  ADC_CHANNEL_4                          = 0x04, /*!< adc channel 4 */
  ADC_CHANNEL_5                          = 0x05, /*!< adc channel 5 */
  ADC_CHANNEL_6                          = 0x06, /*!< adc channel 6 */
  ADC_CHANNEL_7                          = 0x07, /*!< adc channel 7 */
  ADC_CHANNEL_8                          = 0x08, /*!< adc channel 8 */
  ADC_CHANNEL_9                          = 0x09, /*!< adc channel 9 */
  ADC_CHANNEL_10                         = 0x0A, /*!< adc channel 10 */
  ADC_CHANNEL_11                         = 0x0B, /*!< adc channel 11 */
  ADC_CHANNEL_12                         = 0x0C, /*!< adc channel 12 */
  ADC_CHANNEL_13                         = 0x0D, /*!< adc channel 13 */
  ADC_CHANNEL_14                         = 0x0E, /*!< adc channel 14 */
  ADC_CHANNEL_15                         = 0x0F, /*!< adc channel 15 */
  ADC_CHANNEL_16                         = 0x10, /*!< adc channel 16 */
  ADC_CHANNEL_17                         = 0x11, /*!< adc channel 17 */
  ADC_CHANNEL_20                         = 0x14, /*!< adc channel 20 */
  ADC_CHANNEL_21                         = 0x15, /*!< adc channel 21 */
  ADC_CHANNEL_22                         = 0x16, /*!< adc channel 22 */
  ADC_CHANNEL_23                         = 0x17, /*!< adc channel 23 */
  ADC_CHANNEL_24                         = 0x18, /*!< adc channel 24 */
  ADC_CHANNEL_25                         = 0x19, /*!< adc channel 25 */
  ADC_CHANNEL_26                         = 0x1A, /*!< adc channel 26 */
  ADC_CHANNEL_27                         = 0x1B  /*!< adc channel 27 */
} adc_channel_select_type;

/**
  * @brief adc sampletime select type
  */
typedef enum
{
  ADC_SAMPLETIME_2_5                     = 0x00, /*!< adc sample time 2.5 cycle */
  ADC_SAMPLETIME_6_5                     = 0x01, /*!< adc sample time 6.5 cycle */
  ADC_SAMPLETIME_12_5                    = 0x02, /*!< adc sample time 12.5 cycle */
  ADC_SAMPLETIME_24_5                    = 0x03, /*!< adc sample time 24.5 cycle */
  ADC_SAMPLETIME_47_5                    = 0x04, /*!< adc sample time 47.5 cycle */
  ADC_SAMPLETIME_92_5                    = 0x05, /*!< adc sample time 92.5 cycle */
  ADC_SAMPLETIME_247_5                   = 0x06, /*!< adc sample time 247.5 cycle */
  ADC_SAMPLETIME_640_5                   = 0x07  /*!< adc sample time 640.5 cycle */
} adc_sampletime_select_type;

/**
  * @brief adc ordinary group trigger event select type
  */
typedef enum
{
  ADC_ORDINARY_TRIG_TMR1TRGOUT           = 0x00, /*!< timer1 trgout event as trigger source of ordinary sequence */
  ADC_ORDINARY_TRIG_TMR1CH4              = 0x01, /*!< timer1 ch4 event as trigger source of ordinary sequence */
  ADC_ORDINARY_TRIG_TMR2TRGOUT           = 0x02, /*!< timer2 trgout event as trigger source of ordinary sequence */
  ADC_ORDINARY_TRIG_TMR3TRGOUT           = 0x03, /*!< timer3 trgout event as trigger source of ordinary sequence */
  ADC_ORDINARY_TRIG_TMR9TRGOUT           = 0x04, /*!< timer9 trgout event as trigger source of ordinary sequence */
  ADC_ORDINARY_TRIG_TMR1CH1              = 0x05, /*!< timer1 ch1 event as trigger source of ordinary sequence */
  ADC_ORDINARY_TRIG_EXINT11              = 0x06, /*!< exint line11 event as trigger source of ordinary sequence */
  ADC_ORDINARY_TRIG_SOFTWARE             = 0x07  /*!< software(OCSWTRG) as trigger source of ordinary sequence */
} adc_ordinary_trig_select_type;

/**
  * @brief adc ordinary channel conversion's external_trigger_edge type
  */
typedef enum
{
  ADC_ORDINARY_TRIG_EDGE_NONE            = 0x00, /*!< ordinary channels trigger detection disabled */
  ADC_ORDINARY_TRIG_EDGE_RISING          = 0x01, /*!< ordinary channels trigger detection on the rising edge */
  ADC_ORDINARY_TRIG_EDGE_FALLING         = 0x02, /*!< ordinary channels trigger detection on the falling edge */
  ADC_ORDINARY_TRIG_EDGE_RISING_FALLING  = 0x03  /*!< ordinary channels trigger detection on both the rising and falling edges */
} adc_ordinary_trig_edge_type;

/**
  * @brief adc preempt group external trigger event select type
  */
typedef enum
{
  ADC_PREEMPT_TRIG_TMR1CH2               = 0x00, /*!< timer1 ch2 event as trigger source of preempt sequence */
  ADC_PREEMPT_TRIG_TMR1CH3               = 0x01, /*!< timer1 ch3 event as trigger source of preempt sequence */
  ADC_PREEMPT_TRIG_TMR2CH4               = 0x02, /*!< timer2 ch4 event as trigger source of preempt sequence */
  ADC_PREEMPT_TRIG_TMR3CH4               = 0x03, /*!< timer3 ch4 event as trigger source of preempt sequence */
  ADC_PREEMPT_TRIG_TMR9CH1               = 0x04, /*!< timer9 ch1 event as trigger source of preempt sequence */
  ADC_PREEMPT_TRIG_TMR6TRGOUT            = 0x05, /*!< timer6 trgout event as trigger source of preempt sequence */
  ADC_PREEMPT_TRIG_EXINT15               = 0x06, /*!< exint line15 event as trigger source of preempt sequence */
  ADC_PREEMPT_TRIG_SOFTWARE              = 0x07  /*!< software(PCSWTRG) as trigger source of preempt sequence */
} adc_preempt_trig_select_type;

/**
  * @brief adc preempt channel conversion's external_trigger_edge type
  */
typedef enum
{
  ADC_PREEMPT_TRIG_EDGE_NONE             = 0x00, /*!< preempt channels trigger detection disabled */
  ADC_PREEMPT_TRIG_EDGE_RISING           = 0x01, /*!< preempt channels trigger detection on the rising edge */
  ADC_PREEMPT_TRIG_EDGE_FALLING          = 0x02, /*!< preempt channels trigger detection on the falling edge */
  ADC_PREEMPT_TRIG_EDGE_RISING_FALLING   = 0x03  /*!< preempt channels trigger detection on both the rising and falling edges */
} adc_preempt_trig_edge_type;

/**
  * @brief adc preempt channel type
  */
typedef enum
{
  ADC_PREEMPT_CHANNEL_1                  = 0x00, /*!< adc preempt channel 1 */
  ADC_PREEMPT_CHANNEL_2                  = 0x01, /*!< adc preempt channel 2 */
  ADC_PREEMPT_CHANNEL_3                  = 0x02, /*!< adc preempt channel 3 */
  ADC_PREEMPT_CHANNEL_4                  = 0x03  /*!< adc preempt channel 4 */
} adc_preempt_channel_type;

/**
  * @brief adc voltage_monitoring type
  */
typedef enum
{
  ADC_VMONITOR_SINGLE_ORDINARY           = 0x00800200, /*!< voltage_monitoring on a single ordinary channel */
  ADC_VMONITOR_SINGLE_PREEMPT            = 0x00400200, /*!< voltage_monitoring on a single preempt channel */
  ADC_VMONITOR_SINGLE_ORDINARY_PREEMPT   = 0x00C00200, /*!< voltage_monitoring on a single ordinary or preempt channel */
  ADC_VMONITOR_ALL_ORDINARY              = 0x00800000, /*!< voltage_monitoring on all ordinary channel */
  ADC_VMONITOR_ALL_PREEMPT               = 0x00400000, /*!< voltage_monitoring on all preempt channel */
  ADC_VMONITOR_ALL_ORDINARY_PREEMPT      = 0x00C00000, /*!< voltage_monitoring on all ordinary and preempt channel */
  ADC_VMONITOR_NONE                      = 0x00000000  /*!< no channel guarded by the voltage_monitoring */
} adc_voltage_monitoring_type;

/**
  * @brief adc oversample ratio type
  */
typedef enum
{
  ADC_OVERSAMPLE_RATIO_2                 = 0x00, /*!< adc oversample ratio 2 */
  ADC_OVERSAMPLE_RATIO_4                 = 0x01, /*!< adc oversample ratio 4 */
  ADC_OVERSAMPLE_RATIO_8                 = 0x02, /*!< adc oversample ratio 8 */
  ADC_OVERSAMPLE_RATIO_16                = 0x03, /*!< adc oversample ratio 16 */
  ADC_OVERSAMPLE_RATIO_32                = 0x04, /*!< adc oversample ratio 32 */
  ADC_OVERSAMPLE_RATIO_64                = 0x05, /*!< adc oversample ratio 64 */
  ADC_OVERSAMPLE_RATIO_128               = 0x06, /*!< adc oversample ratio 128 */
  ADC_OVERSAMPLE_RATIO_256               = 0x07  /*!< adc oversample ratio 256 */
} adc_oversample_ratio_type;

/**
  * @brief adc oversample shift type
  */
typedef enum
{
  ADC_OVERSAMPLE_SHIFT_0                 = 0x00, /*!< adc oversample shift 0 */
  ADC_OVERSAMPLE_SHIFT_1                 = 0x01, /*!< adc oversample shift 1 */
  ADC_OVERSAMPLE_SHIFT_2                 = 0x02, /*!< adc oversample shift 2 */
  ADC_OVERSAMPLE_SHIFT_3                 = 0x03, /*!< adc oversample shift 3 */
  ADC_OVERSAMPLE_SHIFT_4                 = 0x04, /*!< adc oversample shift 4 */
  ADC_OVERSAMPLE_SHIFT_5                 = 0x05, /*!< adc oversample shift 5 */
  ADC_OVERSAMPLE_SHIFT_6                 = 0x06, /*!< adc oversample shift 6 */
  ADC_OVERSAMPLE_SHIFT_7                 = 0x07, /*!< adc oversample shift 7 */
  ADC_OVERSAMPLE_SHIFT_8                 = 0x08  /*!< adc oversample shift 8 */
} adc_oversample_shift_type;

/**
  * @brief adc ordinary oversample recover type
  */
typedef enum
{
  ADC_OVERSAMPLE_CONTINUE                = 0x00, /*!< continue mode:when preempt triggered,oversampling is temporary stopped and continued after preempt sequence */
  ADC_OVERSAMPLE_RESTART                 = 0x01  /*!< restart mode:when preempt triggered,oversampling is aborted and resumed from start after preempt sequence */
} adc_ordinary_oversample_restart_type;

/**
  * @brief adc common config type
  */
typedef struct
{
  adc_div_type                           div;                             /*!< adc division select */
  confirm_state                          tempervintrv_state;              /*!< adc temperature sensor and vintrv state */
} adc_common_config_type;

/**
  * @brief adc base config type
  */
typedef struct
{
  confirm_state                          sequence_mode;           /*!< adc sequence mode */
  confirm_state                          repeat_mode;             /*!< adc repeat mode */
  adc_data_align_type                    data_align;              /*!< adc data alignment */
  uint8_t                                ordinary_channel_length; /*!< adc ordinary channel sequence length*/
} adc_base_config_type;

/**
  * @brief type define adc register all
  */
typedef struct
{

  /**
    * @brief adc sts register, offset:0x00
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t vmor                 : 1; /* [0] */
      __IO uint32_t occe                 : 1; /* [1] */
      __IO uint32_t pcce                 : 1; /* [2] */
      __IO uint32_t pccs                 : 1; /* [3] */
      __IO uint32_t occs                 : 1; /* [4] */
      __IO uint32_t occo                 : 1; /* [5] */
      __IO uint32_t rdy                  : 1; /* [6] */
      __IO uint32_t reserved1            : 25;/* [31:7] */
    } sts_bit;
  };

  /**
    * @brief adc ctrl1 register, offset:0x04
    */
  union
  {
    __IO uint32_t ctrl1;
    struct
    {
      __IO uint32_t vmcsel               : 5; /* [4:0] */
      __IO uint32_t occeien              : 1; /* [5] */
      __IO uint32_t vmorien              : 1; /* [6] */
      __IO uint32_t pcceien              : 1; /* [7] */
      __IO uint32_t sqen                 : 1; /* [8] */
      __IO uint32_t vmsgen               : 1; /* [9] */
      __IO uint32_t pcautoen             : 1; /* [10] */
      __IO uint32_t ocpen                : 1; /* [11] */
      __IO uint32_t pcpen                : 1; /* [12] */
      __IO uint32_t ocpcnt               : 3; /* [15:13] */
      __IO uint32_t reserved1            : 6; /* [21:16] */
      __IO uint32_t pcvmen               : 1; /* [22] */
      __IO uint32_t ocvmen               : 1; /* [23] */
      __IO uint32_t crsel                : 2; /* [25:24] */
      __IO uint32_t occoien              : 1; /* [26] */
      __IO uint32_t reserved2            : 5; /* [31:27] */
    } ctrl1_bit;
  };

   /**
    * @brief adc ctrl2 register, offset:0x08
    */
  union
  {
    __IO uint32_t ctrl2;
    struct
    {
      __IO uint32_t adcen                : 1; /* [0] */
      __IO uint32_t rpen                 : 1; /* [1] */
      __IO uint32_t adcal                : 1; /* [2] */
      __IO uint32_t adcalinit            : 1; /* [3] */
      __IO uint32_t adabrt               : 1; /* [4] */
      __IO uint32_t reserved1            : 3; /* [7:5] */
      __IO uint32_t ocdmaen              : 1; /* [8] */
      __IO uint32_t ocdrcen              : 1; /* [9] */
      __IO uint32_t eocsfen              : 1; /* [10] */
      __IO uint32_t dtalign              : 1; /* [11] */
      __IO uint32_t reserved2            : 4; /* [15:12] */
      __IO uint32_t pctesel              : 4; /* [19:16] */
      __IO uint32_t pcete                : 2; /* [21:20] */
      __IO uint32_t pcswtrg              : 1; /* [22] */
      __IO uint32_t reserved3            : 1; /* [23] */
      __IO uint32_t octesel              : 4; /* [27:24] */
      __IO uint32_t ocete                : 2; /* [29:28] */
      __IO uint32_t ocswtrg              : 1; /* [30] */
      __IO uint32_t reserved4            : 1; /* [31] */
    } ctrl2_bit;
  };

  /**
  * @brief adc spt1 register, offset:0x0C
  */
  union
  {
    __IO uint32_t spt1;
    struct
    {
      __IO uint32_t cspt10               : 3; /* [2:0] */
      __IO uint32_t cspt11               : 3; /* [5:3] */
      __IO uint32_t cspt12               : 3; /* [8:6] */
      __IO uint32_t cspt13               : 3; /* [11:9] */
      __IO uint32_t cspt14               : 3; /* [14:12] */
      __IO uint32_t cspt15               : 3; /* [17:15] */
      __IO uint32_t cspt16               : 3; /* [20:18] */
      __IO uint32_t cspt17               : 3; /* [23:21] */
      __IO uint32_t cspt18               : 3; /* [26:24] */
      __IO uint32_t reserved1            : 5;/* [31:27] */
    } spt1_bit;
  };

  /**
  * @brief adc spt2 register, offset:0x10
  */
  union
  {
    __IO uint32_t spt2;
    struct
    {
      __IO uint32_t cspt0                : 3;/* [2:0] */
      __IO uint32_t cspt1                : 3;/* [5:3] */
      __IO uint32_t cspt2                : 3;/* [8:6] */
      __IO uint32_t cspt3                : 3;/* [11:9] */
      __IO uint32_t cspt4                : 3;/* [14:12] */
      __IO uint32_t cspt5                : 3;/* [17:15] */
      __IO uint32_t cspt6                : 3;/* [20:18] */
      __IO uint32_t cspt7                : 3;/* [23:21] */
      __IO uint32_t cspt8                : 3;/* [26:24] */
      __IO uint32_t cspt9                : 3;/* [29:27] */
      __IO uint32_t reserved1            : 2;/* [31:30] */
    } spt2_bit;
  };

  /**
  * @brief adc pcdto1 register, offset:0x14
  */
  union
  {
    __IO uint32_t pcdto1;
    struct
    {
      __IO uint32_t pcdto1               : 12; /* [11:0] */
      __IO uint32_t reserved1            : 20; /* [31:12] */
    } pcdto1_bit;
  };

  /**
  * @brief adc pcdto2 register, offset:0x18
  */
  union
  {
    __IO uint32_t pcdto2;
    struct
    {
      __IO uint32_t pcdto2               : 12; /* [11:0] */
      __IO uint32_t reserved1            : 20; /* [31:12] */
    } pcdto2_bit;
  };

  /**
  * @brief adc pcdto3 register, offset:0x1C
  */
  union
  {
    __IO uint32_t pcdto3;
    struct
    {
      __IO uint32_t pcdto3               : 12; /* [11:0] */
      __IO uint32_t reserved1            : 20; /* [31:12] */
    } pcdto3_bit;
  };

  /**
  * @brief adc pcdto4 register, offset:0x20
  */
  union
  {
    __IO uint32_t pcdto4;
    struct
    {
      __IO uint32_t pcdto4               : 12; /* [11:0] */
      __IO uint32_t reserved1            : 20; /* [31:12] */
    } pcdto4_bit;
  };

  /**
  * @brief adc vmhb register, offset:0x24
  */
  union
  {
    __IO uint32_t vmhb;
    struct
    {
      __IO uint32_t vmhb                 : 16; /* [15:0] */
      __IO uint32_t reserved1            : 16; /* [31:16] */
    } vmhb_bit;
  };

  /**
  * @brief adc vmlb register, offset:0x28
  */
  union
  {
    __IO uint32_t vmlb;
    struct
    {
      __IO uint32_t vmlb                 : 16; /* [15:0] */
      __IO uint32_t reserved1            : 16; /* [31:16] */
    } vmlb_bit;
  };

  /**
  * @brief adc osq1 register, offset:0x2C
  */
  union
  {
    __IO uint32_t osq1;
    struct
    {
      __IO uint32_t osn13                : 5; /* [4:0] */
      __IO uint32_t osn14                : 5; /* [9:5] */
      __IO uint32_t osn15                : 5; /* [14:10] */
      __IO uint32_t osn16                : 5; /* [19:15] */
      __IO uint32_t oclen                : 5; /* [24:20] */
      __IO uint32_t reserved1            : 7; /* [31:25] */
    } osq1_bit;
  };

  /**
  * @brief adc osq2 register, offset:0x30
  */
  union
  {
    __IO uint32_t osq2;
    struct
    {
      __IO uint32_t osn7                 : 5; /* [4:0] */
      __IO uint32_t osn8                 : 5; /* [9:5] */
      __IO uint32_t osn9                 : 5; /* [14:10] */
      __IO uint32_t osn10                : 5; /* [19:15] */
      __IO uint32_t osn11                : 5; /* [24:20] */
      __IO uint32_t osn12                : 5; /* [29:25] */
      __IO uint32_t reserved1            : 2; /* [31:30] */
    } osq2_bit;
  };

  /**
  * @brief adc osq3 register, offset:0x34
  */
  union
  {
    __IO uint32_t osq3;
    struct
    {
      __IO uint32_t osn1                 : 5; /* [4:0] */
      __IO uint32_t osn2                 : 5; /* [9:5] */
      __IO uint32_t osn3                 : 5; /* [14:10] */
      __IO uint32_t osn4                 : 5; /* [19:15] */
      __IO uint32_t osn5                 : 5; /* [24:20] */
      __IO uint32_t osn6                 : 5; /* [29:25] */
      __IO uint32_t reserved1            : 2; /* [31:30] */
    } osq3_bit;
  };

  /**
  * @brief adc psq register, offset:0x38
  */
  union
  {
    __IO uint32_t psq;
    struct
    {
      __IO uint32_t psn1                 : 5; /* [4:0] */
      __IO uint32_t psn2                 : 5; /* [9:5] */
      __IO uint32_t psn3                 : 5; /* [14:10] */
      __IO uint32_t psn4                 : 5; /* [19:15] */
      __IO uint32_t pclen                : 2; /* [21:20] */
      __IO uint32_t reserved1            : 10;/* [31:22] */
    } psq_bit;
  };

  /**
  * @brief adc pdt1 register, offset:0x3C
  */
  union
  {
    __IO uint32_t pdt1;
    struct
    {
      __IO uint32_t pdt1                 : 16; /* [15:0] */
      __IO uint32_t reserved1            : 16; /* [31:16] */
    } pdt1_bit;
  };

  /**
  * @brief adc pdt2 register, offset:0x40
  */
  union
  {
    __IO uint32_t pdt2;
    struct
    {
      __IO uint32_t pdt2                 : 16; /* [15:0] */
      __IO uint32_t reserved1            : 16; /* [31:16] */
    } pdt2_bit;
  };

  /**
  * @brief adc pdt3 register, offset:0x44
  */
  union
  {
    __IO uint32_t pdt3;
    struct
    {
      __IO uint32_t pdt3                 : 16; /* [15:0] */
      __IO uint32_t reserved1            : 16; /* [31:16] */
    } pdt3_bit;
  };

  /**
  * @brief adc pdt4 register, offset:0x48
  */
  union
  {
    __IO uint32_t pdt4;
    struct
    {
      __IO uint32_t pdt4                 : 16; /* [15:0] */
      __IO uint32_t reserved1            : 16; /* [31:16] */
    } pdt4_bit;
  };

  /**
  * @brief adc odt register, offset:0x4C
  */
  union
  {
    __IO uint32_t odt;
    struct
    {
      __IO uint32_t odt                  : 16; /* [15:0] */
      __IO uint32_t reserved1            : 16; /* [31:16] */
    } odt_bit;
  };

  /**
  * @brief adc spt3 register, offset:0x50
  */
  union
  {
    __IO uint32_t spt3;
    struct
    {
      __IO uint32_t cspt20               : 3;/* [2:0] */
      __IO uint32_t cspt21               : 3;/* [5:3] */
      __IO uint32_t cspt22               : 3;/* [8:6] */
      __IO uint32_t cspt23               : 3;/* [11:9] */
      __IO uint32_t cspt24               : 3;/* [14:12] */
      __IO uint32_t cspt25               : 3;/* [17:15] */
      __IO uint32_t cspt26               : 3;/* [20:18] */
      __IO uint32_t cspt27               : 3;/* [23:21] */
      __IO uint32_t reserved1            : 8;/* [31:24] */
    } spt3_bit;
  };

  /**
  * @brief adc osq4 register, offset:0x54
  */
  union
  {
    __IO uint32_t osq4;
    struct
    {
      __IO uint32_t osn17                : 5; /* [4:0] */
      __IO uint32_t osn18                : 5; /* [9:5] */
      __IO uint32_t osn19                : 5; /* [14:10] */
      __IO uint32_t osn20                : 5; /* [19:15] */
      __IO uint32_t osn21                : 5; /* [24:20] */
      __IO uint32_t osn22                : 5; /* [29:25] */
      __IO uint32_t reserved1            : 2; /* [31:30] */
    } osq4_bit;
  };

  /**
  * @brief adc osq5 register, offset:0x58
  */
  union
  {
    __IO uint32_t osq5;
    struct
    {
      __IO uint32_t osn23                : 5; /* [4:0] */
      __IO uint32_t osn24                : 5; /* [9:5] */
      __IO uint32_t osn25                : 5; /* [14:10] */
      __IO uint32_t osn26                : 5; /* [19:15] */
      __IO uint32_t osn27                : 5; /* [24:20] */
      __IO uint32_t osn28                : 5; /* [29:25] */
      __IO uint32_t reserved1            : 2; /* [31:30] */
    } osq5_bit;
  };

  /**
  * @brief adc osq6 register, offset:0x5c
  */
  union
  {
    __IO uint32_t osq6;
    struct
    {
      __IO uint32_t osn29                : 5; /* [4:0] */
      __IO uint32_t osn30                : 5; /* [9:5] */
      __IO uint32_t osn31                : 5; /* [14:10] */
      __IO uint32_t osn32                : 5; /* [19:15] */
      __IO uint32_t reserved1            : 12; /* [31:20] */
    } osq6_bit;
  };

  __IO uint32_t reserved1[8];

  /**
  * @brief adc ovsp register, offset:0x80
  */
  union
  {
    __IO uint32_t ovsp;
    struct
    {
      __IO uint32_t oosen                : 1; /* [0] */
      __IO uint32_t posen                : 1; /* [1] */
      __IO uint32_t osrsel               : 3; /* [4:2] */
      __IO uint32_t osssel               : 4; /* [8:5] */
      __IO uint32_t oostren              : 1; /* [9] */
      __IO uint32_t oosrsel              : 1; /* [10] */
      __IO uint32_t reserved1            : 21; /* [31:11] */
    } ovsp_bit;
  };

  __IO uint32_t reserved2[12];

  /**
  * @brief adc calval register, offset:0xB4
  */
  union
  {
    __IO uint32_t calval;
    struct
    {
      __IO uint32_t calval               : 7; /* [6:0] */
      __IO uint32_t reserved1            : 25; /* [31:7] */
    } calval_bit;
  };

  __IO uint32_t reserved3[6];

  /**
  * @brief adc misc register, offset:0xD0
  */
  union
  {
    __IO uint32_t misc;
    struct
    {
      __IO uint32_t xtest                : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26; /* [31:6] */
    } misc_bit;
  };
} adc_type;

/**
  * @brief type define adc register all
  */
typedef struct
{

  /**
    * @brief adc csts register, offset:0x00
    */
  union
  {
    __IO uint32_t csts;
    struct
    {
      __IO uint32_t vmor1                : 1; /* [0] */
      __IO uint32_t occe1                : 1; /* [1] */
      __IO uint32_t pcce1                : 1; /* [2] */
      __IO uint32_t pccs1                : 1; /* [3] */
      __IO uint32_t occs1                : 1; /* [4] */
      __IO uint32_t occo1                : 1; /* [5] */
      __IO uint32_t rdy1                 : 1; /* [6] */
      __IO uint32_t reserved1            : 25; /* [31:7] */
    } csts_bit;
  };

  /**
    * @brief adc cctrl register, offset:0x04
    */
  union
  {
    __IO uint32_t cctrl;
    struct
    {
      __IO uint32_t reserved1            : 16; /* [15:0] */
      __IO uint32_t adcdiv               : 4; /* [19:16] */
      __IO uint32_t reserved2            : 3; /* [22:20] */
      __IO uint32_t itsrven              : 1; /* [23] */
      __IO uint32_t reserved3            : 8; /* [31:24] */
    } cctrl_bit;
  };

} adccom_type;

/**
  * @}
  */

#define ADC1                             ((adc_type *) ADC1_BASE)
#define ADCCOM                           ((adccom_type *) ADCCOM_BASE)

/** @defgroup ADC_exported_functions
  * @{
  */

void adc_reset(void);
void adc_enable(adc_type *adc_x, confirm_state new_state);
void adc_base_default_para_init(adc_base_config_type *adc_base_struct);
void adc_base_config(adc_type *adc_x, adc_base_config_type *adc_base_struct);
void adc_common_default_para_init(adc_common_config_type *adc_common_struct);
void adc_common_config(adc_common_config_type *adc_common_struct);
void adc_resolution_set(adc_type *adc_x, adc_resolution_type resolution);
void adc_dma_mode_enable(adc_type *adc_x, confirm_state new_state);
void adc_dma_request_repeat_enable(adc_type *adc_x, confirm_state new_state);
void adc_interrupt_enable(adc_type *adc_x, uint32_t adc_int, confirm_state new_state);
void adc_calibration_value_set(adc_type *adc_x, uint8_t adc_calibration_value);
void adc_calibration_init(adc_type *adc_x);
flag_status adc_calibration_init_status_get(adc_type *adc_x);
void adc_calibration_start(adc_type *adc_x);
flag_status adc_calibration_status_get(adc_type *adc_x);
void adc_voltage_monitor_enable(adc_type *adc_x, adc_voltage_monitoring_type adc_voltage_monitoring);
void adc_voltage_monitor_threshold_value_set(adc_type *adc_x, uint16_t adc_high_threshold, uint16_t adc_low_threshold);
void adc_voltage_monitor_single_channel_select(adc_type *adc_x, adc_channel_select_type adc_channel);
void adc_ordinary_channel_set(adc_type *adc_x, adc_channel_select_type adc_channel, uint8_t adc_sequence, adc_sampletime_select_type adc_sampletime);
void adc_preempt_channel_length_set(adc_type *adc_x, uint8_t adc_channel_lenght);
void adc_preempt_channel_set(adc_type *adc_x, adc_channel_select_type adc_channel, uint8_t adc_sequence, adc_sampletime_select_type adc_sampletime);
void adc_ordinary_conversion_trigger_set(adc_type *adc_x, adc_ordinary_trig_select_type adc_ordinary_trig, adc_ordinary_trig_edge_type adc_ordinary_trig_edge);
void adc_preempt_conversion_trigger_set(adc_type *adc_x, adc_preempt_trig_select_type adc_preempt_trig, adc_preempt_trig_edge_type adc_preempt_trig_edge);
void adc_preempt_offset_value_set(adc_type *adc_x, adc_preempt_channel_type adc_preempt_channel, uint16_t adc_offset_value);
void adc_ordinary_part_count_set(adc_type *adc_x, uint8_t adc_channel_count);
void adc_ordinary_part_mode_enable(adc_type *adc_x, confirm_state new_state);
void adc_preempt_part_mode_enable(adc_type *adc_x, confirm_state new_state);
void adc_preempt_auto_mode_enable(adc_type *adc_x, confirm_state new_state);
void adc_conversion_stop(adc_type *adc_x);
flag_status adc_conversion_stop_status_get(adc_type *adc_x);
void adc_occe_each_conversion_enable(adc_type *adc_x, confirm_state new_state);
void adc_ordinary_software_trigger_enable(adc_type *adc_x, confirm_state new_state);
flag_status adc_ordinary_software_trigger_status_get(adc_type *adc_x);
void adc_preempt_software_trigger_enable(adc_type *adc_x, confirm_state new_state);
flag_status adc_preempt_software_trigger_status_get(adc_type *adc_x);
uint16_t adc_ordinary_conversion_data_get(adc_type *adc_x);
uint16_t adc_preempt_conversion_data_get(adc_type *adc_x, adc_preempt_channel_type adc_preempt_channel);
flag_status adc_flag_get(adc_type *adc_x, uint8_t adc_flag);
flag_status adc_interrupt_flag_get(adc_type *adc_x, uint8_t adc_flag);
void adc_flag_clear(adc_type *adc_x, uint32_t adc_flag);
void adc_ordinary_oversample_enable(adc_type *adc_x, confirm_state new_state);
void adc_preempt_oversample_enable(adc_type *adc_x, confirm_state new_state);
void adc_oversample_ratio_shift_set(adc_type *adc_x, adc_oversample_ratio_type adc_oversample_ratio, adc_oversample_shift_type adc_oversample_shift);
void adc_ordinary_oversample_trig_enable(adc_type *adc_x, confirm_state new_state);
void adc_ordinary_oversample_restart_set(adc_type *adc_x, adc_ordinary_oversample_restart_type adc_ordinary_oversample_restart);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
