#ifndef ENEMY_H
#define	ENEMY_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/character.h"


class Enemy : Character {    
private:    
public:
    Enemy(GLfloat gX, GLfloat gY, GLfloat gRadius, GLfloat gVel):Character(gX, gY, gRadius, gVel){        
    };
    void Draw(){ 
       Character::Draw(gX, gY, gRadius, 1,0,0);
    };
    void Move();
    GLfloat getgX(){Character::getgX();};
    GLfloat getgY(){Character::getgY();};
    GLfloat getgRadius(){Character::getgRadius();};
    GLfloat getgVel(){Character::getgVel();};
};

#endif	/* ENEMY_H */