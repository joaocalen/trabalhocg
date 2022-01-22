#ifndef PLAYER_H
#define	PLAYER_H
#include "../include/character.h"


class Player : Character {
    bool jumping;
    bool falling;
private:    
public:
    
    Player():Character(0, 0, 0, 0){
    };
    Player(GLfloat gX, GLfloat gY, GLfloat gHeight, GLfloat gVel):Character(0, 0, 0, 0){
    };
    void Draw(){
        Character::Draw(gX, gY, gRadius, 0.0,1.0,0.0);
    };
    void MoveX(GLfloat dx){
        Character::MoveX(dx);
    }
    void MoveY(GLfloat dy){
        Character::MoveY(dy);
    }
    void setgX(GLfloat gX);
    void setgY(GLfloat gY);
    void setgRadius(GLfloat gHeight);
    void setgVel(GLfloat gVel);
    void setJumping(bool jumping);
    void setFalling(bool falling);
    Shot* Shoot(){Character::Shoot();};
    GLfloat getgX(){Character::getgX();};
    GLfloat getgY(){Character::getgY();};
    GLfloat getgRadius(){Character::getgRadius();};
    GLfloat getgVel(){Character::getgVel();};
    GLfloat getThetaArm(){Character::getThetaArm();};
    Shot* getShot(){Character::getShot();};
    void deleteShot(){Character::deleteShot();};
    GLfloat setThetaArm(GLfloat theta){Character::setThetaArm(theta);};
    bool getJumping();
    bool getFalling();    
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
};

#endif	/* PLAYER_H */