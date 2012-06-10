#include "button.h"

struct libusb_device_handle *openButton() {
    libusb_context *ctx = NULL;
    if(libusb_init(&ctx) != 0) {
        printf("Cannot init libusb!\n");
        return NULL;
    }

    struct libusb_device_handle *hDev = libusb_open_device_with_vid_pid(ctx, 0x1d34, 0xd);
    if(hDev == NULL) {
        printf("Cannot access the button! Is it connected?\n");
        return NULL;
    }

    if(libusb_kernel_driver_active(hDev, 0) == 1) {
        if(libusb_detach_kernel_driver(hDev, 0) != 0) {
            printf("Device is busy. :(\n");
            return NULL;
        }
    }

    int result = libusb_claim_interface(hDev, 0);
    if(result < 0) {
        printf("Cannot claim the button - Error code is %i\n", result);
        return NULL;
    }
    
    return hDev;
}

unsigned char wasButtonPushed(struct libusb_device_handle *dev) {
    if(libusb_control_transfer(dev, CONTROL_REQUEST_TYPE_IN, HID_SET_REPORT,
            (HID_REPORT_TYPE_OUTPUT<<8)|0x00, 0, HID_CTRL_DATA, 8, 500) < 0) {
        printf("Cannot write to the button.\n");
        return 0;
    }

    int bytesRead=0;
    char buffer[8];
    int result = libusb_interrupt_transfer(dev, 0x81, buffer, 8, &bytesRead, 500);
    if(result < 0) {
        printf("Failed to read from button.\n");
        return 0;
    }

    if(buffer[0] == 0x16) return 1;
    return 0;
}
