#ifndef __USBD_CONF_H
#define __USBD_CONF_H


#include "stm32f3xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Common Config */
#define USBD_MAX_NUM_INTERFACES               1
#define USBD_MAX_NUM_CONFIGURATION            1
#define USBD_MAX_STR_DESC_SIZ                 0x100
#define USBD_SUPPORT_USER_STRING              1
#define USBD_SELF_POWERED                     0
#define USBD_DEBUG_LEVEL                      2


/* DEBUG macros */
#if (USBD_DEBUG_LEVEL > 1)
	extern void USBD_ErrLog(const char *fmt, ...);
#else
	#define USBD_ErrLog(...)
#endif /* USBD_DEBUG_LEVEL */


#endif /* __USBD_CONF_H */
