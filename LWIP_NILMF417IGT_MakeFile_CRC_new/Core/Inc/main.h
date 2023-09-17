/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOH
#define LCD_CS_Pin GPIO_PIN_4
#define LCD_CS_GPIO_Port GPIOA
#define LCD_RES_Pin GPIO_PIN_0
#define LCD_RES_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOB
#define LCD_BLK_Pin GPIO_PIN_2
#define LCD_BLK_GPIO_Port GPIOB
#define ADC_OS0_Pin GPIO_PIN_13
#define ADC_OS0_GPIO_Port GPIOB
#define ADC_OS1_Pin GPIO_PIN_14
#define ADC_OS1_GPIO_Port GPIOB
#define ADC_OS2_Pin GPIO_PIN_15
#define ADC_OS2_GPIO_Port GPIOB
#define ADC_RANG_Pin GPIO_PIN_8
#define ADC_RANG_GPIO_Port GPIOA
#define ADC_REF_Pin GPIO_PIN_13
#define ADC_REF_GPIO_Port GPIOH
#define ADC_STANDBY_Pin GPIO_PIN_15
#define ADC_STANDBY_GPIO_Port GPIOH
#define ADC_RST_Pin GPIO_PIN_6
#define ADC_RST_GPIO_Port GPIOD
#define SdDetect_Pin GPIO_PIN_10
#define SdDetect_GPIO_Port GPIOG
#define LCD_CLK_Pin GPIO_PIN_3
#define LCD_CLK_GPIO_Port GPIOB
#define LCD_SDA_Pin GPIO_PIN_5
#define LCD_SDA_GPIO_Port GPIOB
#define BUSY_INT_Pin GPIO_PIN_8
#define BUSY_INT_GPIO_Port GPIOB
#define BUSY_INT_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
