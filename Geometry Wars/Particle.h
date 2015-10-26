//
//  Particle.h
//  Geometry Wars
//
//  Created by Vicky D on 1/8/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#ifndef __Geometry_Wars__Particle__
#define __Geometry_Wars__Particle__

#include <stdio.h>
#include "NeonObj.h"

extern const int width;
extern const int height;

typedef struct{
    struct NeonObj n;
} Particle;

Particle *initParticle(int, int, float, float, float);
void animateAuxParticle(struct NeonObj *);
int deconstParticle(struct NeonObj *, struct NeonObj *);
#endif /* defined(__Geometry_Wars__Particle__) */
