#include "../include/obstacle.h"

void Obstacle::DrawObstacle(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    glColor3f (0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f (-width/2, 0);
        glVertex2f (width/2, 0);
        glVertex2f (width/2, height);
        glVertex2f (-width/2, height);
    glEnd();
    glPopMatrix();
}