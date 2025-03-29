#include <ti/screen.h>
#include <ti/getkey.h>
#include <stdint.h>
#include "stdio.h"
#include <sys/timers.h>

#define lcd_Ram ((void *)0xD40004)
#define LCD_WIDTH (320)
#define LCD_HEIGHT (240)
#define LCD_SIZE (LCD_WIDTH * LCD_HEIGHT * 2)
#define lcd_BacklightLevel (*(volatile uint8_t *)0xF60024)
#define BRIGHTNESS_MIN 229
#define BRIGHTNESS_MAX 49

#define COLOR_RED 0xF800
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE 0x001F
#define COLOR_WHITE 0xFFFF
#define COLOR_BLACK 0x0000
#define COLOR_YELLOW 0xFFE0
#define COLOR_CYAN 0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_GRAY 0x8410
#define COLOR_ORANGE 0xFC00
#define COLOR_PINK 0xF81F
#define COLOR_PURPLE 0x780F
#define COLOR_BROWN 0xA145

typedef uint16_t color_t;

void lcd_set_pixel(uint32_t x, uint32_t y, color_t color)
{
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT)
    {
        return;
    }

    uint32_t pixel_offset = (y * LCD_WIDTH + x) * sizeof(color_t);
    *((volatile color_t *)(lcd_Ram + pixel_offset)) = color; // idek what this was I just found it in the graphx asm and converted it and no one knows what it does
}

void lcd_color_screen(color_t color)
{
    for (uint32_t y = 0; y < LCD_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < LCD_WIDTH; x++)
        {
            lcd_set_pixel(x, y, color);
        }
    }
}
void lcd_set_backlight(uint8_t light)
{
    lcd_BacklightLevel = light;
}
uint32_t getPixelColor(int x, int y, int width)
{
    uint32_t *pixelAddr = (uint32_t *)(lcd_Ram + (y * width + x) * sizeof(uint32_t));

    uint32_t color = *pixelAddr;

    return color;
}
char snum[5];

int main()
{
    color_t color = 0xF800;   // Red
    uint32_t x = 50, y = 100; // Starting position
    os_ClrLCDFull();
    // Draw D
    for (uint32_t i = 0; i < 10; i++)
    {
        for (uint32_t j = 0; j < 14; j++)
        {
            if (i == 0 || i == 9 || j == 0 || (i == 9 && j > 0 && j < 13) || (i < 9 && j == 13))
            {
                lcd_set_pixel(x + i, y + j, color);
            }
        }
    }

    x += 15; // Space between characters

    // Draw G
    for (uint32_t i = 0; i < 10; i++)
    {
        for (uint32_t j = 0; j < 14; j++)
        {
            if (i == 0 || i == 9 || j == 0 || (i == 0 && j < 13) || (j == 13 && i < 6) || (i == 5 && j > 4 && j < 13))
            {
                lcd_set_pixel(x + i, y + j, color);
            }
        }
    }

    x += 15; // Space between characters

    // Draw X
    for (uint32_t i = 0; i < 10; i++)
    {
        for (uint32_t j = 0; j < 14; j++)
        {
            if (i == j || i + j == 9)
            {
                lcd_set_pixel(x + i, y + j, color);
            }
        }
    }
    // end screen fade
    delay(1500);
    lcd_color_screen(COLOR_MAGENTA);
}
