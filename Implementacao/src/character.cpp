#include "../include/character.h"
#include <iostream>
void Character::DrawBody(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f (R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/2, 0);
        glVertex2f (radius/2, 0);
        glVertex2f (radius/2, radius);
        glVertex2f (-radius/2, radius);
    glEnd();
}
void Character::DrawCharacter(GLfloat x, GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();    
    glTranslatef(x,y,0);
    DrawBody(radius, R, G, B);        
    glPopMatrix();
}