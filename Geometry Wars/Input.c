//
//  Input.c
//  Geometry Wars
//
//  Created by Vicky D on 9/13/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <math.h>
#include <stdlib.h>
#include "Input.h"
#include "Player.h"

int keys[150];
int special_keys[150];

extern const int width;
extern const int height;

extern Player *p1;

void doStuff() {
    
    // Delete Key
    if (keys[127] == 1) {
        exit(0);
    }
    
    // D Key
    if (keys[100] == 1) {
        p1->n.target->x += p1->n.speed_limit;
    }
    
    // A key
    if (keys[97] == 1) {
        p1->n.target->x -= p1->n.speed_limit;
    }
    
    // W key
    if (keys[119] == 1) {
        p1->n.target->y -= p1->n.speed_limit;
    }
    
    // S key
    if (keys[115] == 1) {
        p1->n.target->y += p1->n.speed_limit;
    }
    /** Space key
    if (keys[32] == 1)
        translate_y -= 0.1;
    
     Q key
    if (keys[113] == 1)
        translate_y += 0.1;
    
     E key
    if (keys[101] == 1)
        translate_y -= 0.1;
    **/
    
    if (special_keys[GLUT_KEY_RIGHT] == 1) {
        if(p1->bullet_rot < M_PI)
            p1->bullet_rot += (-p1->bullet_rot)/2;
        else
            p1->bullet_rot += ((M_PI*2)-p1->bullet_rot)/2;
        if(p1->bullet_fire == 0)
            p1->bullet_fire = p1->bullet_rate;
    }
    
    if (special_keys[GLUT_KEY_LEFT] == 1) {
        p1->bullet_rot += (M_PI - p1->bullet_rot)/2;
        if(p1->bullet_fire == 0)
            p1->bullet_fire = p1->bullet_rate;
    }
    
    if (special_keys[GLUT_KEY_UP] == 1) {
        if(p1->bullet_rot < M_PI/2)
            p1->bullet_rot += (-(M_PI/2) - p1->bullet_rot)/2;
        else
            p1->bullet_rot += ((3*M_PI/2) - p1->bullet_rot)/2;
        if(p1->bullet_fire == 0)
            p1->bullet_fire = p1->bullet_rate;
    }

    if (special_keys[GLUT_KEY_DOWN] == 1) {
        if(p1->bullet_rot > 3 * M_PI/2)
            p1->bullet_rot += ((5*M_PI/2) - p1->bullet_rot)/2;
        else
            p1->bullet_rot += (M_PI/2 - p1->bullet_rot)/2;
        if(p1->bullet_fire == 0)
            p1->bullet_fire = p1->bullet_rate;
    }

    
    // Request display update
    glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y)
{
    keys[(int)key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
    keys[(int)key] = 0;
}

void keySpecialDown(int key, int x, int y)
{
    special_keys[key] = 1;
}

void keySpecialUp(int key, int x, int y)
{
    special_keys[key] = 0;
}
