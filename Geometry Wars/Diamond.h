//
//  Diamond.h
//  Geometry Wars
//
//  Created by Vicky D on 11/2/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef __Geometry_Wars__Diamond__
#define __Geometry_Wars__Diamond__

#include <stdio.h>
#include "NeonObj.h"

extern const int width;
extern const int height;

typedef struct{
    struct NeonObj n;
} Diamond;

Diamond *initDiamond(int, int);
void animateAuxDiamond(struct NeonObj *);
int deconstDiamond(struct NeonObj *, struct NeonObj *);
#endif /* defined(__Geometry_Wars__Diamond__) */
