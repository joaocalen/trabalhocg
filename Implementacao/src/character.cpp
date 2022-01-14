#include "../include/character.h"
#include <iostream>


void Character::DrawHead(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
   glColor3f (R, G, B);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 360; i += 10){
            glVertex2d(radius/16 * cos(i * M_PI / 180), radius/16 * sin(i * M_PI / 180));
        }
    glEnd();
}
void Character::DrawBody(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glTranslatef(0,-radius*5/16,0);    
    glColor3f (R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/8, -radius/4);
        glVertex2f (radius/8, -radius/4);
        glVertex2f (radius/8, radius/4);
        glVertex2f (-radius/8, radius/4);
    glEnd();
}
void Character::DrawLegs(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glTranslatef(radius/16,-radius/4,0);
    glColor3f (R, G, B);
    // glRotatef(45, 0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/32, -7*radius/16);
        glVertex2f (radius/32, -7*radius/16);
        glVertex2f (radius/32, 7*radius/16);
        glVertex2f (-radius/32, 7*radius/16);
    glEnd();
    glTranslatef(-radius/8,0,0);
    // glRotatef(-90, 0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/32, -7*radius/16);
        glVertex2f (radius/32, -7*radius/16);
        glVertex2f (radius/32, 7*radius/16);
        glVertex2f (-radius/32, 7*radius/16);
    glEnd();    
}
void Character::DrawArm(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
    glTranslatef(radius/16,0,0);
    glRotatef(-90,0,0,1);
    glColor3f (R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/32, 0);
        glVertex2f (radius/32, 0);
        glVertex2f (radius/32, radius/4);
        glVertex2f (-radius/32, radius/4);
    glEnd();
    glPopMatrix();
}
void Character::DrawCharacter(GLfloat x, GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();    
    glTranslatef(x,y+radius,0);    
    DrawHead(radius, R, G, B);    
    DrawBody(radius, R, G, B);
    DrawArm(radius, R, G, B);
    DrawLegs(radius, R, G, B);
    glPopMatrix();
}