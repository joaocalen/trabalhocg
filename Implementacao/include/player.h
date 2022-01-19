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
    void setgX(GLfloat gX);
    void setgY(GLfloat gY);
    void setgRadius(GLfloat gHeight);
    void setgVel(GLfloat gVel);
    GLfloat getgX(){Character::getgX();};
    GLfloat getgY(){Character::getgY();};
    GLfloat getgRadius(){Character::getgRadius();};
    GLfloat getgVel(){Character::getgVel();};
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
};

#endif	/* PLAYER_H */