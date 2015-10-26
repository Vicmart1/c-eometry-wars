//
//  Vector2.h
//  Geometry Wars
//
//  Created by Vicky D on 9/12/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifndef Geometry_Wars_Vector2_h
#define Geometry_Wars_Vector2_h

typedef struct {
    float x;
    float y;
} Vector2;

void addVector(Vector2*, Vector2, Vector2);
void subVector(Vector2*, Vector2, Vector2);
void resetVector(Vector2 *);
void perpendicularVector(Vector2*, Vector2);
float magnitudeVector(Vector2);
void normalizeVector(Vector2*, Vector2);
float dotproductVector(Vector2, Vector2);
void xVector(Vector2*, Vector2, float);
void divVector(Vector2*, Vector2, float);
void negVector(Vector2*, Vector2);
void printVector(Vector2);
int equalsVector(Vector2, Vector2);
void rotVector(Vector2*, Vector2, Vector2, float);
void reflectVector(Vector2*, Vector2, Vector2);
float arctanVector(Vector2);
void inverseVector(Vector2*, Vector2, float);
void zeroVector(Vector2*);
void copyVector(Vector2*, Vector2*);
#endif
