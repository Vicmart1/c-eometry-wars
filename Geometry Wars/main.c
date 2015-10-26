//
//  main.c
//  Geometry Wars
//
//  Created by Vicky D on 9/11/14.
//  Copyright (c) 2014 Vicmart. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Player.h"
#include "Input.h"
#include "NeonObj.h"
#include "Diamond.h"
#include "Pinwheel.h"
#include "Bullet.h"
#include "Particle.h"
#include "Grid.h"
#include "Gridline.h"

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

const int frames_per_second = 240;
const int width = 1280;
const int height = 800;
const int detail = 0;
const float distance = 0.4;

struct NeonObj *head;
struct NeonObj *curr;
Player *p1;

float timer = 0.0f;

void display();
void mainThread();
void drawLine(Vector2 *, Vector2 *, Vector3 *);
void createPlayer(int, int);
void createDiamond(int, int);
void createPinwheel(int, int);
void createBullet(int);
void createGrid(int, int, int);

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //glOrtho (0, width, height, 0, 0, 1);
    gluOrtho2D(0.0, width, height, 0.0);
    glMatrixMode (GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    struct NeonObj *pointer = head;
    Vector2* firstLine = malloc(sizeof(Vector2));
    Vector2* secondLine = malloc(sizeof(Vector2));
    Vector2* zeroLine = malloc(sizeof(Vector2));
    Vector2* zero = malloc(sizeof(Vector2));
    Vector2* camera = malloc(sizeof(Vector2));
    camera->x = width/2;
    camera->y = height/2;
    subVector(camera, *p1->n.pos, *camera);
    zeroVector(zero);
    
    while(pointer != NULL) {
        if(pointer->type != 3) {
            for(int i = 0; i < pointer->verts; i++) {
                if(pointer->pos->x > (camera->x) - pointer->size && pointer->pos->x < (camera->x + width) + pointer->size && pointer->pos->y > (camera->y) - pointer->size && pointer->pos->y < (camera->y + height) + pointer->size) {
                    rotVector(firstLine, pointer->shape[i], *zero, pointer->rotation);
                    xVector(firstLine, *firstLine, pointer->size);
                    subVector(firstLine, *firstLine, *camera);
                    if(i < pointer->verts - 1) {
                        rotVector(secondLine, pointer->shape[i+1], *zero, pointer->rotation);
                        xVector(secondLine, *secondLine, pointer->size);
                        subVector(secondLine, *secondLine, *camera);
                    }
                    rotVector(zeroLine, pointer->shape[0], *zero, pointer->rotation);
                    xVector(zeroLine, *zeroLine, pointer->size);
                    subVector(zeroLine, *zeroLine, *camera);
                
                    if(i < pointer->verts - 1) {
                        addVector(firstLine, *firstLine, *pointer->pos);
                        addVector(secondLine, *secondLine, *pointer->pos);
                        drawLine(firstLine, secondLine, pointer->color);
                    } else {
                        addVector(firstLine, *firstLine, *pointer->pos);
                        addVector(zeroLine, *zeroLine, *pointer->pos);
                        drawLine(firstLine, zeroLine, pointer->color);
                    }
                }
            }
        }
        pointer = pointer->next;
    }
    
    free(camera);
    free(firstLine);
    free(secondLine);
    free(zeroLine);
    free(zero);
    
    glFlush();
    
    if(p1->n.alive == 1)
        doStuff();
    else
        glutPostRedisplay();
}

