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
    GLint width_absolute; 
    GLint height_absolute;
    GLint width_local;
    GLint height_local;
    vector<Enemy> enemies;
    vector<Obstacle> obstacles;
    Player player;
    string svg_path;    

    // pensar em como representar outras classes aqui dentro, se é que vou representar nessa classe.    
private:
    void DrawObstacle(vector<Obstacle> obstacles);
    void DrawPlayer(Player player);
    void DrawEnemies(vector<Enemy> enemies);
    void ChangeCameraPosition(GLfloat x, GLfloat y);
public:
    Arena(string path){
        width_absolute = 0; 
        height_absolute = 0;
        height_local = 0;
        width_local = 0;
        svg_path = path;        
    };
    void Draw(){ 
        DrawObstacle(obstacles);
        DrawPlayer(player);
        DrawEnemies(enemies);        
    };
    void LoadComponents();
    // void Recria(GLfloat x, GLfloat y);
    // bool Atingido(Tiro *tiro);
};

#endif	/* ARENA_H */
