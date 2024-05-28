/*
 * Author: Tomo (@indiegdevstdio)
 * Given the tile position (X,Y), checks if there's any obstacles (collisions or actors) at that position
 * License: MIT Licence
 */
#pragma bank 255

#include <gbdk/platform.h>
#include "vm.h"
#include "collision.h"
#include "actor.h"

void WalkabilityChecker(SCRIPT_CTX * THIS) OLDCALL BANKED {
    // Variable index is passed (in ARG0) for result storage, so now we can assign the results back to this variable
    int16_t* results = VM_REF_TO_PTR(*(int16_t *)VM_REF_TO_PTR(FN_ARG0));

    // Passed in values from editor
    int16_t x = *(int16_t*)VM_REF_TO_PTR(FN_ARG2);
    int16_t y = *(int16_t*)VM_REF_TO_PTR(FN_ARG1);

    // Get the collision ID at the specified tile position
    UBYTE collisionID = tile_at(x, y);
    if(collisionID != 0) {
        // Can't walk through because map has collision
        *results = 0;
        return;
    }

    // Map collision check passed, so now we will check if any actor's are there
    actor_t* actor = actor_at_tile(x, y, 1);
    // Ignore pinned actors
    if(!actor->pinned && actor != NULL) {
        // Can't walk through because there's an actor
        *results = 0;
        return;
    }

    // Can walk through
    *results = 1;
}
