#!/bin/bash

if [[ $EUID -ne 0 ]]; then
    echo "$0 is not running as root. Try using sudo."
    exit 2
fi

apt-get install --no-install-recommends nasm gcc binutils gcc-multilib bximage dosfstools libvcflib-tools mtools make gdb coreutils qemu-system-x86
