#include <gb/gb.h>
#include <stdio.h>
#include "graphics/bird.h"

void main() {

    int pos_x = 50;
    int pos_y = 70;

    const int BIRD_ID = 0;

    SPRITES_8x8;


    set_sprite_data(BIRD_ID,0,BirdGraphics);
    set_sprite_tile(BIRD_ID,0);
    move_sprite(BIRD_ID, pos_x, pos_y);


    SHOW_SPRITES;

    while (1) {
        if (joypad() & J_UP) {
            pos_y+=1;
        }

        move_sprite(0, pos_x, pos_y);
    }
}