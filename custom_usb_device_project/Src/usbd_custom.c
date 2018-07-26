#include "usbd_custom.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"
#include "main.h"
#include <stdint.h>


static uint8_t USBD_CUSTOM_Init (USBD_HandleTypeDef *pdev, uint8_t cfgidx);

static uint8_t USBD_CUSTOM_DeInit (USBD_HandleTypeDef *pdev, uint8_t cfgidx);

static uint8_t USBD_CUSTOM_Setup (USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);

static uint8_t *USBD_CUSTOM_GetCfgDesc (uint16_t *length);

static uint8_t USBD_CUSTOM_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t USBD_CUSTOM_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t USBD_CUSTOM_EP0_RxReady (USBD_HandleTypeDef *pdev);

static uint8_t USBD_CUSTOM_EP0_TxReady (USBD_HandleTypeDef *pdev);

static uint8_t USBD_CUSTOM_SOF (USBD_HandleTypeDef *pdev);

static uint8_t USBD_CUSTOM_IsoInIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t USBD_CUSTOM_IsoOutIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);


USBD_ClassTypeDef USBD_CUSTOM_ClassDriver =
{
	USBD_CUSTOM_Init,
	USBD_CUSTOM_DeInit,
	USBD_CUSTOM_Setup,
	USBD_CUSTOM_EP0_TxReady,
	USBD_CUSTOM_EP0_RxReady,
	USBD_CUSTOM_DataIn,
	USBD_CUSTOM_DataOut,
	USBD_CUSTOM_SOF,
	USBD_CUSTOM_IsoInIncomplete,
	USBD_CUSTOM_IsoOutIncomplete,
	NULL,
	USBD_CUSTOM_GetCfgDesc,
	NULL,
	NULL

#ifdef USBD_SUPPORT_USER_STRING

	, USBD_CUSTOM_USRStringDesc

#endif /* USBD_SUPPORT_USER_STRING */

};


/* USB CUSTOM device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_CUSTOM_CfgDesc[USB_CUSTOM_CONFIG_DESC_SIZE] __ALIGN_END =
{
	0x09, /* bLength: Configuration Descriptor size */
	USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
	USB_CUSTOM_CONFIG_DESC_SIZE, /* wTotalLength: Bytes returned */
	0x00,
	0x01, /*bNumInterfaces: 1 interface*/
	0x01, /*bConfigurationValue: Configuration value*/
	USBD_IDX_CONFIG_STR, /*iConfiguration: Index of string descriptor describing the configuration*/
	0x00, /*bmAttributes: bus powered and does NOT support remote wake-up */
	0x32, /*bMaxPower 100 mA: this current is used for detecting Vbus*/
	/* 09 */

	/************** Descriptor of Joystick Mouse interface ****************/
	0x09, /*bLength: Interface Descriptor size*/
	USB_DESC_TYPE_INTERFACE, /*bDescriptorType: Interface descriptor type*/
	0x00, /*bInterfaceNumber: Number of Interface*/
	0x00, /*bAlternateSetting: Alternate setting*/
	0x00, /*bNumEndpoints*/
	0xFF, /*bInterfaceClass: Vendor*/
	0xFF, /*bInterfaceSubClass : Vendor*/
	0xFF, /*nInterfaceProtocol : Vendor*/
	USBD_IDX_INTERFACE_STR /*iInterface: Index of string descriptor*/
	/* 18 */
} ;


/**
 * @brief  USBD_CUSTOM_Init
 *         Initialize the CUSTOM interface
 * @param  pdev: device instance
 * @param  cfgidx: Configuration index
 * @retval status
 */
static uint8_t USBD_CUSTOM_Init (USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
	return USBD_OK;
}


/**
 * @brief  USBD_CUSTOM_Init
 *         DeInitialize the CUSTOM layer
 * @param  pdev: device instance
 * @param  cfgidx: Configuration index
 * @retval status
 */
static uint8_t USBD_CUSTOM_DeInit (USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
	return USBD_OK;
}


/**
 * @brief  USBD_CUSTOM_Setup
 *         Handle the CUSTOM specific requests
 * @param  pdev: instance
 * @param  req: usb requests
 * @retval status
 */
static uint8_t USBD_CUSTOM_Setup (USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
	switch (req->bmRequest & USB_REQ_TYPE_MASK)
	{
		case USB_REQ_TYPE_CLASS:
		{
			USBD_CtlError(pdev, req);
			return USBD_FAIL;
		}
		case USB_REQ_TYPE_STANDARD:
		{
			USBD_CtlError(pdev, req);
			return USBD_FAIL;
		}
		case USB_REQ_TYPE_VENDOR:
		{
			/* Toggling LED10 via control endpoint */
			if (req->bRequest == 0xAA)
				BSP_LED_Toggle(LED10);

			return USBD_OK;
		}
	}

	USBD_CtlError(pdev, req);
	return USBD_FAIL;
}


/**
 * @brief  USBD_CUSTOM_GetCfgDesc
 *         return configuration descriptor
 * @param  speed : current device speed
 * @param  length : pointer data length
 * @retval pointer to descriptor buffer
 */
static uint8_t *USBD_CUSTOM_GetCfgDesc (uint16_t *length)
{
	*length = sizeof (USBD_CUSTOM_CfgDesc);
	return USBD_CUSTOM_CfgDesc;
}


/**
 * @brief  USBD_CUSTOM_DataIn
 *         handle data IN Stage
 * @param  pdev: device instance
 * @param  epnum: endpoint index
 * @retval status
 */
static uint8_t USBD_CUSTOM_DataIn (USBD_HandleTypeDef *pdev,
		uint8_t epnum)
{
	return USBD_OK;
}


/**
  * @brief  USBD_TEMPLATE_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_CUSTOM_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
	return USBD_OK;
}


/**
  * @brief  USBD_TEMPLATE_EP0_RxReady
  *         handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t USBD_CUSTOM_EP0_RxReady (USBD_HandleTypeDef *pdev)
{
	return USBD_OK;
}


/**
  * @brief  USBD_TEMPLATE_EP0_TxReady
  *         handle EP0 TRx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t USBD_CUSTOM_EP0_TxReady (USBD_HandleTypeDef *pdev)
{
	return USBD_OK;
}


/**
  * @brief  USBD_TEMPLATE_SOF
  *         handle SOF event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t USBD_CUSTOM_SOF (USBD_HandleTypeDef *pdev)
{
	return USBD_OK;
}


/**
  * @brief  USBD_TEMPLATE_IsoINIncomplete
  *         handle data ISO IN Incomplete event
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_CUSTOM_IsoInIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
	return USBD_OK;
}


/**
  * @brief  USBD_TEMPLATE_IsoOutIncomplete
  *         handle data ISO OUT Incomplete event
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_CUSTOM_IsoOutIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
	return USBD_OK;
}
