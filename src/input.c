#include "input.h"
#include "collision_mask.h"

void INPUT_joystickHandler(Character* character, bool isPaused) {
    character->isJumping = FALSE;
    u16 value = JOY_readJoypad(JOY_1);

    //if (!isPaused && !character->isMoving) {
        character->speed.x = 0;

        /*if (!character->isGrounded) {
            character->speed.y = FIX32(1); // += FIX32(1);
        } else {
            character->speed.y = 0;
        }*/

        if (value & BUTTON_RIGHT) {
            character->speed.x = FIX32(1);
        } else if (value & BUTTON_LEFT) {
            character->speed.x = FIX32(-1);
        }

        if (value & BUTTON_C) {
            character->position.y = 0;
        }
        if (value & BUTTON_A) {
            character->isJumping = TRUE;
        }
    //}
}
