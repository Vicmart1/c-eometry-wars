//
//  NeonObj.c
//  Geometry Wars
//
//  Created by Vicky D on 10/31/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "NeonObj.h"

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })

void animate(struct NeonObj *pointer)
{
    if(pointer->size == pointer->max_size || pointer->type == 1) {
        subVector(pointer->vel, *pointer->target, *pointer->pos);
        if(pointer->constant_speed == 0) {
            normalizeVector(pointer->vel, *pointer->vel);
            xVector(pointer->vel, *pointer->vel, pointer->speed_limit);
        } else {
            xVector(pointer->vel, *pointer->vel, pointer->constant_speed);
        }
        addVector(pointer->pos, *pointer->pos, *pointer->vel);
        if(pointer->alive != 1)
            pointer->alive = 1;
    }
    pointer->time_var+=5;
    if(pointer->time_var>=360)
        pointer->time_var = 0;
    
    if(pointer->size != -1 && pointer->size != pointer->max_size) {
        pointer->size += 0.5;
    }
    pointer->animatefunc(pointer);
}
