#include "player.h"
#include "game_math.h"
#include "collision_mask.h"
#include "hitboxes.h"
#include "maths.h"

Box CHAR_hitbox(Character* character) {
    Box hitbox = {
        .x = (s16)( fix32ToInt(character->position.x) ),
        .y = (s16)( fix32ToInt(character->position.y) ),
        .w = 16,
        .h = 16,
    };
    return hitbox;
}

void CHAR_updateCollisions(Character* character) {
    Box bb = CHAR_hitbox(character);
    character->collisionMask = HB_get_collision_mask(bb);
}

bool CHAR_checkCollision(Character* character, s16 x, s16 y) {
/*
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
*/
    return TRUE;
}

void CHAR_movement(Character* character) {
    character->position.x += character->speed.x;
    character->position.y += character->speed.y;

    CHAR_updateCollisions(character);

    if (COLMASK_CONTAINS(character->collisionMask, COLMASK_DOWN)) {
        character->speed.y = 0;
    }
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
