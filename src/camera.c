#include "camera.h"

s16 cameraPositionX = -1;
s16 cameraPositionY = -1;

void CAM_setPosition(Map* map, Sprite* sprite, s16 x, s16 y) {
    if ((x - 160 != cameraPositionX) || (y - 120 != cameraPositionY)) {
        cameraPositionX = x - 160;
        cameraPositionY = y - 120;

        if (cameraPositionX < 0) {
            cameraPositionX = 0;
        } else if (cameraPositionX > CAMERA_MAX_X - 320) {
            cameraPositionX = CAMERA_MAX_X - 320;
        }

        if (cameraPositionY < 0) {
            cameraPositionY = 0;
        } else if (cameraPositionY > CAMERA_MAX_Y - 320) {
            cameraPositionY = CAMERA_MAX_Y - 320;
        }

        SPR_setPosition(sprite, x - cameraPositionX, y - cameraPositionY);
        MAP_scrollTo(map, cameraPositionX, cameraPositionY);
    }
}