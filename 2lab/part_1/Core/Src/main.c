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
int count = 0;
uint8_t rx_buff[6];
char trans_string [5];
int ans_from_com=0;
float sin_ans=0;

//static uint8_t *rx_buffer;
//static uint8_t *tx_buffer;
//
//static uint8_t current_number = 0;
//static uint8_t changed_number = 0;
//static const float e = 2.71828;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

void setnumber (int number)
{
	switch (number)
	{
		case 0x2d:
				{
					//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET); //dot
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET); //A
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); //B
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET); //C
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET); //D
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET); //E
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);	//F
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);  //G
					break;
				}

		case 0:
			{
				//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET); //dot
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

void show_4dig_number(uint8_t count){

		HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_RESET);  //dp
		setnumber(count%10);
		HAL_Delay(1);

		HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_RESET);  //dp
		HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);  //dp
		setnumber(count/10%10);
		HAL_Delay(1);

		HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_RESET);  //dp
		HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);  //dp
		setnumber(count/100%10);
		HAL_Delay(1);

		HAL_GPIO_WritePin(GPIOB, DIG1_Pin, GPIO_PIN_RESET);  //dp
		HAL_GPIO_WritePin(GPIOB, DIG2_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOA, DIG3_Pin, GPIO_PIN_SET);  //dp
		HAL_GPIO_WritePin(GPIOC, DIG4_Pin, GPIO_PIN_SET);  //dp
		setnumber(count/1000%10);
		HAL_Delay(1);

}

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
//	rx_buffer = (uint8_t*) malloc(sizeof(uint8_t)*8);
//	tx_buffer = (uint8_t*) malloc(sizeof(uint8_t)*8);
//	HAL_UART_Receive_IT(&huart2, rx_buffer, 4);
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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//	  show_4dig_number(changed_number);
//    /* USER CODE BEGIN 3 */
//	  free(rx_buffer);
//	  free(tx_buffer);


//	  show_4dig_number(5);





  /* USER CODE END 3 */
}
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
  huart2.Init.BaudRate = 57600;
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

  /*Configure GPIO pins : RED_SW_Pin BLUE_SW_Pin */
  GPIO_InitStruct.Pin = RED_SW_Pin|BLUE_SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//	rx_buff[6]='\0';
//	ans_from_com=atoi(&rx_buff[1]);
//	sin_ans=sin(ans_from_com);
//
////	char *tmpSign = (sin_ans < 0) ? "-" : "";
////	float tmpVal = (sin_ans < 0) ? -sin_ans : sin_ans;
//
//	int tmpInt1 = tmpVal;                  // Get the integer (678).
//	float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
//	int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).
//	sprintf (trans_string, "%s%d.%04d\r\n", tmpSign, tmpInt1, tmpInt2);
//	//sprintf(trans_string, "%d ",sin_ans);
//	HAL_UART_Transmit_IT(&huart2, (uint8_t*) trans_string, sizeof(trans_string));
//////	show_4dig_number((int)trans_string);
////	//HAL_Delay(1);
//	HAL_UART_Receive_IT(&huart2,rx_buff,sizeof(rx_buff));

	HAL_UART_Transmit_IT(&huart2, (uint8_t*) trans_string, sizeof(trans_string));
			//HAL_Delay(1);
			HAL_UART_Receive_IT(&huart2,rx_buff,sizeof(rx_buff));

//	if (huart->Instance == huart2.Instance)
//	  {
//	    for (int i=1; i<3; i++){
//	      char sym = rx_buffer[i];
//	      current_number += sym;//) * pow(10, i%2);
//	    }
//	    changed_number = pow(e, current_number);
//	    sprintf(tx_buffer, "\r%d\n", changed_number);
//	    HAL_UART_Transmit_IT(&huart2, tx_buffer, 4);
//	    current_number = 0;

	//    HAL_UART_Transmit(&huart2,&rx_buffer,sizeof(rx_buffer), 100);
	//    HAL_UART_Receive_IT(&huart2, &rx_buffer, 1);
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