#include "demo.h"

#include <stdint.h>
#include <stdio.h>

static uint16_t pixels[TI84FB_WIDTH * TI84FB_HEIGHT];

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s output.ppm\n", argv[0]);
        return 2;
    }

    ti84fb_t surface = { pixels, TI84FB_WIDTH, TI84FB_HEIGHT };
    ti84fb_draw_demo(&surface);

    FILE *out = fopen(argv[1], "wb");
    if (out == NULL) {
        perror(argv[1]);
        return 1;
    }

    fprintf(out, "P6\n%d %d\n255\n", TI84FB_WIDTH, TI84FB_HEIGHT);
    for (size_t i = 0; i < TI84FB_WIDTH * TI84FB_HEIGHT; ++i) {
        uint16_t rgb565 = pixels[i];
        unsigned char rgb[3] = {
            (unsigned char)(((rgb565 >> 11) & 31) * 255 / 31),
            (unsigned char)(((rgb565 >> 5) & 63) * 255 / 63),
            (unsigned char)((rgb565 & 31) * 255 / 31)
        };
        if (fwrite(rgb, 1, sizeof rgb, out) != sizeof rgb) {
            perror("writing preview");
            fclose(out);
            return 1;
        }
    }

    if (fclose(out) != 0) {
        perror("closing preview");
        return 1;
    }
    return 0;
}
