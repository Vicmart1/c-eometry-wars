//
//  Gridlineline.c
//  Geometry Wars
//
//  Created by Vicky D on 1/27/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#include "Gridline.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Converts degrees to radians.
#define toRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define toDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

Gridline *initGridline(int x, int y, int length)
{
    Gridline *new = malloc(sizeof(Gridline));
    
    new->n.pos = malloc(sizeof(Vector2));
    new->n.pos->x = x;
    new->n.pos->y = y;
    
    new->n.color = malloc(sizeof(Vector3));
    new->n.color->x = 0.0f;
    new->n.color->y = 0.0f;
    new->n.color->z = 1.0f;
    
    int size = 1;
    int verticies = 2;
    Vector2 *geom = malloc(sizeof(Vector2) * verticies);
    geom[0] = (Vector2){.x = 0, .y = size};
    geom[1] = (Vector2){.x = 0, .y = -size};
    new->n.shape = geom;
    
    size = length;
    new->n.size = size;
    new->n.max_size = size;
    new->n.verts = verticies;
    new->n.type = 4;
    new->n.next = NULL;
    
    new->n.target = malloc(sizeof(Vector2));
    copyVector(new->n.target, new->n.pos);
    new->n.absolute_target = malloc(sizeof(Vector2));
    copyVector(new->n.absolute_target, new->n.pos);
    
    new->n.rotation = 0;
    new->n.rotation_target = 0;
    
    new->n.vel = malloc(sizeof(Vector2));
    zeroVector(new->n.vel);
    
    new->n.speed_limit = 30;
    new->n.constant_speed = 0.05;
    new->n.rot_limit = 0;
    new->n.health = 0;
    new->n.alive = 1;
    
    new->n.animatefunc = &animateAuxGridline;
    new->n.deconstfunc = &deconstGridline;
    return new;
}

void animateAuxGridline(struct NeonObj *pointer)
{

}

int deconstGridline(struct NeonObj *head, struct NeonObj *pointer)
{
    struct NeonObj *index = head;
    Vector2 *check = malloc(sizeof(Vector2));
    
    while(index != NULL) {
        if(index->type == 3) {
            if(index != pointer && index->absolute_target->x == pointer->absolute_target->x && index->absolute_target->y == pointer->absolute_target->y) {
                copyVector(&pointer->shape[0], index->pos);
                subVector(&pointer->shape[0], pointer->shape[0], *pointer->absolute_target);
                xVector(&pointer->shape[0], pointer->shape[0], 1.0/pointer->size);
            }else if((int)pointer->rot_limit == 0 && index->absolute_target->x == pointer->absolute_target->x && index->absolute_target->y == pointer->absolute_target->y + (pointer->size * 2)) {
                copyVector(&pointer->shape[1], index->pos);
                subVector(&pointer->shape[1], pointer->shape[1], *pointer->absolute_target);
                xVector(&pointer->shape[1], pointer->shape[1], 1.0/pointer->size);
            }else if((int)pointer->rot_limit == 1 && index->absolute_target->x == pointer->absolute_target->x + (pointer->size * 2) && index->absolute_target->y == pointer->absolute_target->y) {
                copyVector(&pointer->shape[1], index->pos);
                subVector(&pointer->shape[1], pointer->shape[1], *pointer->absolute_target);
                xVector(&pointer->shape[1], pointer->shape[1], 1.0/pointer->size);
            }
        }
        index = index->next;
    }
    
    free(check);
    return 0;
}
