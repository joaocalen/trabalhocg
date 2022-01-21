#include "../include/player.h"

void Player::setgX(GLfloat gX)
{
    this->gX = gX;
}
void Player::setgY(GLfloat gY)
{
    this->gY = gY;
}
void Player::setgRadius(GLfloat gRadius)
{
    this->gRadius = gRadius;
}
void Player::setgVel(GLfloat gVel)
{
    this->gVel = gVel;
}
void Player::setFalling(bool falling)
{
    this->falling = falling;
}

bool Player::getFalling()
{
    return this->falling;
}

void Player::setJumping(bool jumping)
{
    this->jumping = jumping;
}

bool Player::getJumping()
{
    return this->jumping;
}
