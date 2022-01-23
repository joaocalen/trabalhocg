#include "../include/shot.h"
#include <math.h>
#define DISTANCIA_MAX 500

void Shot::DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f (R, G, B);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 10){
            glVertex2d(radius * cos(i * M_PI / 180), radius * sin(i * M_PI / 180));
        }
    glEnd();
}

void Shot::DrawShot(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    DrawCircle(0.3, 1, 1, 1);
    glPopMatrix();
}

void Shot::Move()
{
    gX += gVel * sin(-gDirectionAng * M_PI / 180);
    gY += gVel * cos(-gDirectionAng * M_PI/180);
}

bool Shot::Valid()
{
    return DISTANCIA_MAX > sqrt(pow(gX-gXInit,2) + pow(gY-gYInit,2));
}