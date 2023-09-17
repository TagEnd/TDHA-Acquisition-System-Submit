/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "dma.h"
#include "lwip.h"
#include "rtc.h"
#include "sdio.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ad7606.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
AD7606Dev ad7606dev;
// AD7606Dev ad7606dev __attribute__((at(0X64080000)));
// struct netif gnetif;
// struct dhcp *dhcp;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_FSMC_Init();
  MX_SDIO_SD_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  MX_LWIP_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  TCP_Client_Init();

  printf("\r\nUsart1 Test11111!\r\n");
  ad7606ini(&ad7606dev);

  HAL_GPIO_WritePin(ADC_RST_GPIO_Port, ADC_RST_Pin, GPIO_PIN_SET);

  HAL_Delay(500);
  HAL_GPIO_WritePin(ADC_RST_GPIO_Port, ADC_RST_Pin, GPIO_PIN_RESET);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

  // TestRAM();

  // uint8_t CRCTest[20];
  // uint32_t CrCValue[3] = {0, 0, 0};
  // uint8_t CRC_Index = 0;
  // uint32_t CrcRes;
  // uint8_t k = 0;
  // // ff0007e7030701212c010141
  // // ff0007e7030701212c010141
  // CRCTest[CRC_Index++] = 0xff;
  // CRCTest[CRC_Index++] = 0x00;
  // CRCTest[CRC_Index++] = 0x07;
  // CRCTest[CRC_Index++] = 0xe7;

  // CRCTest[CRC_Index++] = 0x03;
  // CRCTest[CRC_Index++] = 0x07;
  // CRCTest[CRC_Index++] = 0x01;
  // CRCTest[CRC_Index++] = 0x21;

  // CRCTest[CRC_Index++] = 0x2c;
  // CRCTest[CRC_Index++] = 0x01;
  // CRCTest[CRC_Index++] = 0x01;
  // CRCTest[CRC_Index++] = 0x41;

  // CRCTest[CRC_Index++] = 0xe7;
  // CRCTest[CRC_Index++] = 0x07;
  // CRCTest[CRC_Index++] = 0x00;
  // CRCTest[CRC_Index++] = 0xff;

  // CRCTest[CRC_Index++] = 0x21;
  // CRCTest[CRC_Index++] = 0x01;
  // CRCTest[CRC_Index++] = 0x07;
  // CRCTest[CRC_Index++] = 0x03;

  // CRCTest[CRC_Index++] = 0x41;
  // CRCTest[CRC_Index++] = 0x01;
  // CRCTest[CRC_Index++] = 0x01;
  // CRCTest[CRC_Index++] = 0x2c;

  // for (uint8_t i = 0; i < CRC_Index; i = i + 4)
  // {
  //   uint8_t t = i + 3;
  //   CrCValue[k] = CRCTest[t--];
  //   CrCValue[k] += CRCTest[t--] << 8;
  //   CrCValue[k] += CRCTest[t--] << 16;
  //   CrCValue[k] += CRCTest[t--] << 24;
  //   k++;
  // }

  // CrcRes = HAL_CRC_Calculate(&hcrc, (uint32_t *)CrCValue, 3);
  // CRCTest[CRC_Index++] = CrcRes;

  // LWIP_Send_data(CRCTest, CRC_Index, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    ana_AD7606();
    // lv_timer_handler();
    // HAL_Delay(5);
    MX_LWIP_Process();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

