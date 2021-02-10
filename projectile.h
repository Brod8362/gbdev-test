#include <gb/gb.h>

typedef struct {
    INT16 sprite_id;
    INT16 pos_x;
    INT16 pos_y;
    INT16 vel_x;
    INT16 vel_y;
    BOOLEAN active; //if active is set to false, the projectile will stop moving.
} Projectile;