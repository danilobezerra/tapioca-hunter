#include "camera.h"

s16 cameraPositionX = -1;
s16 cameraPositionY = 0;

void CAM_update(Map* mapA, Map* mapB, s16 x, s16 y) {
    if ((x - 160 != cameraPositionX) || (y - 120 != cameraPositionY)) {
        cameraPositionX = x - 160;
        //cameraPositionY = y - 120;

        if (cameraPositionX < 0) {
            cameraPositionX = 0;
        } else if (cameraPositionX > CAMERA_MAX_X - 320) {
            cameraPositionX = CAMERA_MAX_X - 320;
        }
/*
        if (cameraPositionY < 0) {
            cameraPositionY = 0;
        } else if (cameraPositionY > CAMERA_MAX_Y - 320) {
            cameraPositionY = CAMERA_MAX_Y - 320;
        }
*/
        MAP_scrollTo(mapB, cameraPositionX, cameraPositionY);
        MAP_scrollTo(mapA, cameraPositionX, cameraPositionY);
    }
}

void CAM_setSpritePosition(Sprite* sprite, s16 x, s16 y) {
    if ((x - 160 != cameraPositionX) || (y - 120 != cameraPositionY)) {
        SPR_setPosition(sprite, x - cameraPositionX, y - cameraPositionY);
    }
}
