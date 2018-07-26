#ifndef __MAIN_H__
#define __MAIN_H__


#include "stm32f3_discovery.h"
#include "stm32f3_discovery_accelerometer.h"
#include "stm32f3_discovery_gyroscope.h"


#define KEY_PRESSED     0x01
#define KEY_NOT_PRESSED 0x00


/* It is possible to remap the USB interrupts (USB_LP and USB_WKUP) on interrupt
   lines 75 and 76.
   Uncomment the line below to select your USB Interrupt Line */

#define USE_USB_INTERRUPT_DEFAULT   1
//#define USE_USB_INTERRUPT_REMAPPED   1

#if !defined (USE_USB_INTERRUPT_DEFAULT) && !defined (USE_USB_INTERRUPT_REMAPPED)
	#error "Missing define Please Define Your Interrupt Mode By UnComment Line in main.h file"
#endif


extern void SystemClock_Config(void);


#define USE_FULL_ASSERT 1U

extern void _Error_Handler(char *, int);
#define Error_Handler() _Error_Handler(__FILE__, __LINE__)


#endif /* __MAIN_H__ */
