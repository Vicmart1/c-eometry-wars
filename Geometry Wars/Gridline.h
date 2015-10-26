//
//  Gridline.h
//  Geometry Wars
//
//  Created by Vicky D on 1/27/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#ifndef __Geometry_Wars__Gridline__
#define __Geometry_Wars__Gridline__

#include <stdio.h>
#include "NeonObj.h"

extern const int width;
extern const int height;

typedef struct{
    struct NeonObj n;
} Gridline;

Gridline *initGridline(int, int, int);
void animateAuxGridline(struct NeonObj *);
int deconstGridline(struct NeonObj *, struct NeonObj *);

#endif /* defined(__Geometry_Wars__Gridline__) */
