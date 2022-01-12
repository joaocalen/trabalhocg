#ifndef ARENA_H
#define	ARENA_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "shot.h"
#include "enemy.h"
#include "player.h"
#include "obstacle.h"
#include "tinyxml2.h"
#include <vector>
#include <string>
using namespace std;

class Arena {
    GLint width; 
    GLint height;
    // GLint centerX;
    // GLint centerY;
    vector<Enemy> enemies;
    vector<Obstacle> obstacles;
    Player* player;
    // pensar em como representar outras classes aqui dentro, se é que vou representar nessa classe.    
private:
    void DrawObstacle(vector<Obstacle> obstacles);
    void DrawPlayer(Player* player);
    void DrawEnemies(vector<Enemy> enemies);
    void ChangeCameraPosition(GLfloat x, GLfloat y);
public:
    Arena(){
        this->width = 0; 
        this->height = 0;                
    };
    void Draw(){ 
        DrawObstacle(obstacles);
        DrawPlayer(player);
        DrawEnemies(enemies);        
    };
    void LoadComponents(string svg_path);
    GLfloat getWidth(){
        return this->width;
    };
    GLfloat getHeigth(){
        return this->height;
    };
    // void Recria(GLfloat x, GLfloat y);
    // bool Atingido(Tiro *tiro);
};

#endif	/* ARENA_H */
