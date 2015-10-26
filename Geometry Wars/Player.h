//
//  Player.h
//  Geometry Wars
//
//  Created by Vicky D on 9/13/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef Geometry_Wars_Player_h
#define Geometry_Wars_Player_h
#include "NeonObj.h"

typedef struct{
    struct NeonObj n;
    int bullet_fire;
    int bullet_rate;
    float bullet_rot;
} Player;

Player *initPlayer(int, int);
void animateAuxPlayer(struct NeonObj *);
int deconstPlayer(struct NeonObj *, struct NeonObj *);
#endif
