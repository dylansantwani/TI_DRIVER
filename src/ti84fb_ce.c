#include "ti84fb_ce.h"

#include <sys/lcd.h>

ti84fb_t ti84fb_ce_screen(void)
{
    ti84fb_t surface = {
        (volatile uint16_t *)lcd_Ram,
        TI84FB_WIDTH,
        TI84FB_HEIGHT
    };
    return surface;
}

void ti84fb_ce_set_backlight(uint8_t level)
{
    lcd_BacklightLevel = level;
}
