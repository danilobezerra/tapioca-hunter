#include <genesis.h>
#include <resources.h>

bool isRunning = TRUE;

int main() {
    VDP_drawText("Hello World!", 10, 13);

    while (isRunning) {

        SYS_doVBlankProcess();
    }

    return 0;
}