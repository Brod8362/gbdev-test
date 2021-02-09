#include <stdbool.h>
#include <gb/gb.h>
#include "spritemanager.h"

void om_init(ObjManager *manager, UINT8 starting_id) {
    for (UINT8 i = 0; i < MAX_IDS; i++) {
        manager->ids[i] = starting_id+i;
        manager->available[i] = true;
    }
}

/*
Return the first available ID and mark it as used.
If no free IDs are available, return -1.
*/
UINT8 assign_id(ObjManager *manager) {
    for (UINT8 i = 0; i < MAX_IDS; i++) {
        if (manager->available[i]) {
            manager->available[i]=false;
            return manager->ids[i];
        }
    }
    return -1;
}

/*
Mark a given ID as available
*/
void free_id(ObjManager *manager, UINT8 id) {
    INT8 index = find_id_index(manager,id);
    if (index == -1) { 
        return;
    }
    manager->available[index] = true;
}

/*
Find the index of an ID
*/
INT8 find_id_index(ObjManager *manager, UINT8 id) {
    for (UINT8 i = 0; i < MAX_IDS; i++) {
        if (manager->ids[i] == id) {
            return i;
        }
    }
    return -1;
}