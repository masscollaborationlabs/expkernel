# PSD GNU/Linux
#
# Copyright (C) 2026 Mass Collaboration Labs
# Copyright (C) 2026 PSD Authors
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

.intel_syntax noprefix

.section .text
.code16
.global _start

.set KERNEL_LOAD_SEG, 0x1000
.set KERNEL_SECTORS, 8

_start:
    cli
    cld
    xor ax, ax
    mov ss, ax
    mov sp, 0x7C00

    mov ax, 0x07C0
    mov ds, ax
    mov es, ax

    mov byte ptr [boot_drive], dl

    # Enable A20 via port 0x92.
    in al, 0x92
    or al, 0x02
    out 0x92, al

    # Read kernel sectors from disk to 0x10000.
    mov ax, KERNEL_LOAD_SEG
    mov es, ax
    xor bx, bx

    mov ah, 0x02
    mov al, KERNEL_SECTORS
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    mov dl, byte ptr [boot_drive]
    int 0x13
    jc disk_error16

    # Switch to VGA Mode 13h (320x200x256) before protected mode.
    mov ax, 0x0013
    int 0x10

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ljmp 0x08, 0x7C00 + protected_mode

disk_error16:
    mov si, disk_error_msg
1:
    lodsb
    test al, al
    jz 2f
    mov ah, 0x0E
    mov bh, 0x00
    int 0x10
    jmp 1b
2:
    cli
    hlt

.code32
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    ljmp 0x08, 0x10000

boot_drive:
    .byte 0

disk_error_msg:
    .asciz "Disk read error"

.align 8
gdt_start:
    .quad 0x0000000000000000
    .quad 0x00CF9A000000FFFF
    .quad 0x00CF92000000FFFF
gdt_end:

gdt_descriptor:
    .word gdt_end - gdt_start - 1
    .long 0x7C00 + gdt_start

.org 510
.word 0xAA55
