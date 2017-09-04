/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "APA102.h"
#include "limits.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
// === APA102 Strip Configurable Parameters ===
#define APA102_STRIPLEN   144      // Length of APA102 LED Strip
#define APA102_SPI_HANDLE hspi2    // SPI port connected to APA102 LED Strip

// === APA102 Strip Protocol Parameters ===
#define APA102_BYTES_PER_PIXEL   4
#define APA102_START_FRAME_BYTES 4
#define APA102_END_FRAME_BYTES   12
#define APA102_STRIP_UPDATE_PACKET_BYTES (APA102_START_FRAME_BYTES + (APA102_STRIPLEN * APA102_BYTES_PER_PIXEL) + APA102_END_FRAME_BYTES)
uint8_t APA102_StartFrameByte                          = {0b00000000};
uint8_t APA102_EndFrameByte                            = {0b11111111};
uint8_t APA102_Strip[APA102_STRIP_UPDATE_PACKET_BYTES] = {0};
#define APA102_MAX_STRIP_LENGTH  (APA102_START_FRAME_BYTES + (UINT_MAX / APA102_BYTES_PER_PIXEL) + APA102_END_FRAME_BYTES)

// APA102_stripStatus - Global status of APA102 strip.  Primarily used to indicate whether a strip update is currently underway.
typedef enum
{
  APA102_UNKNOWN   = 0x00U,
  APA102_ERROR     = 0x01U,
  APA102_IDLE      = 0x05U,
  APA102_UPDATING  = 0x06U
} APA102_stripStatus;
APA102_stripStatus APA102_stripStatus1 = APA102_UNKNOWN;

// APA102_result - Return status for APA102 related function calls.
typedef enum
{
  APA102_SUCCESS   = 0x00U,
  APA102_FAILURE   = 0x01U
} APA102_result;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
APA102_result APA102_Update(void);
APA102_result APA102_Init(void);
APA102_result APA102_SetPixel(uint32_t, uint8_t, uint16_t, uint16_t);
APA102_result APA102_SetStrip(uint8_t, uint16_t, uint16_t);
void HAL_SPI_TxCpltCallback (SPI_HandleTypeDef * hspi);


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */


/*
 * APA102_Update - Initiates DMA transmit of current pixel data.
 *  arguments:
 *    returns: Status flag based on HAL status.  Failures are not considered
 *             show-stopping based on streaming nature of a typical implementation.
 */
APA102_result APA102_Update()
{
	// Indicate that APA102 strip update is underway.
    APA102_stripStatus1 = APA102_UPDATING;

    // Initiates DMA transmit of current pixel data.  Check HAL return status.
	if (HAL_SPI_Transmit_DMA(&APA102_SPI_HANDLE, APA102_Strip, APA102_STRIP_UPDATE_PACKET_BYTES) != HAL_OK)
	{
		APA102_stripStatus1 = APA102_ERROR;
		return APA102_FAILURE;
	}
	else
	{
		return APA102_SUCCESS;
	}

}


/*
 * APA102_Init - Initializes array containing pixel data.
 *  arguments:
 *    returns: Status flag based on HAL status.  Failures are not considered
 *             show-stopping based on streaming nature of a typical implementation.
 */
APA102_result APA102_Init()
{
	// Set strip status to UNKNOWN when initialized.
	APA102_stripStatus1 = APA102_UNKNOWN;

	// Sanity check strip length
	if (APA102_STRIPLEN > APA102_MAX_STRIP_LENGTH)
	{
		// Halt; cannot recover from a pixel strip data array that cannot be properly initialized.
		_Error_Handler(__FILE__, __LINE__);
	}

	// Copy start frame data into strip update packet.
	for (int i = 0; i < APA102_START_FRAME_BYTES; i++)
	{
	    APA102_Strip[i] = APA102_StartFrameByte;
	}


	// Copy end frame data into strip update packet.
	int j = sizeof(APA102_Strip);
	for (int i = 0; i < APA102_START_FRAME_BYTES; i++)
	{
	    APA102_Strip[j] = APA102_EndFrameByte;
	    j--;
    }


	// Initialize each pixel update frame to OFF
	for (int i = APA102_START_FRAME_BYTES; i < (APA102_STRIP_UPDATE_PACKET_BYTES - APA102_END_FRAME_BYTES); i+=APA102_START_FRAME_BYTES)
	{
		// First three bits must be HIGH, remaining five are a global pixel brightness that we'll default to max for the time being.
	    APA102_Strip[i] = 0b11111111;
	}

	// Return Status
	return APA102_SUCCESS;

}


