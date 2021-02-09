#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "graphics/bird.c"

#include "tilemap/graphics.c"
#include "tilemap/bg_tilemap.c"

int frame = 0;

//todo load this from the data instead of doing it manually
UWORD bkgPalette[] = {
    29344, 32767, 31288, 5344
};

UWORD birdPalette[] = {
    6075, 276, 32767, 1
};

void main() {

    short pos_x = 50;
    short pos_y = 70;

    const short BIRD_ID = 0;

    set_bkg_data(0, 18, BackgroundTileset);
    set_bkg_tiles(0, 0, BackgroundTilemapWidth, BackgroundTilemapHeight, BackgroundTilemap);
    set_bkg_palette(0,1, bkgPalette);

    SHOW_BKG;

    //sprite handler stuff

    SPRITES_8x8;
    set_sprite_data(BIRD_ID,0,BirdGraphics);
    set_sprite_tile(BIRD_ID,0);
    set_sprite_palette(BIRD_ID, 1, birdPalette);
    move_sprite(BIRD_ID, pos_x, pos_y);

    SHOW_SPRITES;

    DISPLAY_ON;

    while (1) {
        switch (joypad()) {
            case J_LEFT:
                pos_x--;
                break;
            case J_RIGHT:
                pos_x++;
                break;
            case J_DOWN:
                pos_y++;
                break;
            case J_UP:
                pos_y--;
                break;
            case J_A:
                break;
            case J_B:
                break;
        }

        move_sprite(BIRD_ID, pos_x, pos_y);
        scroll_bkg(frame%2, 0);
        wait_vbl_done();
        frame++;
    }
}