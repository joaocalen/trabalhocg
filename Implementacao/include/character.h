#ifndef CHARACTER_H
#define	CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>

class Character {
    GLfloat gX;
    GLfloat gY;
    GLfloat gHeight;
    GLfloat gVel;
private:
    void DrawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawBody(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawLeg(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void Shoot(GLfloat x, GLfloat y);
public:
    Character(GLfloat gX, GLfloat gY, GLfloat gHeight, GLfloat gVel){
        this->gX = gX;
        this->gY = gY;
        this->gHeight = gHeight;
        this->gVel = gVel;
    };
    void Draw(){ 
        // DesenhaTiro(gX, gY);
    };
    void Move();    
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
};

#endif	/* CHARACTER_H */