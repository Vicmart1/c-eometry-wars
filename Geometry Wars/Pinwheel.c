//
//  Pinwheel.c
//  Geometry Wars
//
//  Created by Vicky D on 1/2/15.
//  Copyright (c) 2015 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Pinwheel.h"

// Converts degrees to radians.
#define toRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define toDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

Pinwheel *initPinwheel(int x, int y)
{
    Pinwheel *new = malloc(sizeof(Pinwheel));
    
    new->n.pos = malloc(sizeof(Vector2));
    new->n.pos->x = x;
    new->n.pos->y = y;
    
    new->n.color = malloc(sizeof(Vector3));
    new->n.color->x = 0.8f;
    new->n.color->y = 0.0f;
    new->n.color->z = 0.8f;
    
    int size = 1;
    int verticies = 12;
    Vector2 *geom = malloc(sizeof(Vector2) * verticies);
    geom[0] = (Vector2){.x = 0, .y = 0};
    geom[1] = (Vector2){.x = 0, .y = size};
    geom[2] = (Vector2){.x = -size, .y = size};
    geom[3] = (Vector2){.x = 0, .y = 0};
    geom[4] = (Vector2){.x = size, .y = 0};
    geom[5] = (Vector2){.x = size, .y = size};
    geom[6] = (Vector2){.x = 0, .y = 0};
    geom[7] = (Vector2){.x = 0, .y = -size};
    geom[8] = (Vector2){.x = size, .y = -size};
    geom[9] = (Vector2){.x = 0, .y = 0};
    geom[10] = (Vector2){.x = -size, .y = 0};
    geom[11] = (Vector2){.x = -size, .y = -size};
    new->n.shape = geom;
    
    size = 25;
    new->n.size = 0;
    new->n.max_size = size;
    new->n.verts = verticies;
    new->n.type = 11;
    new->n.next = NULL;
    
    new->n.target = malloc(sizeof(Vector2));
    copyVector(new->n.target, new->n.pos);
    
    new->n.rotation = 0.05;
    new->n.rotation_target = 0;
    
    new->n.vel = malloc(sizeof(Vector2));
    zeroVector(new->n.vel);
    
    new->n.speed_limit = 2;
    new->n.constant_speed = 0;
    new->n.health = 2;
    new->n.alive = 1;
    
    new->n.animatefunc = &animateAuxPinwheel;
    new->n.deconstfunc = &deconstPinwheel;

    return new;
}

void animateAuxPinwheel(struct NeonObj *pointer)
{
    for(int i=0;i< pointer->verts;i++){
        rotVector(&pointer->shape[i], pointer->shape[i], (Vector2){.x = 0, .y = 0}, -pointer->rotation);
    }
    
    Vector2* check = malloc(sizeof(Vector2));
    subVector(check, *pointer->target, *pointer->pos);
    if(abs(magnitudeVector(*check)) < 10) {
        pointer->target->x = rand()%width;
        pointer->target->y = rand()%height;
    }
    free(check);
}

int deconstPinwheel(struct NeonObj *head, struct NeonObj *pointer)
{
    struct NeonObj *index = head;
    Vector2 *check = malloc(sizeof(Vector2));
    
    while(index != NULL) {
        if(index->type == 2) {
            if(index->pos->x > pointer->pos->x - pointer->size && index->pos->x < pointer->pos->x + pointer->size && index->pos->y > pointer->pos->y - pointer->size && index->pos->y < pointer->pos->y + pointer->size ) {
                subVector(check, *index->pos, *pointer->pos);
                
                if(magnitudeVector(*check) < pointer->size * 2) {
                    pointer->health += index->health;
                    index->health = 0;

                    if(pointer->health < 0) {
                        pointer->health = 0;
                        free(check);
                        return 1;
                    }
                }
            }
        }
        index = index->next;
    }
    
    free(check);
    return 0;   
}
