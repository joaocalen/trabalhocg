#ifndef PLAYER_H
#define	PLAYER_H
#include "../include/character.h"


class Player : Character {
private:    
public:
    Player(GLfloat gX, GLfloat gY, GLfloat gHeight, GLfloat gVel):Character(gX, gY, gHeight, gVel){
    };
    void Draw(){ 
        Character::Draw(gX, gY, gHeight, 0.0,1.0,0.0);
    };    
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        // xOut = gX;
        // yOut = gY;
    };
};

#endif	/* PLAYER_H */