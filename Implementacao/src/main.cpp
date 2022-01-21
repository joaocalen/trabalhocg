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

//Componentes do mundo virtual sendo modelado
Arena arena;
// Robo robo; //Um rodo
// Tiro * tiro = NULL; //Um tiro por vez
// Alvo alvo(0, 200); //Um alvo por vez

void renderScene(void)
{
     // Clear the screen.
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT);
    
    arena.Draw();
    
     
    //  if (tiro) tiro->Desenha();
     
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
            //  if (!tiro)
            //     tiro = robo.Atira();
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
    GLfloat gx;
    GLfloat gy;
    arena.player.GetPos(gx,gy);   
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
    // if(tiro){
    //     tiro->Move();

    //     //Trata colisao
    //     if (alvo.Atingido(tiro)){
    //         alvo.Recria(rand()%500 - 250, 200);
    //     }

    //     if (!tiro->Valido()){ 
    //         delete tiro;
    //         tiro = NULL;
    //     }
    // }
    
    
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