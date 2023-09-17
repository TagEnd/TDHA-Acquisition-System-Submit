/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sdio.h
  * @brief   This file contains all the function prototypes for
  *          the sdio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SDIO_H__
#define __SDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SD_HandleTypeDef hsd;

/* USER CODE BEGIN Private defines */
#define STD_CAPACITY_SD_CARD_V1_1             ((uint32_t)0x00000000)
#define STD_CAPACITY_SD_CARD_V2_0             ((uint32_t)0x00000001)
#define HIGH_CAPACITY_SD_CARD                 ((uint32_t)0x00000002)
#define MULTIMEDIA_CARD                       ((uint32_t)0x00000003)
#define SECURE_DIGITAL_IO_CARD                ((uint32_t)0x00000004)
#define HIGH_SPEED_MULTIMEDIA_CARD            ((uint32_t)0x00000005)
#define SECURE_DIGITAL_IO_COMBO_CARD          ((uint32_t)0x00000006)
#define HIGH_CAPACITY_MMC_CARD                ((uint32_t)0x00000007)


extern HAL_SD_CardInfoTypeDef SDCardInfo;
/* USER CODE END Private defines */

void MX_SDIO_SD_Init(void);

/* USER CODE BEGIN Prototypes */
void show_sdcard_info(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SDIO_H__ */

