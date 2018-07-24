#include <iostream>
#include "libusb.h"

using namespace std;

int main()
{
	//libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
	libusb_device_handle *dev_handle; //a device handle
	libusb_context *ctx = NULL; //a libusb session
	int r; //for return values
	ssize_t cnt; //holding number of devices in list
	r = libusb_init(&ctx); //initialize the library for the session we just declared
	if (r < 0)
	{
		cout << "Init Error " << r << endl; //there was an error
		return 1;
	}
	libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation

	//cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
	//if (cnt < 0)
	//{
	//	cout << "Get Device Error" << endl; //there was an error
	//	return 1;
	//}
	//cout << cnt << " Devices in list." << endl;

	dev_handle = libusb_open_device_with_vid_pid(ctx, 0x0483, 0x5710); //these are vendorID and productID I found for my usb device
	if (dev_handle == NULL)
		cout << "Cannot open device" << endl;
	else
		cout << "Device Opened" << endl;
	//libusb_free_device_list(devs, 1); //free the list, unref the devices in it

	unsigned char *data = new unsigned char[1]; //data to write

	if (libusb_kernel_driver_active(dev_handle, 0) == 1)
	{
		//find out if kernel driver is attached
		cout << "Kernel Driver Active" << endl;
		if (libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
			cout << "Kernel Driver Detached!" << endl;
	}
	r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had just 1)
	if (r < 0)
	{
		cout << "Cannot Claim Interface" << endl;
		return 1;
	}
	cout << "Claimed Interface" << endl;

	unsigned char* data_dummy = NULL;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	r = libusb_control_transfer(dev_handle, (unsigned char)(LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_INTERFACE),
		0xAA, 0, 0, data_dummy, 0, 1000); //my device's out endpoint
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	r = libusb_release_interface(dev_handle, 0); //release the claimed interface
	if (r != 0)
	{
		cout << "Cannot Release Interface" << endl;
		return 1;
	}
	cout << "Released Interface" << endl;

	libusb_close(dev_handle); //close the device we opened
	libusb_exit(ctx); //needs to be called to end the

	delete[] data; //delete the allocated memory for data
	return 0;
}
