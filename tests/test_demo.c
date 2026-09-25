#include "demo.h"

#include <assert.h>
#include <stdio.h>

static uint16_t pixels[TI84FB_WIDTH * TI84FB_HEIGHT];

static uint16_t at(int x, int y)
{
    return pixels[y * TI84FB_WIDTH + x];
}

int main(void)
{
    ti84fb_t surface = { pixels, TI84FB_WIDTH, TI84FB_HEIGHT };
    ti84fb_draw_demo(&surface);

    assert(at(0, 0) == TI84FB_BLACK);
    assert(at(8, 8) == TI84FB_WHITE);
    assert(at(108, 39) == TI84FB_RED);
    assert(at(153, 39) == TI84FB_GREEN);
    assert(at(188, 39) == TI84FB_BLUE);
    assert(at(50, 150) == TI84FB_RED);
    assert(at(150, 150) == TI84FB_GREEN);
    assert(at(250, 150) == TI84FB_BLUE);
    assert(at(40, 94) == TI84FB_WHITE);
    assert(at(40, 210) == TI84FB_WHITE);

    puts("demo pixel tests passed");
    return 0;
}
