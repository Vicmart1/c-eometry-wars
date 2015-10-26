//
//  Pinwheel.h
//  Geometry Wars
//
//  Created by Vicky D on 1/2/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#ifndef __Geometry_Wars__Pinwheel__
#define __Geometry_Wars__Pinwheel__

#include <stdio.h>
#include "NeonObj.h"

extern const int width;
extern const int height;

typedef struct{
    struct NeonObj n;
} Pinwheel;

Pinwheel *initPinwheel(int x, int y);
void animateAuxPinwheel(struct NeonObj *);
int deconstPinwheel(struct NeonObj *, struct NeonObj *);
#endif /* defined(__Geometry_Wars__Pinwheel__) */
