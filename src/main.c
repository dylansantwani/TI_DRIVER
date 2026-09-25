#include <ti/getkey.h>
#include <ti/screen.h>

#include "demo.h"
#include "ti84fb_ce.h"

int main(void)
{
    ti84fb_t screen = ti84fb_ce_screen();

    ti84fb_draw_demo(&screen);
    os_GetKey();
    os_ClrLCDFull();
    return 0;
}
