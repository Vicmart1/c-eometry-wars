//
//  Player.c
//  Geometry Wars
//
//  Created by Vicky D on 9/13/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Player.h"

Player *initPlayer(int x, int y)
{
    Player *new = malloc(sizeof(Player));
    
    new->n.pos = malloc(sizeof(Vector2));
    new->n.pos->x = x;
    new->n.pos->y = y;
    
    new->n.color = malloc(sizeof(Vector3));
    new->n.color->x = 1.0f;
    new->n.color->y = 1.0f;
    new->n.color->z = 1.0f;
    
    int size = 1;
    int verticies = 8;
    Vector2 *geom = malloc(sizeof(Vector2) * verticies);
    geom[0] = (Vector2){.x = 0, .y = 0};
    geom[1] = (Vector2){.x = -4.0 * size/5, .y = -size/2.0};
    geom[2] = (Vector2){.x = -3.0*size/5, .y = -size};
    geom[3] = (Vector2){.x = -size, .y = -size/4.0};
    geom[4] = (Vector2){.x = 0, .y = 3.0 * size/5};
    geom[5] = (Vector2){.x = size, .y = -size/4.0};
    geom[6] = (Vector2){.x = 3.0 * size/5, .y = -size};
    geom[7] = (Vector2){.x = 4.0 * size/5, .y = -size/2.0};
    new->n.shape = geom;

    size = 25;
    new->n.size = size;
    new->n.max_size = size;
    new->n.verts = verticies;
    new->n.type = 0;
    new->n.next = NULL;
    
    new->n.target = malloc(sizeof(Vector2));
    copyVector(new->n.target, new->n.pos);
    
    new->n.rotation = 0;
    new->n.rotation_target = 0;
    
    new->n.vel = malloc(sizeof(Vector2));
    zeroVector(new->n.vel);
    
    new->n.speed_limit = 20;
    new->n.constant_speed = 0.1;
    new->n.health = 1;
    new->n.alive = 1;
    new->bullet_fire = 0;
    new->bullet_rot = 0;
    new->bullet_rate = 5;
    
    new->n.animatefunc = &animateAuxPlayer;
    new->n.deconstfunc = &deconstPlayer;
    
    return new;
}

void animateAuxPlayer(struct NeonObj *pointer)
{
    if(magnitudeVector(*pointer->vel) > 0.1) {
        pointer->rotation_target = arctanVector(*pointer->vel);
        if(pointer->rotation>pointer->rotation_target&&abs(pointer->rotation-pointer->rotation_target)>M_PI)
            pointer->rotation_target+=M_PI*2;
        else if(pointer->rotation<pointer->rotation_target&&abs(pointer->rotation-pointer->rotation_target)>M_PI)
            pointer->rotation_target-=M_PI*2;
        pointer->rotation += (pointer->rotation_target-pointer->rotation)/4;
    }
}

int deconstPlayer(struct NeonObj *head, struct NeonObj *pointer)
{
    struct NeonObj *index = head->next;
    Vector2 *check = malloc(sizeof(Vector2));
    
    while(index != NULL) {
        if(index->type >= 10 && index->size == index->max_size) {
            if(index->pos->x > pointer->pos->x - pointer->size && index->pos->x < pointer->pos->x + pointer->size && index->pos->y > pointer->pos->y - pointer->size && index->pos->y < pointer->pos->y + pointer->size ) {
                subVector(check, *index->pos, *pointer->pos);
                if(magnitudeVector(*check) < pointer->size * 2) {
                    pointer->health = 0;
                    free(check);
                    return 1;
                }
            }
        }
        index = index->next;
    }
    
    free(check);
    return 0;
}
