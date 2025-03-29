#include <ti/screen.h>
#include <ti/getkey.h>
#include <stdint.h>
#include "stdio.h"
#include <sys/timers.h>




#define lcd_Ram                  ((void*)0xD40000)
#define LCD_WIDTH               (320)
#define LCD_HEIGHT              (240)
#define LCD_SIZE                (LCD_WIDTH*LCD_HEIGHT*2)
#define lcd_BacklightLevel (*(volatile uint8_t*)0xF60024)
#define BRIGHTNESS_MIN 229
#define BRIGHTNESS_MAX 49




typedef uint16_t color_t;

void lcd_set_pixel(uint32_t x, uint32_t y, color_t color) {
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) {
        return;  
    }

    uint32_t pixel_offset = (y * LCD_WIDTH + x) * sizeof(color_t);
    *((volatile color_t*)(lcd_Ram + pixel_offset)) = color; //idek what this was I just found it in the graphx asm and converted it and no one knows what it does 
}


void lcd_color_screen(color_t color) {
    for (uint32_t y = 0; y < LCD_HEIGHT; y++) {
        for (uint32_t x = 0; x < LCD_WIDTH; x++) {
            lcd_set_pixel(x, y, color);
        }
    }
}
void lcd_set_backlight(uint8_t light){
    lcd_BacklightLevel = light;

}
uint32_t getPixelColor(int x, int y, int width) {
    uint32_t *pixelAddr = (uint32_t *)(FRAMEBUFFER_BASE_ADDR + (y * width + x) * sizeof(uint32_t));

    uint32_t color = *pixelAddr;

    return color;   
}s
char snum[5];  

