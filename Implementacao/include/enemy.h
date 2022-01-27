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
    void MoveX(GLfloat dx, GLdouble deltaTime){
        Character::MoveX(dx, deltaTime);
    }
    void MoveY(GLfloat dy, GLdouble deltaTime){
        Character::MoveY(dy, deltaTime);
    }
    Shot* Shoot(){Character::Shoot();};
    Shot* getShot(){Character::getShot();};
    void deleteShot(){Character::deleteShot();};
    GLfloat getgX(){Character::getgX();};
    GLfloat getgY(){Character::getgY();};
    GLfloat getgRadius(){Character::getgRadius();};
    GLfloat getgVel(){Character::getgVel();};
    bool getRightSided(){Character::getRightSided();};
    void setRightSided(bool value){Character::setRightSided(value);};
};

#endif	/* ENEMY_H */