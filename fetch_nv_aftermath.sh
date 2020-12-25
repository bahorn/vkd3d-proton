#!/bin/bash

# NVIDIA NSight Aftermath SDK is a proprietary package and sadly can not be
# directly included.
# This script downloads the latest releases of the SDK from NVIDIAs site.

VERSION=2020_2_1
BASE_URL=https://developer.nvidia.com/rdp/assets/nsight-aftermath-sdk-$VERSION

WINDOWS=$BASE_URL-windows-package
LINUX=$BASE_URL-linux-package


# Windows is packaged as a ZIP

# Linux is provided as a gziped tar

mkdir -p external/store external/windows external/linux

echo "FETCHING AFTERMATH"
wget -O external/store/aftermath-windows.zip $WINDOWS
wget -O external/store/aftermath-linux.tar.gz $LINUX

echo "EXTRACTING AFTERMATH"
unzip external/store/aftermath-windows.zip -d external/windows
tar -xzvf external/store/aftermath-linux.tar.gz -C external/linux
