#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphics/sprites.c"
#include "tilemap/graphics.c"
#include "tilemap/bg_tilemap.c"

#include "spritemanager.c"
#include "projectilemanager.c"
#include "display.h"

#define SPRITE_ID_BIRD 0
#define SPRITE_ID_BALL 1
#define SPRITE_ID_HEART 2
#define SPRITE_ID_NUM0 3

int frame = 0;

//todo load this from the data instead of doing it manually
UWORD bkgPalette[] = {
    29344, 32767, 31288, 5344
};

UWORD birdPalette[] = {
    6075, 276, 32767, 1
};

void update_score(UINT8 ids[], UINT8 len, int score) {
    for (INT8 i = len-1; i >= 0; i--) {
        int digit = score%10;
        score/=10;
        set_sprite_tile(ids[i], SPRITE_ID_NUM0+digit);
    }
}

void main() {

    short pos_x = 50;
    short pos_y = 70;
    short score = 0;

    ObjManager objmanager;
    ProjectileManager prjmanager;

    const UINT8 bird_sprite_id = 0;
    const UINT8 health_sprites[] = {1,2,3};
    const UINT8 score_sprites[] = {4,5,6};

    om_init(&objmanager, 7);

    set_bkg_data(0, 18, BackgroundTileset);
    set_bkg_tiles(0, 0, BackgroundTilemapWidth, BackgroundTilemapHeight, BackgroundTilemap);
    set_bkg_palette(0,1, bkgPalette);

    SHOW_BKG;

    //sprite handler stuff

    SPRITES_8x8;
    set_sprite_data(0,13,Sprites);

    set_sprite_tile(bird_sprite_id,0);
    set_sprite_palette(0, 1, birdPalette);
    move_sprite(bird_sprite_id, pos_x, pos_y);

    //create health sprites and put them on screen
    for (int i = 0; i < 3; i++) {
        int id = health_sprites[i];
        set_sprite_tile(id, 2);
        move_sprite(id, (i+1)*9, 16);
    }
    //create score sprites
    for (int i = 0; i < 3; i++) {
        int id = score_sprites[i];
        set_sprite_tile(id, SPRITE_ID_NUM0);
        move_sprite(id, (i+1)*9+(45), 16);
    }

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

        if (pos_x < SCREEN_X_MIN+8) {
            pos_x = SCREEN_X_MIN+8;
        } else if (pos_x > SCREEN_X_MAX) {
            pos_x = SCREEN_X_MAX;
        }
        if (pos_y < SCREEN_Y_MIN+24) {
            pos_y = SCREEN_Y_MIN+24;
        } else if (pos_y > SCREEN_Y_MAX+8) {
            pos_y = SCREEN_Y_MAX+8;
        }

        move_sprite(bird_sprite_id, pos_x, pos_y);
        scroll_bkg(frame%2, 0);

        // if (frame%1000==0) {
        //     UINT8 id = assign_id(&objmanager);
        //     set_sprite_tile(id, 2);
        //     move_sprite(id, 150, pos_y);
        //     add_projectile(&prjmanager, id, 150, pos_y, 0, -1);
        // }

        tick(&prjmanager);
        update_score(score_sprites, 3, frame);
        wait_vbl_done();
        frame++;
    }
}