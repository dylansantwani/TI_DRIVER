#include "ti84fb.h"

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static uint16_t storage[TI84FB_WIDTH * TI84FB_HEIGHT + 2];

int main(void)
{
    ti84fb_t surface = { &storage[1], TI84FB_WIDTH, TI84FB_HEIGHT };
    uint16_t color = 0;

    storage[0] = 0x1234;
    storage[TI84FB_WIDTH * TI84FB_HEIGHT + 1] = 0x5678;

    ti84fb_fill(&surface, TI84FB_BLUE);
    assert(storage[1] == TI84FB_BLUE);
    assert(storage[TI84FB_WIDTH * TI84FB_HEIGHT] == TI84FB_BLUE);
    assert(ti84fb_put_pixel(&surface, 0, 0, TI84FB_RED));
    assert(ti84fb_put_pixel(&surface, 319, 239, TI84FB_GREEN));
    assert(ti84fb_get_pixel(&surface, 0, 0, &color) && color == TI84FB_RED);
    assert(ti84fb_get_pixel(&surface, 319, 239, &color) && color == TI84FB_GREEN);
    assert(!ti84fb_put_pixel(&surface, -1, 0, TI84FB_WHITE));
    assert(!ti84fb_put_pixel(&surface, 320, 0, TI84FB_WHITE));
    assert(!ti84fb_put_pixel(&surface, 0, 240, TI84FB_WHITE));
    assert(!ti84fb_get_pixel(&surface, 0, 0, NULL));

    ti84fb_fill_rect(&surface, -5, -5, 10, 10, TI84FB_WHITE);
    assert(storage[1] == TI84FB_WHITE);
    assert(storage[1 + 4 * TI84FB_WIDTH + 4] == TI84FB_WHITE);
    assert(storage[1 + 5 * TI84FB_WIDTH + 5] == TI84FB_BLUE);
    ti84fb_fill_rect(&surface, 318, 238, 10, 10, TI84FB_RED);
    assert(storage[TI84FB_WIDTH * TI84FB_HEIGHT] == TI84FB_RED);
    ti84fb_fill_rect(&surface, INT_MAX, INT_MAX, INT_MAX, INT_MAX, TI84FB_WHITE);
    ti84fb_fill_rect(&surface, 0, 0, 0, 10, TI84FB_RED);
    assert(storage[0] == 0x1234);
    assert(storage[TI84FB_WIDTH * TI84FB_HEIGHT + 1] == 0x5678);

    puts("ti84fb host tests passed");
    return 0;
}
