//
//  Grid.h
//  Geometry Wars
//
//  Created by Vicky D on 1/27/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#ifndef __Geometry_Wars__Grid__
#define __Geometry_Wars__Grid__

#include <stdio.h>
#include "NeonObj.h"

extern const int width;
extern const int height;

typedef struct{
    struct NeonObj n;
} Grid;

Grid *initGrid(int, int, int);
void animateAuxGrid(struct NeonObj *);
int deconstGrid(struct NeonObj *, struct NeonObj *);

#endif /* defined(__Geometry_Wars__Grid__) */
