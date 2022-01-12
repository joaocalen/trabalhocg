#ifndef CHARACTER_H
#define	CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>

class Character {    
private:
    void DrawHead(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawBody(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawLeg(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawCharacter(GLfloat x, GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void Shoot(GLfloat x, GLfloat y);
public:
    GLfloat gX;
    GLfloat gY;
    GLfloat gHeight;
    GLfloat gVel;
    Character(GLfloat gX, GLfloat gY, GLfloat gHeight, GLfloat gVel){
        this->gX = gX;
        this->gY = gY;
        this->gHeight = gHeight;
        this->gVel = gVel;
    };
    void Draw(GLfloat x,GLfloat y, GLfloat radius, GLfloat R, GLfloat G, GLfloat B){ 
        DrawCharacter(x, y, radius, R, G, B);
    };
    void Move(GLfloat dx);    
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
};

#endif	/* CHARACTER_H */