//
//  Bullet.h
//  Geometry Wars
//
//  Created by Vicky D on 1/2/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#ifndef __Geometry_Wars__Bullet__
#define __Geometry_Wars__Bullet__

#include <stdio.h>
#include "NeonObj.h"

extern const int width;
extern const int height;

typedef struct{
    struct NeonObj n;
} Bullet;

Bullet *initBullet(int, int);
void animateAuxBullet(struct NeonObj *);
int deconstBullet(struct NeonObj *, struct NeonObj *);
#endif /* defined(__Geometry_Wars__Bullet__) */
