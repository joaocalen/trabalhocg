#ifndef CHARACTER_H
#define	CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../include/obstacle.h"
#include "vector"
using namespace std;

class Character {    
private:
    void DrawHead(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawBody(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawLeftLeg(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawRightLeg(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawLegs(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawArm(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawCharacter(GLfloat x, GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void Shoot(GLfloat x, GLfloat y);
public:
    GLfloat gX;
    GLfloat gY;
    GLfloat gRadius;
    GLfloat gVel;
    Character(GLfloat gX, GLfloat gY, GLfloat gRadius, GLfloat gVel){
        this->gX = gX;
        this->gY = gY;
        this->gRadius = gRadius;
        this->gVel = gVel;
    };
    void Draw(GLfloat x,GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B){ 
        DrawCharacter(x, y, radius, R, G, B);
    };
    void MoveX(GLfloat dx);
    void MoveY(GLfloat dy);
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
    GLfloat getgX();
    GLfloat getgY();
    GLfloat getgRadius();
    GLfloat getgVel();
    
    
};

#endif	/* CHARACTER_H */