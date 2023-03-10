#ifndef GGJ_2023_CAMERA_H
#define GGJ_2023_CAMERA_H

#include <genesis.h>

#define CAMERA_MAX_X 1408
#define CAMERA_MAX_Y 1344

void CAM_update(Map* mapA, Map* mapB, s16 x, s16 y);
void CAM_setSpritePosition(Sprite* sprite, s16 x, s16 y);

#endif //GGJ_2023_CAMERA_H
