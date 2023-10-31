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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define center 2048;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t buffer[2] = {0};
int16_t xy[2] = { 0 };
int32_t LED[4] = { 0 };
uint16_t aux = 0;

enum
{
	W = 0, N, E, S
};

enum
{
	waiting = 0,
	detect,
	button_press,
};

enum
{
	off = 0,
	twohz,
	fourhz,
	on,
};

int state = off;
int button = waiting;

uint8_t sinal_bot_pressionado = 0;


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
  MX_TIM2_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	//HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	//HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
  //HAL_ADC_Start_DMA(&hadc1, (uint32_t *) buffer, 2);
	//HAL_DMA_Start(&hdma_memtomem_dma2_stream1, (uint32_t)LED, (uint32_t)&(htim4.Instance->CCR1), 4);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  switch (button)
	  {
	  case waiting:
		  break;
	  case detect:
		  break;
	  case button_press:
		  sinal_bot_pressionado = 0;
		  aux++;
		  button = waiting;
		  break;
	  default:
		  break;
	  }
	  
	  switch (state)
	  {
	  case off:
		  if (sinal_bot_pressionado) state = twohz;
		  htim4.Instance->CCR2 = 0;
		  break;
	  case twohz:
		  if (sinal_bot_pressionado) state = fourhz;
		  htim4.Instance->CCR2 = htim4.Instance->ARR / 2;
		  htim4.Instance->PSC = 699;
		  break;
	  case fourhz:
		  if (sinal_bot_pressionado) state = on;
		  htim4.Instance->CCR2 = htim4.Instance->ARR / 2;
		  htim4.Instance->PSC = 349;
		  break;
	  case on:
		  if (sinal_bot_pressionado) state = off;
		  htim4.Instance->CCR2 = htim4.Instance->ARR;
		  break;
	  default:
		  break;
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if (GPIO_Pin != GPIO_PIN_0) return;
	EXTI->RTSR = EXTI->RTSR & ~0x1;
	EXTI->IMR = EXTI->IMR & ~0x1;
	//HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	__NVIC_ClearPendingIRQ(EXTI0_IRQn);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
	button = detect;
	HAL_TIM_Base_Start_IT(&htim3);
	
}

void DMA_Callback(DMA_HandleTypeDef *_hdma)
{
	
	
	
}

void checkstate()
{
	
	
	
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

	uint8_t i;
	for (i = 0; i < 2; i++)
	{
		xy[i] = buffer[i] - center;

	}
	
	//state = HAL_OK;
	return;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim3)
	{
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
		{
			button = button_press;
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
			sinal_bot_pressionado = 1;
		}
		else
		{
			button = waiting;
		}
		EXTI->RTSR = 1;
		EXTI->IMR = 1;
		//HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		HAL_TIM_Base_Stop_IT(htim);

	}
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
