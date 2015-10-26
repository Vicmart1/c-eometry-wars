//
//  NeonObj.h
//  Geometry Wars
//
//  Created by Vicky D on 9/13/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef Geometry_Wars_NeonObj_h
#define Geometry_Wars_NeonObj_h
#include "Vector3.h"
#include "Vector2.h"

struct NeonObj{
    Vector2 *pos;
    Vector2 *shape;
    Vector3 *color;
    double size;
    int max_size;
    int verts;
    int time_var;
    int health;
    int alive;
    float speed_limit;
    float constant_speed;
    float rot_limit;
    struct NeonObj *next;
    char type;
    Vector2 *absolute_target;
    Vector2 *target;
    Vector2 *vel;
    float rotation;
    float rotation_target;
    void (*animatefunc)(struct NeonObj *);
    int (*deconstfunc)(struct NeonObj *, struct NeonObj *);
};

void animate(struct NeonObj *);

#endif

//****TYPES****//
//00 - Player
//01 - Particle
//02 - Bullet
//03 - Grid Point
//04 - Line
//10 - Diamond
//11 - Pinwheel
