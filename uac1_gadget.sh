#!/bin/bash
cd /sys/kernel/config/usb_gadget/
mkdir -p audio
cd audio

echo 0x0104 > idProduct # Multifunction Composite Gadget
echo 0x1d6b > idVendor # Linux Foundation
echo 0x0100 > bcdDevice # v1.0.0
echo 0x0200 > bcdUSB # USB2

mkdir strings/0x409
echo "000000000" > strings/0x409/serialnumber
echo "Linux Foundation" > strings/0x409/manufacturer
echo "Linux USB Audio Gadget" > strings/0x409/product

mkdir -p configs/c.1/strings/0x409
echo "Audio Gadget" > configs/c.1/strings/0x409/configuration
echo 250 > configs/c.1/MaxPower

N="uac1.usb0"
mkdir -p functions/$N
echo 3 > functions/$N/c_chmask
echo 44100 > functions/$N/c_srate
echo 2 > functions/$N/c_ssize
echo 3 > functions/$N/p_chmask
echo 44100 > functions/$N/p_srate
echo 2 > functions/$N/p_ssize
echo 2 > functions/$N/req_number

ln -s functions/$N configs/c.1

ls /sys/class/udc > UDC
