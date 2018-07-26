#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"


uint8_t *USBD_CUSTOM_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CUSTOM_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CUSTOM_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CUSTOM_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CUSTOM_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CUSTOM_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_CUSTOM_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);


USBD_DescriptorsTypeDef CUSTOM_Desc =
{
	USBD_CUSTOM_DeviceDescriptor,
	USBD_CUSTOM_LangIDStrDescriptor,
	USBD_CUSTOM_ManufacturerStrDescriptor,
	USBD_CUSTOM_ProductStrDescriptor,
	USBD_CUSTOM_SerialStrDescriptor,
	USBD_CUSTOM_ConfigStrDescriptor,
	USBD_CUSTOM_InterfaceStrDescriptor
};


/* USB Standard Device Descriptor */
const uint8_t USBD_DeviceDesc[USB_LEN_DEV_DESC] =
{
	0x12,                       /* bLength */
	USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
	0x00,                       /* bcdUSB */
	0x02,						/* bcdUSB */
	0x00,                       /* bDeviceClass */
	0x00,                       /* bDeviceSubclass */
	0x00,                       /* bDeviceProtocol */
	USB_MAX_EP0_SIZE,           /* bMaxPacketSize0 */
	LOBYTE(USBD_VID),           /* idVendor */
	HIBYTE(USBD_VID),           /* idVendor */
	LOBYTE(USBD_PID),           /* idProduct */
	HIBYTE(USBD_PID),           /* idProduct */
	0x00,                       /* bcdDevice */
	0x00,                       /* bcdDevice */
	USBD_IDX_MFC_STR,           /* iManufacturer */
	USBD_IDX_PRODUCT_STR,       /* iProduct */
	USBD_IDX_SERIAL_STR,        /* iSerialNumber */
	USBD_MAX_NUM_CONFIGURATION  /* bNumConfigurations */
}; /* USB_DeviceDescriptor */


/* USB Standard Device Descriptor */
const uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC]= 
{
	USB_LEN_LANGID_STR_DESC,
	USB_DESC_TYPE_STRING,
	LOBYTE(USBD_LANGID_STRING),
	HIBYTE(USBD_LANGID_STRING)
};


uint8_t USBD_StringSerial[USB_SIZ_STRING_SERIAL] =
{
	USB_SIZ_STRING_SERIAL,
	USB_DESC_TYPE_STRING
};


uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ];


static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);


/**
 * @brief  Returns the device descriptor.
 * @param  speed: Current device speed
 * @param  length: Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_CUSTOM_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	*length = sizeof(USBD_DeviceDesc);
	return (uint8_t*)USBD_DeviceDesc;
}


/**
 * @brief  Returns the LangID string descriptor.
 * @param  speed: Current device speed
 * @param  length: Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_CUSTOM_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	*length = sizeof(USBD_LangIDDesc);
	return (uint8_t*)USBD_LangIDDesc;
}


/**
 * @brief  Returns the product string descriptor.
 * @param  speed: Current device speed
 * @param  length: Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_CUSTOM_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)USBD_PRODUCT_FS_STRING, USBD_StrDesc, length);
	return USBD_StrDesc;
}


/**
 * @brief  Returns the manufacturer string descriptor.
 * @param  speed: Current device speed
 * @param  length: Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_CUSTOM_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);
	return USBD_StrDesc;
}


/**
 * @brief  Returns the serial number string descriptor.
 * @param  speed: Current device speed
 * @param  length: Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_CUSTOM_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	*length = USB_SIZ_STRING_SERIAL;

	/* Update the serial number string descriptor with the data from the 96-bit unique ID*/
	uint32_t deviceserial0 = HAL_GetUIDw0();
	IntToUnicode(deviceserial0, &USBD_StringSerial[2], 8);
	uint32_t deviceserial1 = HAL_GetUIDw1();
	IntToUnicode(deviceserial1, &USBD_StringSerial[18], 8);
	uint32_t deviceserial2 = HAL_GetUIDw2();
	IntToUnicode(deviceserial2, &USBD_StringSerial[34], 8);

	return USBD_StringSerial;
}


/**
 * @brief  Returns the configuration string descriptor.
 * @param  speed: Current device speed
 * @param  length: Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_CUSTOM_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)USBD_CONFIGURATION_FS_STRING, USBD_StrDesc, length);
	return USBD_StrDesc;
}


/**
 * @brief  Returns the interface string descriptor.
 * @param  speed: Current device speed
 * @param  length: Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_CUSTOM_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)USBD_INTERFACE_FS_STRING, USBD_StrDesc, length);
	return USBD_StrDesc;
}


/**
 * @brief  Convert Hex 32Bits value into char
 * @param  value: value to convert
 * @param  pbuf: pointer to the buffer
 * @param  len: buffer length
 * @retval None
 */
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len)
{
	uint8_t idx = 0;

	for(idx = 0; idx < len; idx++)
	{
		if(((value >> 28)) < 0xA)
		{
			pbuf[2 * idx] = (value >> 28) + '0';
		}
		else
		{
			pbuf[2 * idx] = (value >> 28) + 'A' - 10;
		}

		value = value << 4;

		pbuf[2 * idx + 1] = 0;
	}
}


#ifdef USBD_SUPPORT_USER_STRING

	uint8_t *USBD_CUSTOM_USRStringDesc(struct _USBD_HandleTypeDef *pdev, uint8_t index, uint16_t *length)
	{
		switch (index)
		{
		case 0:
			USBD_GetString((uint8_t *)USBD_USER_STRING0, USBD_StrDesc, length);
			return USBD_StrDesc;
		default:
			length = 0;
			return NULL;
		}
	}

#endif /* USBD_SUPPORT_USER_STRING */
