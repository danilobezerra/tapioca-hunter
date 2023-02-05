#ifndef GGJ_2023_TAPIOCAS_H
#define GGJ_2023_TAPIOCAS_H

#include <genesis.h>
#include <maths.h>
#include "player.h"

#define TAPIOCA_TOTAL 5

typedef struct Tapioca {
    Vect2D_s16 pos;
    bool collected;
} Tapioca;

Tapioca tapiocas[TAPIOCA_TOTAL];
Sprite* tapiocas_sprites[TAPIOCA_TOTAL];

void TAPIOCAS_init();
Box TAPIOCAS_hitbox(Tapioca* tapioca);
void TAPIOCAS_update(Character *character);
void TAPIOCAS_catch();
u8 TAPIOCAS_getCount();
void TAPIOCAS_clear();

#endif //GGJ_2023_TAPIOCAS_H
