#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>

static const int CONTROL_REQUEST_TYPE_IN = 0x21;
static const int HID_SET_REPORT = 0x09;
static const int HID_REPORT_TYPE_OUTPUT = 0x02;
static const char HID_CTRL_DATA[8] = {0,0,0,0,0,0,0,2};

struct libusb_device_handle *openButton();
unsigned char wasButtonPushed(struct libusb_device_handle *dev);
