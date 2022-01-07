#ifndef OBSTACLE_H
#define	OBSTACLE_H
#include <GL/gl.h>
#include <GL/glu.h>


class Obstacle {
    GLfloat gXInit;
    GLfloat gYInit; 
    GLfloat gWidth;
    GLfloat gHeight;
private:
public:
    Obstacle(GLfloat gXInit, GLfloat gYInit, GLfloat gWidth, GLfloat gHeight){
        this->gXInit = gXInit;
        this->gYInit = gYInit;
        this->gWidth = gWidth;
        this->gHeight = gHeight;
    };
    void Draw();
    void Move();    
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gXInit;
        yOut = gYInit;
    };
};

#endif	/* OBSTACLE_H */