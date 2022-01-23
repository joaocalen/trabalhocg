#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "../include/arena.h"
#define INC_KEY 1
#define INC_KEYIDLE 0.01
#define WINDOW_SIZE 500

//Key status
int keyStatus[256];

// Window dimensions
const GLint Width = 700;
const GLint Height = 700;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

//Controla a animacao do robo
int animate = 0;
int old_x = -1;
int old_y = -1;
//Componentes do mundo virtual sendo modelado
Arena arena;
// Robo robo; //Um rodo
// Shot * shot = NULL; //Um tiro por vez
// Alvo alvo(0, 200); //Um alvo por vez

void renderScene(void)
{
     // Clear the screen.
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT);
    
    arena.Draw();
    
     
    if (arena.player.getShot()) arena.player.getShot()->Draw();
    
    for (int i = 0; i < arena.enemies.size(); i++)
    {
        if (arena.enemies.at(i).getShot()) arena.enemies.at(i).getShot()->Draw();
    }
    
     
    //  alvo.Desenha();

     glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
             animate = !animate;
             break;
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 'f':
        case 'F':
            //  robo.RodaBraco1(-INC_KEY);   //Without keyStatus trick
             break;
        case 'r':
        case 'R':
            //  robo.RodaBraco1(+INC_KEY);   //Without keyStatus trick
             break;
        case 'g':
        case 'G':
            //  robo.RodaBraco2(-INC_KEY);   //Without keyStatus trick
             break;
        case 't':
        case 'T':
            //  robo.RodaBraco2(+INC_KEY);   //Without keyStatus trick
             break;
        case 'h':
        case 'H':
            //  robo.RodaBraco3(-INC_KEY);   //Without keyStatus trick
             break;
        case 'y':
        case 'Y':
            //  robo.RodaBraco3(+INC_KEY);   //Without keyStatus trick
             break;
        case ' ':             
             break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void motion(int x, int y)
{    
    if (old_y == -1) old_y = y;
    arena.player.setThetaArm(arena.player.getThetaArm() + 0.3*(y - old_y));
    old_y = y;
    if(fabs(arena.player.getThetaArm()) > 135) arena.player.setThetaArm(135);
    if(fabs(arena.player.getThetaArm()) < 45) arena.player.setThetaArm(45);
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glOrtho(-(ViewingWidth/2),     // X coordinate of left edge          
            (ViewingWidth/2),     // X coordinate of right edge         
            -(ViewingHeight/2),     // Y coordinate of bottom edge        
            (ViewingHeight/2),     // Y coordinate of top edge           
            -100,     // Z coordinate of the “near” plane   
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix
    glLoadIdentity();
    
}

void mouseclick(int button, int state, int x, int y)
{
    if(button == GLUT_RIGHT_BUTTON){
        if(state == GLUT_DOWN)
        {
            arena.player.setJumping(0);
            arena.player.setFalling(1);
        }else
        {
            arena.player.setJumping(1);            
        }
    }
    if (button == GLUT_LEFT_BUTTON && state != GLUT_DOWN)
    {
        if (!arena.player.getShot())
            arena.player.Shoot();
    }
}

void idle(void)
{
    double inc = INC_KEYIDLE;
    double incy = 0.05;
    //Treat keyPress
    if(keyStatus[(int)('a')])
    {
        if(arena.ableToMoveX(-inc, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.player.MoveX(-inc);
    }
    if(keyStatus[(int)('d')])
    {
        if(arena.ableToMoveX(inc, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.player.MoveX(inc);
    }
    
    for(int i = 0; i < arena.enemies.size(); i++)
    {
        if (arena.enemies.at(i).getRightSided())
        {
            if(arena.ableToMoveX(inc, arena.enemies.at(i).getgX(), arena.enemies.at(i).getgY(), arena.enemies.at(i).getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.enemies.at(i).MoveX(inc);
            else arena.enemies.at(i).setRightSided(false);
        }
        else
        {
            if(arena.ableToMoveX(-inc, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.enemies.at(i).MoveX(-inc);
            else arena.enemies.at(i).setRightSided(true);
        }
        
    }

    if(arena.player.getJumping())
    {
        if(arena.ableToMoveY(-incy, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles))
        {
            arena.player.MoveY(-incy);
            // arena.player.setJumping(0);
            arena.player.setFalling(0);
        }
    }
    if(arena.player.getFalling())
    {
        if(arena.ableToMoveY(incy, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.player.MoveY(incy);
        else arena.player.setFalling(0);
    }
    
    //Trata o tiro (soh permite um tiro por vez)
    //Poderia usar uma lista para tratar varios tiros
    if(arena.player.getShot()){
        GLfloat x_shot;
        GLfloat y_shot;
        arena.player.getShot()->GetPos(x_shot,y_shot);

        arena.player.getShot()->Move();        

        if (!arena.player.getShot()->Valid()){ 
            arena.player.deleteShot();
        }
        if (!arena.ableToMoveY(0, x_shot, y_shot, 0.3, arena.player, arena.enemies, arena.obstacles) || !arena.ableToMoveX(0, x_shot, y_shot, 0.3, arena.player, arena.enemies, arena.obstacles))
        {
            arena.player.deleteShot();
        }
    }
    
    for(int i = 0; i < arena.enemies.size(); i++)
    {
        if(arena.enemies.at(i).getShot()){
            GLfloat x_shot;
            GLfloat y_shot;
            arena.enemies.at(i).getShot()->GetPos(x_shot,y_shot);

            arena.enemies.at(i).getShot()->Move();
            if (!arena.enemies.at(i).getShot()->Valid()){ 
                arena.enemies.at(i).deleteShot();
            }
            if (!arena.ableToMoveY(0, x_shot, y_shot, 0.3, arena.player, arena.enemies, arena.obstacles) || !arena.ableToMoveX(0, x_shot, y_shot, 0.3, arena.player, arena.enemies, arena.obstacles))
            {
                arena.enemies.at(i).deleteShot();
            }
        }
        else{
            arena.enemies.at(i).Shoot();
        }        
    }
    
    
    //Control animation
    // if (animate){
    //     static int dir = 1;
    //     if (robo.ObtemX() > (ViewingWidth/2)){
    //         dir *= -1;
    //     }
    //     else if (robo.ObtemX() < -(ViewingWidth/2)){
    //         dir *= -1;
    //     }
    //     robo.MoveEmX(dir*INC_KEYIDLE);
    // }
    
    glutPostRedisplay();
}
 
int main(int argc, char *argv[])
{    
    arena.LoadComponents("/home/joaogobeti/Joao/UFES/Computacao/computacao_grafica/Trabalho_2D/Enunciado/arena_teste.svg");
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(WINDOW_SIZE,WINDOW_SIZE);
    glutInitWindowPosition(150,50);
    glutCreateWindow("trabalhocg");
    
    
    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    glutPassiveMotionFunc(motion);
    glutMouseFunc(mouseclick);
    
    init();
 
    glutMainLoop();
 
    return 0;
}