#ifndef __USB_CUSTOM_H
#define __USB_CUSTOM_H

#include  "usbd_ioreq.h"

#define USB_CUSTOM_CONFIG_DESC_SIZE 18

extern USBD_ClassTypeDef USBD_CUSTOM_ClassDriver;
#define USBD_CUSTOM_CLASS &USBD_CUSTOM_ClassDriver

#endif  /* __USB_CUSTOM_H */
