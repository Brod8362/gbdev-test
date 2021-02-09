#include <gb/gb.h>
#include <stdio.h>

#include "graphics/bird.c"

#include "tilemap/graphics.c"
#include "tilemap/bg_tilemap.c"

void main() {

    int pos_x = 50;
    int pos_y = 70;
    int frame = 0;

    const int BIRD_ID = 0;

    set_bkg_data(0, 18, BackgroundTileset);
    set_bkg_tiles(0, 0, BackgroundTilemapWidth, BackgroundTilemapHeight, BackgroundTilemap);

    SHOW_BKG;

    //sprite handler stuff

    SPRITES_8x8;
    set_sprite_data(BIRD_ID,0,BirdGraphics);
    set_sprite_tile(BIRD_ID,0);
    move_sprite(BIRD_ID, pos_x, pos_y);

    SHOW_SPRITES;

    DISPLAY_ON;

    while (1) {
        if (joypad() & J_UP) {
            pos_y+=1;
            move_sprite(BIRD_ID, pos_x, pos_y);
        }
        frame++;
        scroll_bkg(1, 0);
        wait_vbl_done();
    }
}