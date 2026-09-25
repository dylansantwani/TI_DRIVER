#ifndef TI84FB_H
#define TI84FB_H

#include <stdbool.h>
#include <stdint.h>

#define TI84FB_WIDTH 320
#define TI84FB_HEIGHT 240

/* RGB565 colors used by the TI-84 Plus CE's 16-bit framebuffer mode. */
#define TI84FB_BLACK 0x0000u
#define TI84FB_WHITE 0xFFFFu
#define TI84FB_RED   0xF800u
#define TI84FB_GREEN 0x07E0u
#define TI84FB_BLUE  0x001Fu

typedef struct {
    volatile uint16_t *pixels;
    uint16_t width;
    uint16_t height;
} ti84fb_t;

/* All drawing functions silently ignore a null or empty surface. */
bool ti84fb_put_pixel(const ti84fb_t *surface, int x, int y, uint16_t color);
bool ti84fb_get_pixel(const ti84fb_t *surface, int x, int y, uint16_t *color);
void ti84fb_fill(const ti84fb_t *surface, uint16_t color);
void ti84fb_fill_rect(const ti84fb_t *surface, int x, int y,
                      int width, int height, uint16_t color);

#endif
