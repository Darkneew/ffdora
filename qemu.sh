#!/bin/sh
set -e
. ./iso.sh

/mnt/c/'Program Files'/qemu/qemu-system-$(./target-triplet-to-arch.sh $HOST).exe -cdrom ffdora.iso
