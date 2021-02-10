#include <gb/gb.h>
#include "projectile.h"

#define MAX_PROJECTILES 15

typedef struct {
    Projectile* prjs[MAX_PROJECTILES];
} ProjectileManager;

INT8 next_available_index(ProjectileManager* prjman);

INT8 add_projectile(ProjectileManager* prjman, UINT8 sprite_id, INT8 start_x, INT8 start_y, INT8 vel_x, INT8 vel_y);

void remove_projectile(ProjectileManager* prjman, UINT8 sprite_id);

void tick(ProjectileManager* prjman);

void pm_init(ProjectileManager* prjman);