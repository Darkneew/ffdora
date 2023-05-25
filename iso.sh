#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/ffdora.kernel isodir/boot/ffdora.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "ffdora" {
	multiboot /boot/ffdora.kernel
}
EOF
grub-mkrescue -o ffdora.iso isodir