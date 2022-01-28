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
#define INC_KEY 1
#define INC_KEYIDLE 0.01


class Arena {
private:
    void DrawObstacle(vector<Obstacle> obstacles);
    void DrawPlayer(Player player);
    void DrawEnemies(vector<Enemy> enemies);
    void ChangeCameraPosition(GLfloat x, GLfloat y);
    void DrawArena(GLint width, GLint height, GLfloat x, GLfloat y);
public:
    GLfloat width; 
    GLfloat height;
    GLfloat centerX;
    GLfloat centerY;
    vector<Enemy> enemies;
    vector<Obstacle> obstacles;
    Player player;
    string svg_path;
    bool win;
    bool loose;
    Arena(){        
        this->width = 0; 
        this->height = 0;                
        win = false;
        loose = false;
    };
    void Draw(){ 
        DrawArena(width, height, centerX, centerY);
        DrawObstacle(obstacles);
        DrawPlayer(player);
        DrawEnemies(enemies);        
    };
    void LoadComponents();
    bool ableToMoveX(GLfloat dx, GLfloat x, GLfloat y, GLfloat radius, Player player, vector<Enemy> others, vector<Obstacle> obstacles);
    bool ableToMoveY(GLfloat dy, GLfloat x, GLfloat y, GLfloat radius, Player player, vector<Enemy> others, vector<Obstacle> obstacles);
    bool checkCollisionArenaBounds(GLfloat x1, GLfloat y1, GLfloat radius1);
    bool checkCollisionCharacter(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat radius1, GLfloat radius2);
    bool checkCollisionObstacle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat radius, GLfloat height, GLfloat width);
    void destroy();
    // void Recria(GLfloat x, GLfloat y);
    // bool Atingido(Tiro *tiro);
};

#endif	/* ARENA_H */
