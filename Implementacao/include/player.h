#ifndef PLAYER_H
#define	PLAYER_H
#include "../include/character.h"


class Player : Character {    
private:    
public:
    Player(GLfloat gX, GLfloat gY, GLfloat gHeight, GLfloat gVel):Character(gX, gY, gHeight, gVel){
    };
    void Draw(){ 
        // DesenhaTiro(gX, gY);
    };
    void Move();    
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        // xOut = gX;
        // yOut = gY;
    };
};

#endif	/* PLAYER_H */