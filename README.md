# Minimal Bootloader + Kernel

Bu proje AGPLv3-or-later lisansı altında yayımlanan, x86 BIOS üzerinde çalışan çok basit bir örnektir:

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

Doğrudan QEMU komutu:

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin
```

Headless doğrulama (terminalde çıktı görmek için):

```bash
make run-headless
```

## QEMU Sanal Makine Kurulumu

### QEMU Kurulumu

Ubuntu/Debian üzerinde QEMU'yu yüklemek:

```bash
sudo apt-get update
sudo apt-get install qemu-system-i386 qemu-utils
```

Fedora/RHEL üzerinde:

```bash
sudo dnf install qemu-system-i386
```

macOS üzerinde (Homebrew kullanarak):

```bash
brew install qemu
```

### Sanal Makineyi Çalıştırma

Derledikten sonra `make run` komutu QEMU ile önyükleme görüntüsünü otomatik olarak başlatır:

```bash
make run
```

Alternatif olarak doğrudan:

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin
```

Bu komut GUI penceresiyle QEMU sanal makinesini açar.

### İleri QEMU Seçenekleri

Terminalde çalıştırmak (GUI olmadan):

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin -curses
```

Bellek ve CPU ayarlamak:

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin -m 256 -smp 2
```

GDB debugger ile bağlanmak:

```bash
qemu-system-i386 -drive format=raw,file=os-image.bin -s -S
```

(Başka bir terminalden: `gdb`, sonra `target remote localhost:1234`)

### Sorun Giderme

**QEMU bulunamıyor:**
```bash
which qemu-system-i386
```

**32-bit desteği yok:**
Sistem 32-bit desteği olmadan geliyorsa, `-cpu Nehalem` veya benzer seçenekler ekleyebilirsiniz.

**Görüntü açılmıyor:**
`-display gtk` veya `-display sdl` seçenekleri ile farklı görüntü backendleri deneyin.

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
