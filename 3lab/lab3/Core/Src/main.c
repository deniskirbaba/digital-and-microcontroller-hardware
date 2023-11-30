/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <math.h>
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
int n;
int undef_flag = 1;
int n_r;
int res_n;
uint8_t rx_buffer[4];
char tx_buffer[5];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void set_line () {
    HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_SET); //A
    HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_SET); //B
    HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_SET); //C
    HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_SET); //D
    HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_SET); //E
    HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_SET);	//F
    HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_RESET);  //G
    HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp
}

void set_number (int number)
{
    switch (number)
    {
        case 0:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_RESET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_RESET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_RESET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_RESET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_RESET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_SET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 1:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_SET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_RESET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_SET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_SET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_SET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_SET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 2:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_RESET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_RESET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_SET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_RESET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_RESET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_SET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_RESET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 3:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_RESET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_RESET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_RESET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_SET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_SET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_RESET);  //G

            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 4:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_SET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_RESET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_SET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_SET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_RESET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_RESET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 5:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_RESET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_SET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_RESET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_SET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_RESET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_RESET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 6:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_RESET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_SET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_RESET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_RESET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_RESET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_RESET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 7:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_RESET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_RESET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_SET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_SET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_SET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_SET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 8:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_RESET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_RESET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_RESET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_RESET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_RESET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_RESET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }

        case 9:
        {
            HAL_GPIO_WritePin(GPIOA, a_Pin, GPIO_PIN_RESET); //A
            HAL_GPIO_WritePin(GPIOA, b_Pin, GPIO_PIN_RESET); //B
            HAL_GPIO_WritePin(GPIOA, c_Pin, GPIO_PIN_RESET); //C
            HAL_GPIO_WritePin(GPIOC, d_Pin, GPIO_PIN_RESET); //D
            HAL_GPIO_WritePin(GPIOC, e_Pin, GPIO_PIN_SET); //E
            HAL_GPIO_WritePin(GPIOD, f_Pin, GPIO_PIN_RESET);	//F
            HAL_GPIO_WritePin(GPIOC, g_Pin, GPIO_PIN_RESET);  //G
            HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_SET);  //dp

            break;
        }
    }
}

void display_undef () {
    HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_RESET);
    set_line();
    HAL_Delay(1);

    HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);
    set_line();
    HAL_Delay(1);

    HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);
    set_line();
    HAL_Delay(1);

    HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);
    set_line();
    HAL_Delay(1);
}

void display_number (int number){

    HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_RESET);
    set_number(number % 10);
    HAL_Delay(1);

    HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);
    set_number(number / 10 % 10);
    HAL_Delay(1);

    HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);
    set_number(number / 100 % 10);
    HAL_Delay(1);

    HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);
    set_number(number / 1000 % 10);
    HAL_Delay(1);

}
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, rx_buffer, sizeof(rx_buffer));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	if (undef_flag) {
		display_undef();
	}
	else {
		display_number(n);
	}
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 19200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, a_Pin|DIG3_Pin|c_Pin|b_Pin
                          |dp_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DIG4_Pin|d_Pin|e_Pin|g_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DIG1_Pin|DIG2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : a_Pin DIG3_Pin c_Pin b_Pin
                           dp_Pin */
  GPIO_InitStruct.Pin = a_Pin|DIG3_Pin|c_Pin|b_Pin
                          |dp_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DIG4_Pin d_Pin e_Pin g_Pin */
  GPIO_InitStruct.Pin = DIG4_Pin|d_Pin|e_Pin|g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DIG1_Pin DIG2_Pin */
  GPIO_InitStruct.Pin = DIG1_Pin|DIG2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : f_Pin */
  GPIO_InitStruct.Pin = f_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(f_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	n_r = ((int)rx_buffer[1] - 48) * 10 + ((int)rx_buffer[2] - 48);  // since the numbers (digits) start from 48 in ASCII code
	if (n_r == 0) {
		undef_flag = 1;
		sprintf(tx_buffer, "N--E");
	}
	else {
		undef_flag = 0;
		res_n = (int)round(log(n_r));
		n = res_n;
		sprintf(tx_buffer, "N0%uE", res_n);
	}
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)tx_buffer, sizeof(tx_buffer));
	HAL_UART_Receive_IT(&huart2, rx_buffer, sizeof(rx_buffer));
}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
