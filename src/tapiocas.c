#include <genesis.h>
#include <tools.h>
#include "tapiocas.h"
#include "player.h"

u8 tapiocaCount = 5;

void TAPIOCAS_update(Character* player) {

  
}

void TAPIOCAS_catch() {
  tapiocaCount--;
  kprintf("tapiocaCount %u", tapiocaCount);
  if (tapiocaCount == 0) {
    kprintf("WIN GAME!");
  }
}
