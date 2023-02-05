#include <genesis.h>
#include <maths.h>

#include "player.h"
#include "game_math.h"
#include "collision_data.h"
#include "hitboxes.h"
#include "ggj_debug.h"

Character CHAR_init() {
    return (Character) {
        .isJumping = FALSE,
        .isDead = FALSE,
        .position = {
            .x = FIX32(160),
            .y = FIX32(10),
        },
        .speed = {
            .x = FIX32(0),
            .y = FIX32(0),
        },
        .tag = ENTITY_TAG_PLAYER
    };
}

Box PLAYER_hitbox(Character* character) {
    return (Box) {
        .x = (s16) (fix32ToInt(character->position.x) + 9),
        .y = (s16) (fix32ToInt(character->position.y) + 3),
        .w = 10,
        .h = 27,
    };
}

void CHAR_updateCollisions(Character* character) {
    Box bb = PLAYER_hitbox(character);
    character->collision = HB_get_collision_data(bb);
}

bool CHAR_isGrounded(Character* character) {
    return COLMASK_CONTAINS(character->collision, COLMASK_DOWN);
}

void PLAYER_die(Character* character) {
    character->isDead = TRUE;
}

void CHAR_movement(Character* character) {
    // gravity
    if (character->tag == ENTITY_TAG_PLAYER) {
        s32 sy = fix32ToInt(character->speed.y);

        if (character->isJumping && CHAR_isGrounded(character)) {
            sy = -10;
            character->isJumping = FALSE;
        }

        sy = clamp((sy + 1), (-10), (6));

        character->speed.y = FIX32(sy);
    }

    // collision system:

    // begin by translating the character
    character->position.x += character->speed.x;
    character->position.y += character->speed.y;

    // then, calculate the collisions against hitboxes
    CHAR_updateCollisions(character);

    // undo the translation
    character->position.x -= character->speed.x;
    character->position.y -= character->speed.y;

    // some debugging
    #if defined(CHAR_MOV_DEBUG)
        char chmask[5] = "----";
        if (COLMASK_CONTAINS(character->collision, (COLMASK_DOWN)))  { chmask[0] = 'D'; }
        if (COLMASK_CONTAINS(character->collision, (COLMASK_LEFT)))  { chmask[1] = 'L'; }
        if (COLMASK_CONTAINS(character->collision, (COLMASK_RIGHT))) { chmask[2] = 'R'; } 
        if (COLMASK_CONTAINS(character->collision, (COLMASK_UP)))    { chmask[3] = 'U'; }
        GGJ_PRINTF(chmask);
    #endif

    // check if the horizontal speed of the character is trying to go against the collision
    if ((COLMASK_CONTAINS(character->collision, COLMASK_DOWN) && character->speed.y > 0) ||
        (COLMASK_CONTAINS(character->collision, COLMASK_UP) && character->speed.y < 0)
    ) {
        character->speed.y = FIX32(0);
    }

    // check if the vertical speed of the character is trying to go against the collision
    if ((COLMASK_CONTAINS(character->collision, COLMASK_RIGHT) && character->speed.x > 0) ||
        (COLMASK_CONTAINS(character->collision, COLMASK_LEFT) && character->speed.x < 0)
    ) {
        character->speed.x = FIX32(0);
    }

    // now, the speed values are corrected by the collision system, thus it's safe to translate
    character->position.x += character->speed.x;
    character->position.y += character->speed.y;
}
/*
bool CHAR_checkCollision(Character* character, s16 x, s16 y) {
    character->isGrounded = FALSE;

    s16 tileY = y >> 3;
    s16 tileX = x >> 3;

    u8 characterWidth = 4;
    u8 characterHeight = 4;

    s16 leftTile = tileX;
    s16 rightTile = tileX + characterWidth;
    s16 topTile = tileY;
    s16 bottomTile = tileY + characterHeight;

    for (s16 i = leftTile; i <= rightTile; i++) {
        for (s16 j = topTile; j <= bottomTile; j++) {
            if (level[j][i] == 0) {
                if (j == bottomTile) {
                    character->isGrounded = TRUE;
                }

                return FALSE;
            }
        }
    }
    return TRUE;
}

void CHAR_move(Character *character) {
    s16 positionX = fix32ToInt(character->position.x);
    s16 positionY = fix32ToInt(character->position.y);

    s16 tempPositionX;
    s16 tempPositionY;

    s16 speedX = fix32ToInt(character->speed.x);
    s16 speedY = fix32ToInt(character->speed.y);

    if (CHAR_checkCollision(character, positionX + speedX, positionY + speedY)) {
        positionX += speedX;
        positionY += speedY;
    } else {
        if (speedX) {
            tempPositionX = positionX;

            if (speedX > 0) {
                for (u8 i = 1; i < speedX; i++) {
                    tempPositionX++;

                    if (CHAR_checkCollision(character, tempPositionX, positionY)) {
                        positionX = tempPositionX;
                    } else {
                        break;
                    }
                }
            } else {
                for (u8 i = speedX; i > 0; i++) {
                    tempPositionX--;

                    if (CHAR_checkCollision(character, tempPositionX, positionY)) {
                        positionX = tempPositionX;
                    } else {
                        break;
                    }
                }
            }
        }

        if (speedY) {
            tempPositionY = positionY;

            if (speedY > 0) {
                for (u8 i = 1; i < speedY; i++) {
                    tempPositionY++;

                    if (CHAR_checkCollision(character, positionX, tempPositionY)) {
                        positionY = tempPositionY;
                    } else {
                        break;
                    }
                }
            } else {
                for (u8 i = speedY; i > 0; i++) {
                    tempPositionY--;

                    if (CHAR_checkCollision(character, positionX, tempPositionY)) {
                        positionY = tempPositionY;
                    }
                }
            }
        }

        character->position.x = FIX32(positionX);
        character->position.y = FIX32(positionY);
    }

    character->position.x = FIX32(positionX);
    character->position.y = FIX32(positionY);
}
*/