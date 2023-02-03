#include "input.h"

void INPUT_joystickHandler(Character* character, bool isPaused) {
    u16 value = JOY_readJoypad(JOY_1);

    //if (!isPaused && !character->isMoving) {
        character->speed.x = 0;

        if (!character->isGrounded) {
            character->speed.y += FIX32(1);
        } else {
            character->speed.y = 0;
        }

        if (value & BUTTON_RIGHT) {
            character->speed.x = FIX32(5);
        } else if (value & BUTTON_LEFT) {
            character->speed.x = FIX32(-5);
        }

        if (value & BUTTON_A) {
            if (character->isGrounded) {
                character->speed.y = FIX32(-10);
            }
        }
    //}
}
