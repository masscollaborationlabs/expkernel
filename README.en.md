# Minimal Bootloader + Kernel

This project is a minimal example running on x86 BIOS under the AGPLv3-or-later license:

- `bootloader.S`: GAS (GNU assembler) + Intel syntax 512-byte boot sector
- `kernel_entry.S`: 32-bit entry point
- `kernel.c`: Performs pixel-based colorful drawing with VGA Mode 13h (`0xA0000`, 320x200x256)

Displays `HELLO WORLD` in the center of the screen and colorful GNU/Tux drawings below it.

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

Headless verification (to see output in terminal):

```bash
make run-headless
```

## License

PSD GNU/Linux 

Copyright (C) 2026 Mass Collaboration Labs

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
