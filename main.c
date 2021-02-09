#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "graphics/sprites.c"

#include "tilemap/graphics.c"
#include "tilemap/bg_tilemap.c"

#include "spritemanager.c"

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

    ObjManager objmanager;

    const short bird_sprite_id = 0;
    const short health_sprites[] = {1,2,3};

    set_bkg_data(0, 18, BackgroundTileset);
    set_bkg_tiles(0, 0, BackgroundTilemapWidth, BackgroundTilemapHeight, BackgroundTilemap);
    set_bkg_palette(0,1, bkgPalette);

    SHOW_BKG;

    //sprite handler stuff

    SPRITES_8x8;
    set_sprite_data(0,0,SpritesTLE0);
    set_sprite_data(1,0,SpritesTLE2);
    set_sprite_data(2,0,SpritesTLE1);

    set_sprite_tile(bird_sprite_id,0);
    set_sprite_palette(0, 1, birdPalette);
    move_sprite(bird_sprite_id, pos_x, pos_y);

    //create health sprites and put them on screen
    for (int i = 0; i < 3; i++) {
        int id = health_sprites[i];
        set_sprite_tile(id, 1);
        move_sprite(id, (i+1)*9, 16);
    }

    SHOW_SPRITES;

    om_init(&objmanager, 4);


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

        move_sprite(bird_sprite_id, pos_x, pos_y);
        scroll_bkg(frame%2, 0);

        if (frame%100==0) {
            UINT8 id = assign_id(&objmanager);
            set_sprite_tile(id, 2);
            move_sprite(id, 150, pos_y);
        }

        wait_vbl_done();
        frame++;
    }
}