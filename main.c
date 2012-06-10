#include <stdio.h>
#include <stdlib.h>
#include "button.h"

int main() {
    struct libusb_device_handle *dev = openButton();
    do {
        if(wasButtonPushed(dev)) {
            if(fork() == 0) {
                system("button-handler.sh");
                return 0;
            }
            else printf("Pressed.\n");
            while(wasButtonPushed(dev)) usleep(100000);
        }
        usleep(100000);
    } while(1);
    if(libusb_release_interface(dev, 0) != 0) {
        printf("Cannot unclaim button\n");
    }

    libusb_close(dev);
    return 0;
}
