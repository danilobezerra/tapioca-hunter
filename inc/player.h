#ifndef GGJ_2023_PLAYER_H
#define GGJ_2023_PLAYER_H

#include <genesis.h>
#include <maths.h>

#include "collision_mask.h"

typedef struct {
    bool isMoving;
    CollisionMask collisionMask;
    bool isGrounded; // TODO: remove
    bool isJumping;
    Vect2D_f32 position;
    Vect2D_f32 speed;
} Character;

bool CHAR_isGrounded(Character* character);
void CHAR_updateCollisions(Character* character);
bool CHAR_checkCollision(Character* character, s16 x, s16 y);
void CHAR_move(Character *character);
void CHAR_movement(Character *character);

#endif //GGJ_2023_PLAYER_H
