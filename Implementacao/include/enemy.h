#ifndef ENEMY_H
#define	ENEMY_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/character.h"


class Enemy : Character {    
private:    
public:
    Enemy(GLfloat gX, GLfloat gY, GLfloat gHeight, GLfloat gVel):Character(gX, gY, gHeight, gVel){        
    };
    void Draw(){ 
       Character::Draw(gX, gY, gHeight, 1,0,0);
    };
    void Move();    
};

#endif	/* ENEMY_H */