//
//  Grid.c
//  Geometry Wars
//
//  Created by Vicky D on 1/27/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Grid.h"

// Converts degrees to radians.
#define toRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define toDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

Grid *initGrid(int x, int y, int length)
{
    Grid *new = malloc(sizeof(Grid));
    
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
    
    new->n.size = length;
    new->n.max_size = length;
    new->n.verts = verticies;
    new->n.type = 3;
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
    
    new->n.animatefunc = &animateAuxGrid;
    new->n.deconstfunc = &deconstGrid;
    return new;
}

void animateAuxGrid(struct NeonObj *pointer)
{
    subVector(pointer->target, *pointer->absolute_target, *pointer->target);
    xVector(pointer->target, *pointer->target, pointer->constant_speed * 10);
    addVector(pointer->target, *pointer->absolute_target, *pointer->target);
}

int deconstGrid(struct NeonObj *head, struct NeonObj *pointer)
{
    struct NeonObj *index = head;
    Vector2 *check = malloc(sizeof(Vector2));
    Vector2 *temp = malloc(sizeof(Vector2));

    while(index != NULL) {
        if(index->type != 1 && index->type != 3 && index->type != 4) {
            if(index->pos->x > pointer->pos->x - pointer->size && index->pos->x < pointer->pos->x + pointer->size && index->pos->y > pointer->pos->y - pointer->size && index->pos->y < pointer->pos->y + pointer->size && magnitudeVector(*index->vel) > 1.0 && pointer->alive == 1) {

                xVector(temp, *index->vel, 3);
                addVector(pointer->target, *pointer->pos, *temp);
            }
        }
        index = index->next;
    }
    
    free(check);
    free(temp);
    return 0;
}
