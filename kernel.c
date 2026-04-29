typedef unsigned char u8;

static volatile u8* const FB = (u8*)0xA0000;
static const int WIDTH = 320;
static const int HEIGHT = 200;

static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static int str_len(const char* s) {
    int n = 0;
    while (s[n] != '\0') {
        ++n;
    }
    return n;
}

static void put_pixel(int x, int y, u8 color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return;
    }
    FB[y * WIDTH + x] = color;
}

static void fill_screen(u8 color) {
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        FB[i] = color;
    }
}

static void fill_rect(int x, int y, int w, int h, u8 color) {
    for (int yy = 0; yy < h; ++yy) {
        for (int xx = 0; xx < w; ++xx) {
            put_pixel(x + xx, y + yy, color);
        }
    }
}

static void fill_circle(int cx, int cy, int r, u8 color) {
    const int r2 = r * r;
    for (int y = -r; y <= r; ++y) {
        for (int x = -r; x <= r; ++x) {
            if (x * x + y * y <= r2) {
                put_pixel(cx + x, cy + y, color);
            }
        }
    }
}

static void fill_ellipse(int cx, int cy, int rx, int ry, u8 color) {
    const int rx2 = rx * rx;
    const int ry2 = ry * ry;
    const int rhs = rx2 * ry2;
    for (int y = -ry; y <= ry; ++y) {
        for (int x = -rx; x <= rx; ++x) {
            if ((x * x) * ry2 + (y * y) * rx2 <= rhs) {
                put_pixel(cx + x, cy + y, color);
            }
        }
    }
}

static const u8 GLYPH_SPACE[7] = {0, 0, 0, 0, 0, 0, 0};
static const u8 GLYPH_D[7] = {0x1E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1E};
static const u8 GLYPH_E[7] = {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F};
static const u8 GLYPH_G[7] = {0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0E};
static const u8 GLYPH_H[7] = {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11};
static const u8 GLYPH_L[7] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F};
static const u8 GLYPH_N[7] = {0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x11};
static const u8 GLYPH_O[7] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E};
static const u8 GLYPH_R[7] = {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11};
static const u8 GLYPH_T[7] = {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04};
static const u8 GLYPH_U[7] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E};
static const u8 GLYPH_W[7] = {0x11, 0x11, 0x11, 0x15, 0x15, 0x1B, 0x11};
static const u8 GLYPH_X[7] = {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11};

static const u8* glyph_for(char c) {
    switch (c) {
        case 'D': return GLYPH_D;
        case 'E': return GLYPH_E;
        case 'G': return GLYPH_G;
        case 'H': return GLYPH_H;
        case 'L': return GLYPH_L;
        case 'N': return GLYPH_N;
        case 'O': return GLYPH_O;
        case 'R': return GLYPH_R;
        case 'T': return GLYPH_T;
        case 'U': return GLYPH_U;
        case 'W': return GLYPH_W;
        case 'X': return GLYPH_X;
        default:  return GLYPH_SPACE;
    }
}

static void draw_char(int x, int y, char c, int scale, u8 color) {
    const u8* glyph = glyph_for(c);
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (glyph[row] & (1u << (4 - col))) {
                fill_rect(x + col * scale, y + row * scale, scale, scale, color);
            }
        }
    }
}

static void draw_text_center(int y, const char* text, int scale, u8 color) {
    const int len = str_len(text);
    const int char_w = 5 * scale;
    const int spacing = scale;
    const int total_w = len > 0 ? (len * (char_w + spacing) - spacing) : 0;
    int x = (WIDTH - total_w) / 2;
    for (int i = 0; i < len; ++i) {
        draw_char(x, y, text[i], scale, color);
        x += char_w + spacing;
    }
}

static void draw_gnu_logo(int cx, int cy) {
    fill_circle(cx, cy, 28, 55);      
    fill_circle(cx, cy + 2, 19, 62);  
    fill_circle(cx - 20, cy - 20, 10, 45);
    fill_circle(cx + 20, cy - 20, 10, 45);
    fill_circle(cx - 20, cy - 20, 5, 14);
    fill_circle(cx + 20, cy - 20, 5, 14);
    fill_circle(cx - 8, cy - 5, 3, 15);
    fill_circle(cx + 8, cy - 5, 3, 15);
    fill_rect(cx - 14, cy + 10, 28, 4, 50);
    fill_circle(cx - 14, cy + 12, 2, 50);
    fill_circle(cx + 14, cy + 12, 2, 50);
    draw_text_center(cy + 38, "GNU", 2, 14);
}

static void draw_tux_logo(int cx, int cy) {
    fill_ellipse(cx, cy, 24, 32, 0);
    fill_ellipse(cx, cy + 2, 15, 22, 63);
    fill_circle(cx - 8, cy - 10, 3, 15);
    fill_circle(cx + 8, cy - 10, 3, 15);
    fill_circle(cx - 8, cy - 10, 1, 0);
    fill_circle(cx + 8, cy - 10, 1, 0);
    fill_ellipse(cx, cy - 2, 6, 4, 44);
    fill_ellipse(cx - 10, cy + 28, 10, 5, 44);
    fill_ellipse(cx + 10, cy + 28, 10, 5, 44);
    draw_text_center(cy + 38, "TUX", 2, 14);
}

void kernel_main(void) {
    const char* msg = "HELLO WORLD";

    fill_screen(1);

    for (int y = 0; y < HEIGHT; ++y) {
        put_pixel((y * 3) % WIDTH, y, 9);
        put_pixel((WIDTH - 1) - ((y * 2) % WIDTH), y, 17);
    }

    draw_text_center(32, msg, 3, 15);
    draw_gnu_logo(110, 122);
    draw_tux_logo(210, 122);

    for (int i = 0; msg[i] != '\0'; ++i) {
        if (msg[i] == ' ') {
            outb(0xE9, ' ');
        } else {
            outb(0xE9, (unsigned char)msg[i]);
        }
    }
    outb(0xE9, '\n');

    for (;;) {
        __asm__ volatile ("hlt");
    }
}
