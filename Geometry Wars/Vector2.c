//
//  vector2.c
//  Geometry Wars
//
//  Created by Vicky D on 9/11/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "Vector2.h"

#define toRadians(t) (t * M_PI / 180)
#define toDegrees(t) (t * 180 / M_PI)

void addVector(Vector2* on, Vector2 first, Vector2 second)
{
    on->x = first.x + second.x;
    on->y = first.y + second.y;
}

void subVector(Vector2* on, Vector2 first, Vector2 second)
{
    on->x = first.x - second.x;
    on->y = first.y - second.y;
}

void resetVector(Vector2 *first)
{
    first->x = 0;
    first->y = 0;
}

void perpendicularVector(Vector2* on, Vector2 first)
{
    on->x = -first.y;
    on->y = first.x;
}

float magnitudeVector(Vector2 first)
{
    return sqrt((first.x * first.x) + (first.y * first.y));
}

void normalizeVector(Vector2* on, Vector2 first)
{
    float mag = magnitudeVector(first);
    if(mag != 0 && mag != NAN) {
        on->x = first.x / mag;
        on->y = first.y / mag;
    } else {
        on->x = first.x;
        on->y = first.y;
    }
}

float dotproductVector(Vector2 first, Vector2 second)
{
    return (first.x * second.x) + (first.y * second.y);
}

void xVector(Vector2* on, Vector2 first, float factor)
{
    on->x = first.x * factor;
    on->y = first.y * factor;
}

void divVector(Vector2* on, Vector2 first, float divisor)
{
    on->x = first.x / divisor;
    on->y = first.y / divisor;
}

void negVector(Vector2* on, Vector2 first)
{
    on->x = -first.x;
    on->y = -first.y;
}

void printVector(Vector2 first)
{
    printf("< %f , %f >\n", first.x, first.y);
}

int equalsVector(Vector2 first, Vector2 second)
{
    if(first.x == second.x && first.y == second.y)
        return 1;
    return 0;
}

void rotVector(Vector2* on, Vector2 first, Vector2 cent, float theta)
{
    theta *= -1;
    on->x = cent.x + ((first.x-cent.x) * cos(theta) - (first.y-cent.y) * sin(theta));
    on->y = cent.y + ((first.x-cent.x) * sin(theta) + (first.y-cent.y) * cos(theta));
}

void reflectVector(Vector2* on, Vector2 first, Vector2 line)
{
    float factor = dotproductVector(first, line)/dotproductVector(line, line);
    xVector(on, line, factor * 2);
    subVector(on, *on, first);
}

float arctanVector(Vector2 first)
{
    float theta;
    if(first.x >= 0)
        theta = -atan(first.y/first.x) - (M_PI/2);
    else
        theta = -atan(first.y/first.x) + (M_PI/2);
    return theta;
}

void inverseVector(Vector2* on, Vector2 first, float numerator)
{
    on->x = numerator/first.x;
    on->y = numerator/first.y;
}

void zeroVector(Vector2* on)
{
    on->x = 0;
    on->y = 0;
}

void copyVector(Vector2* to, Vector2* from)
{
    to->x = from->x;
    to->y = from->y;
}
