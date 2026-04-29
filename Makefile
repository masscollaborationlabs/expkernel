# PSD GNU/Linux
#
# Copyright (C) 2026 Mass Collaboration Labs
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

AS=as
CC=gcc
LD=ld
OBJCOPY=objcopy

CFLAGS=-m32 -ffreestanding -fno-pic -fno-stack-protector -nostdlib -nostartfiles -nodefaultlibs -Wall -Wextra
LDFLAGS=-m elf_i386 -T linker.ld

all: os-image.bin

bootloader.o: bootloader.S
	$(AS) --32 bootloader.S -o bootloader.o

bootloader.bin: bootloader.o
	$(LD) -m elf_i386 -Ttext 0x0 -e _start bootloader.o -o bootloader.elf
	$(OBJCOPY) -O binary bootloader.elf bootloader.bin
	@test $$(stat -c%s bootloader.bin) -eq 512

kernel_entry.o: kernel_entry.S
	$(AS) --32 kernel_entry.S -o kernel_entry.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

kernel.bin: kernel_entry.o kernel.o linker.ld
	$(LD) $(LDFLAGS) kernel_entry.o kernel.o -o kernel.elf
	objcopy -O binary kernel.elf kernel.bin

os-image.bin: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os-image.bin
	@size=$$(stat -c%s os-image.bin); if [ $$size -lt 4608 ]; then truncate -s 4608 os-image.bin; fi

run: os-image.bin
	qemu-system-i386 -drive format=raw,file=os-image.bin

run-headless: os-image.bin
	qemu-system-i386 -drive format=raw,file=os-image.bin -display none -serial none -debugcon stdio -global isa-debugcon.iobase=0xe9

clean:
	rm -f *.bin *.o *.elf

.PHONY: all run run-headless clean
