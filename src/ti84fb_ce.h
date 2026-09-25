#ifndef TI84FB_CE_H
#define TI84FB_CE_H

#include "ti84fb.h"

/* Call on the calculator, where the LCD is in its normal 16-bit mode. */
ti84fb_t ti84fb_ce_screen(void);

/* 0 is brightest, 255 is darkest. The demo does not change this setting. */
void ti84fb_ce_set_backlight(uint8_t level);

#endif
