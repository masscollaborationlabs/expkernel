# Minimal Bootloader + Kernel

This project is a minimal example running on x86 BIOS under the AGPLv3-or-later license:

- `bootloader.S`: GAS (GNU assembler) + Intel syntax 512-byte boot sector
- `kernel_entry.S`: 32-bit entry point
- `kernel.c`: Performs pixel-based colorful drawing with VGA Mode 13h (`0xA0000`, 320x200x256)

At the top of the screen, it displays `PSD X` inside a circle, with `PSD Authors` and `AGPLv3-or-later` shown below it.

## Requirements

- GNU assembler (`as`, binutils)
- `gcc` (32-bit compilation support)
- `ld`, `objcopy` (binutils)
- `qemu-system-i386` (to run)

## Building

```bash
make
```

This command produces `os-image.bin`.

## Running

```bash
make run
```

Direct QEMU command:

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin
```

Headless verification (to see output in terminal):

```bash
make run-headless
```

## QEMU Virtual Machine Setup

### Installing QEMU

On Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install qemu-system-i386 qemu-utils
```

On Fedora/RHEL:

```bash
sudo dnf install qemu-system-i386
```

On macOS (using Homebrew):

```bash
brew install qemu
```

### Running the Virtual Machine

After building, the `make run` command automatically launches the boot image in QEMU:

```bash
make run
```

Alternatively, run directly:

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin
```

This command opens the QEMU virtual machine with a GUI window.

### Advanced QEMU Options

Run in terminal (without GUI):

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin -curses
```

Adjust memory and CPU:

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin -m 256 -smp 2
```

Attach GDB debugger:

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin -s -S
```

(From another terminal: `gdb`, then `target remote localhost:1234`)

### Troubleshooting

**QEMU not found:**
```bash
which qemu-system-i386
```

**No 32-bit support:**
If your system lacks 32-bit support, try adding `-cpu Nehalem` or similar options.

**Display not opening:**
Try different display backends with `-display gtk` or `-display sdl`.

## License

PSD GNU/Linux 

Copyright (C) 2026 Mass Collaboration Labs

Copyright (C) 2026 PSD Authors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
