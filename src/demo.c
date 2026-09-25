#include "demo.h"

/* DGX is the original demo's label, redrawn as legible 5x7 bitmap glyphs. */
static const uint8_t glyphs[3][7] = {
    { 0x1e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1e }, /* D */
    { 0x0f, 0x10, 0x10, 0x17, 0x11, 0x11, 0x0e }, /* G */
    { 0x11, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x11 }  /* X */
};

static void draw_glyph(const ti84fb_t *surface, int glyph, int x, int y,
                       uint16_t color)
{
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (glyphs[glyph][row] & (1u << (4 - col))) {
                ti84fb_fill_rect(surface, x + col * 5, y + row * 5, 5, 5, color);
            }
        }
    }
}

void ti84fb_draw_demo(const ti84fb_t *surface)
{
    ti84fb_fill(surface, TI84FB_BLACK);
    ti84fb_fill_rect(surface, 8, 8, 304, 224, TI84FB_WHITE);
    ti84fb_fill_rect(surface, 10, 10, 300, 220, TI84FB_BLACK);

    draw_glyph(surface, 0, 108, 39, TI84FB_RED);
    draw_glyph(surface, 1, 148, 39, TI84FB_GREEN);
    draw_glyph(surface, 2, 188, 39, TI84FB_BLUE);

    ti84fb_fill_rect(surface, 36, 105, 82, 95, TI84FB_RED);
    ti84fb_fill_rect(surface, 119, 105, 82, 95, TI84FB_GREEN);
    ti84fb_fill_rect(surface, 202, 105, 82, 95, TI84FB_BLUE);

    /* Thin rules are drawn one pixel at a time to exercise that API. */
    for (int x = 36; x < 284; ++x) {
        ti84fb_put_pixel(surface, x, 94, TI84FB_WHITE);
        ti84fb_put_pixel(surface, x, 210, TI84FB_WHITE);
    }
}
