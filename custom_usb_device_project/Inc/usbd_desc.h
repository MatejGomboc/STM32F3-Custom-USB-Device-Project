#ifndef __USBD_DESC_H
#define __USBD_DESC_H

#include "usbd_def.h"

#define USBD_VID 0x0483
#define USBD_PID 0x5710

#define USBD_LANGID_STRING 0x409

#define USB_SIZ_STRING_SERIAL 0x32

#define USBD_MANUFACTURER_STRING     "Unknown Manufacturer"
#define USBD_PRODUCT_FS_STRING       "CUSTOM Device in FS Mode"
#define USBD_CONFIGURATION_FS_STRING "CUSTOM Configuration"
#define USBD_INTERFACE_FS_STRING     "CUSTOM Interface"
#define USBD_USER_STRING0            "CUSTOM User String"

extern USBD_DescriptorsTypeDef CUSTOM_Desc;

#ifdef USBD_SUPPORT_USER_STRING

	extern uint8_t *USBD_CUSTOM_USRStringDesc(struct _USBD_HandleTypeDef *pdev, uint8_t index, uint16_t *length);

#endif /* USBD_SUPPORT_USER_STRING */

#endif /* __USBD_DESC_H */
