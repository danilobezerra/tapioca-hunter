#include <genesis.h>
#include <maths.h>

#include "player.h"
#include "game_math.h"
#include "collision_data.h"
#include "hitboxes.h"
#include "ggj_debug.h"

Character CHAR_init() {
    return (Character) {
        .position = {
            .x = FIX32(160),
            .y = FIX32(10),
        },
        .speed = {
            .x = FIX32(0),
            .y = FIX32(0),
        }
    };
}

Box CHAR_hitbox(Character* character) {
    Box hitbox = {
        .x = (s16)( fix32ToInt(character->position.x) ),
        .y = (s16)( fix32ToInt(character->position.y) ),
        .w = 32,
        .h = 32,
    };
    return hitbox;
}

void CHAR_updateCollisions(Character* character) {
    Box bb = CHAR_hitbox(character);
    character->collision = HB_get_collision_data(bb);
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
*/

bool CHAR_isGrounded(Character* character) {
    return COLMASK_CONTAINS(character->collision, COLMASK_DOWN);
}

void CHAR_movement(Character* character) {
    // gravity
    s32 sy = fix32ToInt(character->speed.y);

    if (character->isJumping && CHAR_isGrounded(character)) {
        sy = -20;
        character->isJumping = FALSE;
    }

    sy = clamp( (sy + 2), (-8), (2) );

    character->speed.y = FIX32(sy);
    
    // character->position.x += FIX32(spd_dir_x);
    // character->position.y += FIX32(spd_dir_y);

    character->position.x += character->speed.x;
    character->position.y += character->speed.y;

    CHAR_updateCollisions(character);
    
    character->position.x -= character->speed.x;
    character->position.y -= character->speed.y;
    
    // character->position.x -= FIX32(spd_dir_x);
    // character->position.y -= FIX32(spd_dir_y);
    
    #if defined(GGJ_DEBUGGING)
        char chmask[5] = "----";
        if (COLMASK_CONTAINS(character->collision, (COLMASK_DOWN)))  { chmask[0] = 'D'; }
        if (COLMASK_CONTAINS(character->collision, (COLMASK_LEFT)))  { chmask[1] = 'L'; }
        if (COLMASK_CONTAINS(character->collision, (COLMASK_RIGHT))) { chmask[2] = 'R'; } 
        if (COLMASK_CONTAINS(character->collision, (COLMASK_UP)))    { chmask[3] = 'U'; }
        GGJ_PRINTF(chmask);
    #endif

    if ((COLMASK_CONTAINS(character->collision, COLMASK_DOWN) && character->speed.y > 0) ||
        (COLMASK_CONTAINS(character->collision, COLMASK_UP) && character->speed.y < 0)
    ){
        character->speed.y = FIX32(0);
    }

    if ((COLMASK_CONTAINS(character->collision, COLMASK_RIGHT) && character->speed.x > 0) ||
        (COLMASK_CONTAINS(character->collision, COLMASK_LEFT) && character->speed.x < 0)
    ){
        character->speed.x = FIX32(0);
    }
        
    character->position.x += character->speed.x;
    character->position.y += character->speed.y;
}
/*
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
