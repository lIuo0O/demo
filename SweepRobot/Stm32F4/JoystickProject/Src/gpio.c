/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "gpio.h"

#include "RocLog.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
static GpioIrqHandler *GpioIrq[16] = { NULL };
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(ROC_LED_1_PORT, ROC_LED_1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ROC_LED_2_PORT, ROC_LED_2_PIN, GPIO_PIN_SET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(ROC_BEEPER_GPIO_PORT, ROC_BEEPER_CTRL_PIN, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(ROC_OLED_RST_PORT, ROC_OLED_RST_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROC_OLED_DC_PORT, ROC_OLED_DC_PIN, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(ROC_RF_SET_PORT, ROC_RF_SET_PIN, GPIO_PIN_SET);

    /*Configure GPIO pins : LED1 Pin */
    GPIO_InitStruct.Pin = ROC_LED_1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ROC_LED_1_PORT, &GPIO_InitStruct);

    /*Configure GPIO pins : LED2 Pin */
    GPIO_InitStruct.Pin = ROC_LED_2_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ROC_LED_2_PORT, &GPIO_InitStruct);

    /*Configure GPIO pins : Beeper Pin */
    GPIO_InitStruct.Pin = ROC_BEEPER_CTRL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ROC_BEEPER_GPIO_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_1_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_1_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_2_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_2_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_2_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_3_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_3_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_4_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_4_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_4_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_5_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_5_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_5_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_6_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_6_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_6_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_7_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_7_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_7_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_8_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_8_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_8_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_9_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_9_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_9_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_10_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_10_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_10_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_11_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_11_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_12_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_12_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_12_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_13_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_13_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_13_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_14_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_14_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_14_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_15_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_15_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_15_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_LT_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_LT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_LT_PORT, &GPIO_InitStruct);

    /*Configure GPIO pin : ROC_KEY_RT_PIN */
    GPIO_InitStruct.Pin = ROC_KEY_RT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ROC_KEY_RT_PORT, &GPIO_InitStruct);

    /*Configure GPIO pins : OLED Pin */
    GPIO_InitStruct.Pin = ROC_OLED_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ROC_OLED_RST_PORT, &GPIO_InitStruct);

    /*Configure GPIO pins : OLED Pin */
    GPIO_InitStruct.Pin = ROC_OLED_DC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ROC_OLED_DC_PORT, &GPIO_InitStruct);

    /*Configure GPIO pins : RF_SET Pin */
    GPIO_InitStruct.Pin = ROC_RF_SET_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ROC_RF_SET_PORT, &GPIO_InitStruct);

//    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 14, 0);
//    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/* USER CODE BEGIN 2 */
/* Private function prototypes -----------------------------------------------*/

static uint8_t HW_GPIO_GetBitPos(uint16_t GPIO_Pin);

/**
  * @brief  Gets IRQ number as a function of the GPIO_Pin.
  * @param  GPIO_Pin: Specifies the pins connected to the EXTI line.
  * @retval IRQ number
  */
IRQn_Type MSP_GetIRQn( uint16_t GPIO_Pin)
{
  switch( GPIO_Pin )
  {
    case GPIO_PIN_0:  return EXTI0_IRQn;
    case GPIO_PIN_1:  return EXTI1_IRQn;
    case GPIO_PIN_2:  return EXTI2_IRQn;
    case GPIO_PIN_3:  return EXTI3_IRQn;
    case GPIO_PIN_4:  return EXTI4_IRQn;
    case GPIO_PIN_5:  return EXTI9_5_IRQn;
    case GPIO_PIN_6:  return EXTI9_5_IRQn;
    case GPIO_PIN_7:  return EXTI9_5_IRQn;
    case GPIO_PIN_8:  return EXTI9_5_IRQn;
    case GPIO_PIN_9:  return EXTI9_5_IRQn;
    case GPIO_PIN_10: return EXTI15_10_IRQn;
    case GPIO_PIN_11: return EXTI15_10_IRQn;
    case GPIO_PIN_12: return EXTI15_10_IRQn;
    case GPIO_PIN_13: return EXTI15_10_IRQn;
    case GPIO_PIN_14: return EXTI15_10_IRQn;
    case GPIO_PIN_15: return EXTI15_10_IRQn;
    default:return EXTI15_10_IRQn;
  }
}

