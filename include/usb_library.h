
#ifndef XFILMEE_USB_LIBRARY_H
#define XFILMEE_USB_LIBRARY_H

#include <stddef.h>

#define XFILMEE_MAX_USB_MOVIES 128

typedef struct {
    char filename[256];
    char title[256];
    char path[512];
    char cover_path[512];
} UsbMovie;

int xfilmee_usb_scan(
    const char *directory,
    UsbMovie *output,
    size_t capacity
);

#endif
