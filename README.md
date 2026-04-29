# Minimal Bootloader + Kernel

Bu proje, x86 BIOS üzerinde çalışan çok basit bir örnektir:

- `bootloader.S`: GAS (GNU assembler) + Intel syntax ile 512-byte boot sector
- `kernel_entry.S`: 32-bit giriş noktası
- `kernel.c`: VGA Mode 13h (`0xA0000`, 320x200x256) ile piksel tabanlı renkli çizim yapar

Ekranda ortada `HELLO WORLD` ve altında renkli GNU/Tux çizimleri gösterir.

## Gereksinimler

- GNU assembler (`as`, binutils)
- `gcc` (32-bit derleme desteği)
- `ld`, `objcopy` (binutils)
- `qemu-system-i386` (çalıştırmak için)

## Derleme

```bash
make
```

Bu komut `os-image.bin` üretir.

## Çalıştırma

```bash
make run
```

Headless doğrulama (terminalde çıktı görmek için):

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
