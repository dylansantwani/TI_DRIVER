#include "ti84fb.h"

#include <stddef.h>

static bool valid_surface(const ti84fb_t *surface)
{
    return surface != NULL && surface->pixels != NULL &&
           surface->width != 0 && surface->height != 0;
}

static bool in_bounds(const ti84fb_t *surface, int x, int y)
{
    return valid_surface(surface) && x >= 0 && y >= 0 &&
           x < surface->width && y < surface->height;
}

bool ti84fb_put_pixel(const ti84fb_t *surface, int x, int y, uint16_t color)
{
    if (!in_bounds(surface, x, y)) {
        return false;
    }

    surface->pixels[(size_t)y * surface->width + (size_t)x] = color;
    return true;
}

bool ti84fb_get_pixel(const ti84fb_t *surface, int x, int y, uint16_t *color)
{
    if (color == NULL || !in_bounds(surface, x, y)) {
        return false;
    }

    *color = surface->pixels[(size_t)y * surface->width + (size_t)x];
    return true;
}

void ti84fb_fill(const ti84fb_t *surface, uint16_t color)
{
    if (!valid_surface(surface)) {
        return;
    }

    size_t count = (size_t)surface->width * surface->height;
    for (size_t i = 0; i < count; ++i) {
        surface->pixels[i] = color;
    }
}

void ti84fb_fill_rect(const ti84fb_t *surface, int x, int y,
                      int width, int height, uint16_t color)
{
    if (!valid_surface(surface) || width <= 0 || height <= 0) {
        return;
    }

    /* Wider endpoints prevent overflow before clipping, including on hosts. */
    int64_t left = x;
    int64_t top = y;
    int64_t right = (int64_t)x + width;
    int64_t bottom = (int64_t)y + height;

    if (left < 0) left = 0;
    if (top < 0) top = 0;
    if (right > surface->width) right = surface->width;
    if (bottom > surface->height) bottom = surface->height;

    for (int row = (int)top; row < bottom; ++row) {
        size_t offset = (size_t)row * surface->width;
        for (int col = (int)left; col < right; ++col) {
            surface->pixels[offset + (size_t)col] = color;
        }
    }
}
