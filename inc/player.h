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

bool CHAR_checkCollision(Character* character, s16 x, s16 y);
void CHAR_move(Character *character);

#endif //GGJ_2023_PLAYER_H
