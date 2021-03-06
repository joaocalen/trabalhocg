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
    glTranslatef(0,-radius*4/16,0);    
    glColor3f (R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/16, -3*radius/16);
        glVertex2f (radius/16, -3*radius/16);
        glVertex2f (radius/16, 3*radius/16);
        glVertex2f (-radius/16, 3*radius/16);
    glEnd();
}
void Character::DrawLeftLeg(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
    if(right_sided)
        glRotatef(thetaLeg, 0, 0, 1);
    else
        glRotatef(-thetaLeg, 0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/32, 0);
        glVertex2f (radius/32, 0);
        glVertex2f (radius/32, 4*radius/16);
        glVertex2f (-radius/32, 4*radius/16);
    glEnd();
    glTranslatef(0,4*radius/16,0);
    if(right_sided)
        glRotatef(-30, 0, 0, 1);
    else
        glRotatef(15, 0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/32, 0);
        glVertex2f (radius/32, 0);
        glVertex2f (radius/32, 4*radius/16);
        glVertex2f (-radius/32, 4*radius/16);
    glEnd();    
    glPopMatrix();
}

void Character::DrawRightLeg(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
    if(right_sided)
        glRotatef(-thetaLeg, 0, 0, 1);
    else
        glRotatef(thetaLeg, 0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/32, 0);
        glVertex2f (radius/32, 0);
        glVertex2f (radius/32, 4*radius/16);
        glVertex2f (-radius/32, 4*radius/16);
    glEnd();
    glTranslatef(0,4*radius/16,0);
    if(right_sided)
        glRotatef(-15, 0, 0, 1);
    else
        glRotatef(30, 0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/32, 0);
        glVertex2f (radius/32, 0);
        glVertex2f (radius/32, 4*radius/16);
        glVertex2f (-radius/32, 4*radius/16);
    glEnd();    
    glPopMatrix();
}

void Character::DrawLegs(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
    glTranslatef(0,-3*radius/16,0);
    glColor3f (R, G, B);
    glRotatef(180,0,0,1);
    DrawLeftLeg(radius,R,G,B);
    DrawRightLeg(radius,R,G,B);    
    glPopMatrix();
}
void Character::DrawArm(GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
    if(this->right_sided)
    {
        glTranslatef(radius/16,0,0);
        glRotatef(-thetaArm,0,0,1);
    }
    else
    {
        glTranslatef(-radius/16,0,0);
        glRotatef(thetaArm,0,0,1);
    }
    glColor3f (R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f (-radius/32, 0);
        glVertex2f (radius/32, 0);
        glVertex2f (radius/32, radius/6);
        glVertex2f (-radius/32, radius/6);
    glEnd();
    glPopMatrix();
}
void Character::DrawCharacter(GLfloat x, GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
    glTranslatef(x,y + radius,0);
    DrawHead(radius*2, R, G, B);
    DrawBody(radius*2, R, G, B);
    DrawArm(radius*2, R, G, B);
    DrawLegs(radius*2, R, G, B);
    glPopMatrix();
}

void Character::MoveX(GLfloat dx, GLdouble deltaTime, bool jumping)
{
    if(dx > 0) this->right_sided = true;
    else this->right_sided = false;
    this -> gX += dx * deltaTime;
    if(!jumping){
        if(abs(thetaLeg + abs(dx * deltaTime * 3)) > 45){
            thetaLegIncreasing = !thetaLegIncreasing;
            // thetaLeg = 45 * signbit(thetaLeg);
        }
        if(thetaLegIncreasing)
            thetaLeg += abs(dx * deltaTime* 3);
        else
            thetaLeg -= abs(dx * deltaTime* 3);        
    }
    if(thetaLeg > 45) thetaLeg = 45;        
}

void Character::MoveY(GLfloat dy, GLdouble deltaTime)
{
    this -> gY += dy * deltaTime;
}

Shot* Character::Shoot()
{
    Shot* shot;
    if(right_sided)
        shot = new Shot(gX + 2*gRadius/3, gY, -thetaArm, gVel*2/100);
    else
        shot = new Shot(gX - 2*gRadius/3, gY , thetaArm, gVel*2/100);
    return shot;
}

GLfloat Character::getgX()
{
    return this->gX;
}
GLfloat Character::getgY()
{
    return this->gY;
}
GLfloat Character::getgRadius()
{
    return this->gRadius;
}
GLfloat Character::getgVel()
{
    return this->gVel;
}

GLfloat Character::getThetaArm()
{
    return this->thetaArm;
}
GLfloat Character::setThetaArm(GLfloat thetaArm)
{
    this->thetaArm = thetaArm;
}

bool Character::getRightSided()
{
    return right_sided;
}

void Character::setRightSided(bool right_sided)
{
    this->right_sided = right_sided;
}