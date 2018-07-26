#ifndef __STM32F3xx_IT_H
#define __STM32F3xx_IT_H

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void RCC_IRQHandler(void);

#if defined (USE_USB_INTERRUPT_DEFAULT)

	void USB_LP_CAN_RX0_IRQHandler(void);

#elif defined (USE_USB_INTERRUPT_REMAPPED)

	void USB_LP_IRQHandler(void);

#endif /* USE_USB_INTERRUPT_REMAPPED */

#endif /* __STM32F3xx_IT_H */
