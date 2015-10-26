//
//  Particle.c
//  Geometry Wars
//
//  Created by Vicky D on 1/8/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Particle.h"

// Converts degrees to radians.
#define toRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define toDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

Particle *initParticle(int x, int y, float xc, float yc, float zc)
{
    Particle *new = malloc(sizeof(Particle));
    
    new->n.pos = malloc(sizeof(Vector2));
    new->n.pos->x = x;
    new->n.pos->y = y;
    
    new->n.color = malloc(sizeof(Vector3));
    new->n.color->x = xc;
    new->n.color->y = yc;
    new->n.color->z = zc;
    
    int size = 1;
    int verticies = 2;
    Vector2 *geom = malloc(sizeof(Vector2) * verticies);
    geom[0] = (Vector2){.x = 0, .y = size};
    geom[1] = (Vector2){.x = 0, .y = -size};
    new->n.shape = geom;

    size = 15;
    new->n.size = size;
    new->n.max_size = size;
    new->n.verts = verticies;
    new->n.type = 1;
    new->n.next = NULL;
    
    new->n.target = malloc(sizeof(Vector2));
    copyVector(new->n.target, new->n.pos);
    
    new->n.rotation = 0;
    new->n.rotation_target = 0;
    
    new->n.vel = malloc(sizeof(Vector2));
    zeroVector(new->n.vel);

    new->n.speed_limit = 30;
    new->n.constant_speed = 0.05;
    new->n.rot_limit = 0;
    new->n.health = 0;
    new->n.alive = 1;
    
    new->n.animatefunc = &animateAuxParticle;
    new->n.deconstfunc = &deconstParticle;
    return new;
}

void animateAuxParticle(struct NeonObj *pointer)
{
    if(magnitudeVector(*pointer->vel) > 0)
        pointer->rotation_target = arctanVector(*pointer->vel);
    if(pointer->rotation > pointer->rotation_target&&abs(pointer->rotation-pointer->rotation_target)>M_PI)
        pointer->rotation_target += M_PI*2;
    else if(pointer->rotation < pointer->rotation_target&&abs(pointer->rotation - pointer->rotation_target)>M_PI)
        pointer->rotation_target -= M_PI*2;
    
    pointer->rotation += (pointer->rotation_target - pointer->rotation)/1;
    
    pointer->size = magnitudeVector(*pointer->vel);
}

int deconstParticle(struct NeonObj *head, struct NeonObj *pointer)
{
    Vector2* check = malloc(sizeof(Vector2));
    subVector(check, *pointer->pos, *pointer->target);
    if(magnitudeVector(*check) < 25) {
        free(check);
        return 1;
    }
    free(check);
    return 0;
}
