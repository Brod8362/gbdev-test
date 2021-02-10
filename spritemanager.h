#include <stdbool.h>

#define MAX_IDS 16

typedef struct {
    UINT8 ids[MAX_IDS];
    BOOLEAN available[MAX_IDS];
} ObjManager;


void om_init(ObjManager *manager, UINT8 starting_id);

/*
Return the first available ID and mark it as used.
If no free IDs are available, return -1.
*/
UINT8 assign_id(ObjManager *manager);

/*
Mark a given ID as available
*/
void free_id(ObjManager *manager, UINT8 id);

void free_all(ObjManager *manager);

/*
Find the index of an ID
*/
INT8 find_id_index(ObjManager *manager, UINT8 id);

