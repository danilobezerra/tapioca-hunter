#ifndef GGJ_2023_PLAYER_H
#define GGJ_2023_PLAYER_H

#include <genesis.h>
#include <maths.h>

#include "collision_data.h"

typedef enum EntityTag {
    ENTITY_TAG_GHOST = 1,
    ENTITY_TAG_ENEMY = 2,
    ENTITY_TAG_PLAYER = 3,
} EntityTag;

typedef struct {
    CollisionData collision;
    bool isJumping;
    bool isDead;
    bool isAttacking;
    s8 direction;
    EntityTag tag;
    Vect2D_f32 position;
    Vect2D_f32 speed;
} Character;

//#define CHAR_MOV_DEBUG

Character CHAR_init();
Box PLAYER_hitbox(Character* character);
Box PLAYER_atk_hitbox(Character* character);
void PLAYER_die(Character* character);
bool CHAR_isGrounded(Character* character);
void CHAR_updateCollisions(Character* character);
void CHAR_movement (Character *character);

#endif //GGJ_2023_PLAYER_H
