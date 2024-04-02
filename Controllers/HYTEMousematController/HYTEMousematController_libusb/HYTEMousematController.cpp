/*---------------------------------------------------------*\
|  HYTEMousematController.cpp                               |
|                                                           |
|  Driver for HYTE CNVS RGB mousemat controller             |
|                                                           |
|  Adam Honse (calcprogrammer1@gmail.com), 7/18/2023        |
\*---------------------------------------------------------*/

#include "HYTEMousematController.h"

#include <cstring>
#include <iomanip>
#include <sstream>

HYTEMousematController::HYTEMousematController(libusb_device_handle* dev_handle)
{
    dev = dev_handle;

    /*-----------------------------------------------------*\
    | Fill in location string with USB ID                   |
    \*-----------------------------------------------------*/
    libusb_device_descriptor descriptor;
    libusb_get_device_descriptor(libusb_get_device(dev_handle), &descriptor);

    std::stringstream location_stream;
    location_stream << std::hex << std::setfill('0') << std::setw(4) << descriptor.idVendor << ":" << std::hex << std::setfill('0') << std::setw(4) << descriptor.idProduct;
    location = location_stream.str();
}

HYTEMousematController::~HYTEMousematController()
{

}

std::string HYTEMousematController::GetLocation()
{
    return(location);
}

void HYTEMousematController::FirmwareAnimationControl(bool enabled)
{
    unsigned char serial_buf[4];

    /*-----------------------------------------------------*\
    | Zero out buffer                                       |
    \*-----------------------------------------------------*/
    memset(serial_buf, 0, sizeof(serial_buf));

    /*-----------------------------------------------------*\
    | Set up Firmware Animation Control packet              |
    \*-----------------------------------------------------*/
    serial_buf[0]   = 0xFF;
    serial_buf[1]   = 0xDC;
    serial_buf[2]   = 0x05;
    serial_buf[3]   = enabled;

    /*-----------------------------------------------------*\
    | Send packet                                           |
    \*-----------------------------------------------------*/
    libusb_bulk_transfer(dev, HYTE_CNVS_EP_OUT, serial_buf, sizeof(serial_buf), NULL, 1000);
}

void HYTEMousematController::StreamingCommand(RGBColor* colors)
{
    unsigned char serial_buf[157];
    unsigned int max_brightness = 72;

    /*-----------------------------------------------------*\
    | Zero out buffer                                       |
    \*-----------------------------------------------------*/
    memset(serial_buf, 0, sizeof(serial_buf));

    /*-----------------------------------------------------*\
    | Set up Streaming packet                               |
    \*-----------------------------------------------------*/
    serial_buf[0]   = 0xFF;
    serial_buf[1]   = 0xEE;
    serial_buf[2]   = 0x02;
    serial_buf[3]   = 0x01;
    serial_buf[4]   = 0x00;
    serial_buf[5]   = 0x32;
    serial_buf[6]   = 0x00;

    /*-----------------------------------------------------*\
    | Copy in colors                                        |
    \*-----------------------------------------------------*/
    for(unsigned int color_idx = 0; color_idx < 50; color_idx++)
    {
        serial_buf[7 + (color_idx * 3)] = ( max_brightness * RGBGetGValue(colors[color_idx]) ) / 100;
        serial_buf[8 + (color_idx * 3)] = ( max_brightness * RGBGetRValue(colors[color_idx]) ) / 100;
        serial_buf[9 + (color_idx * 3)] = ( max_brightness * RGBGetBValue(colors[color_idx]) ) / 100;
    }

    /*-----------------------------------------------------*\
    | Send packet                                           |
    \*-----------------------------------------------------*/
    libusb_bulk_transfer(dev, HYTE_CNVS_EP_OUT, serial_buf, sizeof(serial_buf), NULL, 1000);
}
