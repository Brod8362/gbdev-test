#include <gb/gb.h>
#include "projectilemanager.h"
#include "display.h"

INT8 add_projectile(ProjectileManager* prjman, UINT8 sprite_id, INT8 start_x, INT8 start_y, INT8 vel_x, INT8 vel_y) {
    INT8 next_id = next_available_index(prjman);
    if (next_id != -1) {
        Projectile p;
        p.sprite_id=sprite_id;
        p.pos_x=start_x;
        p.pos_y=start_y;
        p.vel_x=vel_x;
        p.vel_y=vel_y;
        p.active=true;
        prjman->prjs[next_id] = &p;
    }
    return next_id;
}

void tick(ProjectileManager* prjman) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        Projectile* p = prjman->prjs[i];
        if (p != NULL && p->active) {
            p->pos_x+=p->vel_x;
            p->pos_y+=p->vel_y;
            if (p->pos_x < SCREEN_X_MIN || p->pos_y < SCREEN_Y_MIN || p->pos_x > SCREEN_X_MAX || p->pos_y > SCREEN_Y_MAX) {
                set_sprite_tile(p->sprite_id, 99);
                remove_projectile(prjman, p->sprite_id);
            } else {
                move_sprite(p->sprite_id, p->pos_x, p->pos_y);
            }
            
        }
    }
}

INT8 next_available_index(ProjectileManager* prjman) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (prjman->prjs[i] == NULL) {
            return i;
        }
    }
    return -1;
}

void pm_init(ProjectileManager* prjman) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        prjman->prjs[i] = NULL;
    }
}

INT8 find_id(ProjectileManager* prjman, UINT8 search) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (prjman->prjs[i] != NULL && prjman->prjs[i]->sprite_id==search) {
            return i;
        }
    }
    return -1;
}

void remove_projectile(ProjectileManager* prjman, UINT8 sprite_id) {
    INT8 index = find_id(prjman, sprite_id);
    if (index != -1) {
        prjman->prjs[index] = NULL;
    }
}