/*
 * APA102_SetPixel - Sets a single pixel to the prescribed color intensities.
 *  arguments: pixel number in strip (1 based), red intensity, green intensity, blue intensity
 *    returns: Status flag based on HAL status.  Failures are not considered
 *             show-stopping based on streaming nature of a typical implementation.
 */
APA102_result APA102_SetPixel(uint32_t pixel, uint8_t red, uint16_t grn, uint16_t blu)
{
	// Variable Declarations
	uint32_t position = 0;

	// Sanity check pixel number input
	if (pixel > APA102_STRIPLEN)
	{
		return APA102_FAILURE;
	}

	// Account for 0 based array
	pixel --;

	// Calculate desired pixel data's position in the strip array.
	position = (APA102_START_FRAME_BYTES + (pixel * APA102_BYTES_PER_PIXEL));

	// Insert desired pixel data into strip array.
	APA102_Strip[position + 1] = blu;
	APA102_Strip[position + 2] = grn;
	APA102_Strip[position + 3] = red;

	// Return Status
	return APA102_SUCCESS;
}


/*
 * APA102_SetStrip - Sets the entire strip to the prescribed color intensities.
 *  arguments: red intensity, green intensity, blue intensity
 *    returns: Status flag based on HAL status.  Failures are not considered
 *             show-stopping based on streaming nature of a typical implementation.
 */
APA102_result APA102_SetStrip(uint8_t red, uint16_t grn, uint16_t blu)
{
	// Update strip color, pixel by pixel.
	for (int i = 1; i <= APA102_STRIPLEN; i++)
	{
        APA102_SetPixel(i, red, grn, blu);
	}

	// Return Status
	return APA102_SUCCESS;
}


void HAL_SPI_TxCpltCallback (SPI_HandleTypeDef * hspi)
{
	// Indicate that APA102 strip update is complete.
    if (hspi == &APA102_SPI_HANDLE)
    {
    	APA102_stripStatus1 = APA102_IDLE;
    }

}



/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_SPI2_Init();

  /* USER CODE BEGIN 2 */
  APA102_Init();
  APA102_Update();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */


	  APA102_SetStrip(0, 0, 0);
	  APA102_Update();
	  HAL_Delay(500);
	  APA102_SetStrip(0, 1, 1);
	  APA102_Update();
	  HAL_Delay(500);



	  /*
	  APA102_SetPixel(10, 0, 0, 255);
	  APA102_SetPixel(100, 0, 0, 255);
	  APA102_SetPixel(144, 0, 0, 255);
	  APA102_SetPixel(143, 0, 0, 255);
	  APA102_SetPixel(142, 0, 0, 255);
	  APA102_SetPixel(141, 0, 0, 255);
	  APA102_SetPixel(140, 0, 0, 255);
	  APA102_Update();
	  HAL_Delay(500);
	  APA102_SetPixel(10, 255, 0, 0);
	  APA102_SetPixel(100, 255, 0, 0);
	  APA102_SetPixel(144, 255, 0, 0);
	  APA102_SetPixel(143, 255, 0, 0);
	  APA102_SetPixel(142, 255, 0, 0);
	  APA102_SetPixel(141, 255, 0, 0);
	  APA102_SetPixel(140, 255, 0, 0);
	  APA102_Update();
	  //APA102_Update();
	  HAL_Delay(500);
      */



	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);



  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI2 init function */
static void MX_SPI2_Init(void)
{

  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PA2   ------> USART2_TX
     PA3   ------> USART2_RX
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {

  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