int main(int argc, const char * argv[])
{
    time_t t;
    srand((unsigned) time(&t));
    
    srand((int)time(NULL));

    createGrid(1500, 1500, 80);
    
    Player *first = initPlayer(0, 0);
    curr->next = &first->n;
    curr = &first->n;
    p1 = first;
    
    for(int i = 0; i < 10; i++) {
        createDiamond(600, 400);
    }
    
    for(int i = 0; i < 10; i++) {
        createPinwheel(600, 400);
    }
    

    glutInit(&argc, (char **)argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Geometry Wars");
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(keySpecialDown);
    glutSpecialUpFunc(keySpecialUp);
    glutDisplayFunc(mainThread);

    glutMainLoop();
    
    return 0;
}

void createPlayer(int x1, int y1)
{
    Player *new = initPlayer(x1, y1);
    curr->next = &new->n;
    curr = &new->n;
}

void createDiamond(int x1, int y1)
{
    Diamond *new = initDiamond(x1, y1);
    curr->next = &new->n;
    curr = &new->n;
}

void createPinwheel(int x1, int y1)
{
    Pinwheel *new = initPinwheel(x1, y1);
    curr->next = &new->n;
    curr = &new->n;
}

void createBullet(int num)
{
    double bullet_angle;
    double target_angle;
    Bullet *new;
    for(int i = -num/2; i <= num/2; i++) {
        bullet_angle = M_PI/2;
        target_angle = M_PI/400;
        if(num%2 == 0 && i == 0)
            i++;
        new = initBullet((int)(-cos(p1->bullet_rot + (bullet_angle * i))*-10 + p1->n.pos->x), (int)(-sin(p1->bullet_rot + (bullet_angle * i))*-10 + p1->n.pos->y));
        new->n.target->x = (int)(cos(p1->bullet_rot + (target_angle * i)/1)*width + p1->n.pos->x);
        new->n.target->y = (int)(sin(p1->bullet_rot + (target_angle * i)/1)*width + p1->n.pos->y);
        curr->next = &new->n;
        curr = &new->n;
    }
}

void createExplosion(int x, int y, Vector3* col,double magnitude)
{
    double random = 0;
    
    for(double r = 0; r < M_PI*2;r += M_PI/(50*magnitude)) {
        Particle *new = initParticle(x, y, col->x, col->y, col->z);
        random = ((rand()%100 + 50)/100.0);
        new->n.target->x = cos(r) * (300 * magnitude) * random + x;
        new->n.target->y = sin(r) * (300 * magnitude) * random + y;
        curr->next = &new->n;
        curr = &new->n;
    }
}

void createGrid(int grid_width, int grid_height, int grid_size)
{
    for(int x = 0; x < grid_width; x += grid_size) {
        for(int y = 0; y < grid_width; y += grid_size) {
            for(int i = 0; i < 2; i++) {
                Grid *new = initGrid(x, y, grid_size/2);
                new->n.target->x = x;
                new->n.target->y = y;
                if(head == NULL) {
                    head = &new->n;
                    curr = &new->n;
                } else {
                    curr->next = &new->n;
                    curr = &new->n;
                }
                Gridline *new_line = initGridline(x, y, grid_size/2);
                new_line->n.target->x = x;
                new_line->n.target->y = y;
                new_line->n.rot_limit = i;
                curr->next = &new_line->n;
                curr = &new_line->n;
            }
        }
    }
}

void drawLine(Vector2* first, Vector2* second, Vector3* color)
{
    Vector2* diff = malloc(sizeof(Vector2));
    subVector(diff, *first, *second);
    normalizeVector(diff, *diff);
    perpendicularVector(diff, *diff);
    float transparency;
    
    for(int i = -detail; i < detail + 1; i++)
    {
        transparency = max(1.0/(1.0 + (((1.0/0.99) - 1.0) * pow(M_E, 2.0*abs(i)))), 0.2);
        glBegin(GL_LINES);
        glColor4f(color->x, color->y, color->z, transparency);
        glVertex2f(first->x + (diff->x * i * distance), first->y + (diff->y * i * distance));
        glVertex2f(second->x + (diff->x * i * distance), second->y + (diff->y * i * distance));
        glEnd();
    }
    
    
    free(diff);
}

void mainThread()
{
    timer++;
    display();
    
    if(p1->n.alive == 1 && p1->bullet_fire == p1->bullet_rate) {
        if(p1->bullet_rot > M_PI*2)
            p1->bullet_rot -= M_PI*2;
        else if(p1->bullet_rot < 0)
            p1->bullet_rot += M_PI*2;
        
        createBullet(2);
    }
    
    if(p1->bullet_fire > 0)
        p1->bullet_fire--;
    
    struct NeonObj *pointer = head;
    
    if(p1 != NULL && p1->n.deconstfunc(head, &p1->n) == 1 && p1->n.alive == 1) {
        createExplosion(p1->n.pos->x, p1->n.pos->y, p1->n.color, 2);
        p1->n.alive = 0;
        p1->n.size = 0;
        copyVector(p1->n.target, p1->n.pos);
        pointer = pointer->next;
        
        while (pointer != NULL) {
            if(pointer->type >= 10)
                pointer->health = -1;
            pointer = pointer->next;
        }
    }
    
    Vector2* camera = malloc(sizeof(Vector2));
    camera->x = width/2;
    camera->y = height/2;
    subVector(camera, *p1->n.pos, *camera);
    
    while(pointer != NULL) {
        if(pointer->next != NULL && ((pointer->pos->x > (camera->x) - pointer->size && pointer->pos->x < (camera->x + width) + pointer->size && pointer->pos->y > (camera->y) - pointer->size && pointer->pos->y < (camera->y + height) + pointer->size) || pointer->type == 2) && (pointer->next->deconstfunc(head, pointer->next) == 1 || (pointer->next->health == -1 && pointer->next->type >= 10))) {
            struct NeonObj *temp = pointer->next;
            
            if(temp->type >= 10) {
                if(rand()%2 == 1)
                    createDiamond(rand()%width, rand()%height);
                else
                    createPinwheel(rand()%width, rand()%height);
                if(pointer->next->health != -1)
                    createExplosion(temp->pos->x, temp->pos->y, temp->color, 1);
                else
                    createExplosion(temp->pos->x, temp->pos->y, temp->color, 0.5);
            }
            
            if(pointer->next->next != NULL)
                pointer->next = pointer->next->next;
            else {
                curr = pointer;
                pointer->next = NULL;
            }

            free(temp->color);
            free(temp->pos);
            free(temp->target);
            free(temp->shape);
            free(temp->vel);
            free(temp);
        }
        animate(pointer);
        pointer = pointer->next;
    }
    
    usleep((1000 * 1000) / frames_per_second);
}
