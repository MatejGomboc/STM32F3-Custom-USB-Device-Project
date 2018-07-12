#include "stm32f3xx_hal.h"
#include "stm32f3xx_it.h"


extern PCD_HandleTypeDef hpcd;


/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
	while (1);
}


/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
	while (1);
}


/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void)
{
	while (1);
}


/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void)
{
	while (1);
}


/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void)
{
	while (1);
}


/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{
	while (1);
}


/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
	while (1);
}


/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
	while (1);
}


/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles RCC global interrupt.
 */
void RCC_IRQHandler(void)
{
	while (1);
}


/**
  * @brief  This function handles USB Handler.
  * @param  None
  * @retval None
  */
#if defined (USE_USB_INTERRUPT_DEFAULT)
void USB_LP_CAN_RX0_IRQHandler(void)
#elif defined (USE_USB_INTERRUPT_REMAPPED)
void USB_LP_IRQHandler(void)
#endif
{
  HAL_PCD_IRQHandler(&hpcd);
}
