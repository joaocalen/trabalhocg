#ifndef TIRO_H
#define	TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>
#define MAX_DISTANCE 60

class Shot {
    GLfloat gXInit; 
    GLfloat gYInit; 
    GLfloat gX; 
    GLfloat gY; 
    GLfloat gDirectionAng;
    GLfloat gVel;
private:
    void DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawShot(GLfloat x, GLfloat y);
public:
    Shot(GLfloat x, GLfloat y, GLfloat directionAng, GLfloat gVel){
        gXInit = x; 
        gYInit = y; 
        gX = x; 
        gY = y; 
        gDirectionAng = directionAng; 
        this-> gVel = gVel;
    };
    void Draw(){ 
        DrawShot(gX, gY);
    };
    void Move(GLdouble deltaTime);
    bool Valid();
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
};

#endif	/* TIRO_H */
