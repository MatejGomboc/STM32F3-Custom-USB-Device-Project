#include "gpio.h"
#include "stm32f3xx_hal.h"


void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();

	/*Configure GPIO pin : PE9, LD3 red LED*/

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}


void MX_GPIO_DeInit(void)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_DISABLE();
}


void MX_GPIO_Set_LD3(bool on)
{
	if (on)
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
}

void MX_GPIO_Set_LD4(bool on)
{
	if (on)
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
}
