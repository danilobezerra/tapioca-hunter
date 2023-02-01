#ifndef GGJ_2023_PLAYER_H
#define GGJ_2023_PLAYER_H

#include <genesis.h>

typedef struct {
    f32 x;
    f32 y;
} Vector;

typedef struct {
    bool isMoving;
    bool isGrounded;
    Vector position;
    Vector speed;
} Character;

#endif //GGJ_2023_PLAYER_H
