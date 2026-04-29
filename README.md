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