/* Exported functions ---------------------------------------------------------*/
/*!
 * @brief Initializes the given GPIO object
 *
 * @param  GPIOx: where x can be (A..E and H)
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @param [IN] initStruct  GPIO_InitTypeDef intit structure
 * @retval none
 */
void HW_GPIO_Init( GPIO_TypeDef* port, uint16_t GPIO_Pin, GPIO_InitTypeDef* initStruct)
{

  RCC_GPIO_CLK_ENABLE(  (uint32_t) port);

  initStruct->Pin = GPIO_Pin ;

  HAL_GPIO_Init( port, initStruct );
}

/*!
 * @brief Records the interrupt handler for the GPIO  object
 *
 * @param  GPIOx: where x can be (A..E and H) 
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @param [IN] prio       NVIC priority (0 is highest)
 * @param [IN] irqHandler  points to the  function to execute
 * @retval none
 */
void HW_GPIO_SetIrq( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t prio,  GpioIrqHandler *irqHandler )
{
  IRQn_Type IRQnb;
  
  uint32_t BitPos = HW_GPIO_GetBitPos( GPIO_Pin ) ;
  
  if ( irqHandler != NULL)
  {
    GpioIrq[ BitPos ] = irqHandler;

    IRQnb = MSP_GetIRQn( GPIO_Pin );

    HAL_NVIC_SetPriority( IRQnb , prio, 0);
    
    HAL_NVIC_EnableIRQ( IRQnb );
    ROC_LOGN("%d", IRQnb);
  }
  else
  {
    GpioIrq[ BitPos ] = NULL;
  }
}

/*!
 * @brief Execute the interrupt from the object
 *
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @retval none
 */
void HW_GPIO_IrqHandler( uint16_t GPIO_Pin )
{
  uint32_t BitPos = HW_GPIO_GetBitPos( GPIO_Pin );
  
  if ( GpioIrq[ BitPos ]  != NULL)
  {
    GpioIrq[ BitPos ] ( );
  }
}

/*!
 * @brief Writes the given value to the GPIO output
 *
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @param [IN] value New GPIO output value
 * @retval none
 */
void HW_GPIO_Write( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,  uint32_t value )
{
  HAL_GPIO_WritePin( GPIOx, GPIO_Pin , (GPIO_PinState) value );
}

/*!
 * @brief Reads the current GPIO input value
 *
 * @param  GPIOx: where x can be (A..E and H) 
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @retval value   Current GPIO input value
 */
uint32_t HW_GPIO_Read( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin )
{
  return HAL_GPIO_ReadPin( GPIOx, GPIO_Pin);
}

/* Private functions ---------------------------------------------------------*/

/*!
 * @brief Get the position of the bit set in the GPIO_Pin
 * @param  GPIO_Pin: specifies the port bit to be written.
 *                   This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                   All port bits are not necessarily available on all GPIOs.
 * @retval the position of the bit
 */
static uint8_t HW_GPIO_GetBitPos(uint16_t GPIO_Pin)
{
  uint8_t PinPos=0;
  
  if ( ( GPIO_Pin & 0xFF00 ) != 0) { PinPos |= 0x8; }
  if ( ( GPIO_Pin & 0xF0F0 ) != 0) { PinPos |= 0x4; }
  if ( ( GPIO_Pin & 0xCCCC ) != 0) { PinPos |= 0x2; }
  if ( ( GPIO_Pin & 0xAAAA ) != 0) { PinPos |= 0x1; }
  
  return PinPos;
}

/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
