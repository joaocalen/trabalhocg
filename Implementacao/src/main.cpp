#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "../include/arena.h"
#define WINDOW_SIZE 500


// TODO:
/*
Finish the game if player gets shot. -> (done)
Final messages (win or loose). -> (done).
Fix Jump. -> (almost done)
Fix character moviment.
Create win condition when the player gets in the final spot. -> (done)
Fix camera to follow player. (done)
Create parameters for the program (deltaTime). -> (done)
Fix IA to shoot in player direction (optional).
Recriate the game when the "r" button is pressed. -> (done)
Read the svg file from the terminal
*/


//Key status
int keyStatus[256];

// Window dimensions
const GLint Width = 700;
const GLint Height = 700;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

//Controla a animacao do robo
int ia = 1;
int old_x = -INT_MAX;
int old_y = -INT_MAX;
static char str[999];
bool availableToShoot = true;
bool camera = true;
Arena arena;

void RenderFinalMessage()
{  
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2f(arena.player.getgX(), 0);
    if(arena.win)
        sprintf(str, "VITORIA!");
    else
        sprintf(str, "GAME OVER!");
    char* text;    
    text = str;
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *text);
        text++;
    }
    
}

void renderScene(void)
{
     // Clear the screen.
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT);     
    
    arena.Draw();

    for(Shot* s : arena.shots)
    {
        s->Draw();
    }    
    if(arena.win || arena.loose)
    {
        RenderFinalMessage();        
    }
    //  alvo.Desenha();

     glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
             ia = !ia;
             break;
        case '2':
             camera = !camera;
             break;
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 'r':
        case 'R':
            arena.destroy();
            arena.LoadComponents();
             break;
        case ' ':
        keyStatus[(int)(' ')] = 1; //Using keyStatus trick
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
    if (old_y == -INT_MAX) old_y = y;
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
            if(arena.player.getAbleToJump()){
                arena.player.setYIniJump(arena.player.getgY());                
                arena.player.setJumping(1);  
            }          
        }else
        {
            arena.player.setJumping(0);
            arena.player.setFalling(1);            
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
            if(availableToShoot)
                arena.shots.push_back(arena.player.Shoot());
    }
}

void idle(void)
{
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    static GLdouble timeToShoot = 0;
    double inc = INC_KEYIDLE * arena.player.getgVel();
    double incy = INC_KEYIDLE * arena.player.getgVel();
    //Treat win/loose condition
    if(arena.win || arena.loose){        
        return;
    }
    
    // Camera
    if (camera){
        glMatrixMode(GL_PROJECTION); 
        glLoadIdentity();
        glOrtho(arena.player.getgX() - arena.height/2, arena.player.getgX() + arena.height/2, -arena.height/2, arena.height/2,-1,1);    
        glMatrixMode(GL_MODELVIEW); 
    } else{
        glMatrixMode(GL_PROJECTION); 
        glLoadIdentity();
        glOrtho(-(ViewingWidth/2),     // X coordinate of left edge          
            (ViewingWidth/2),     // X coordinate of right edge         
            -(ViewingHeight/2),     // Y coordinate of bottom edge        
            (ViewingHeight/2),-1,1);    
        glMatrixMode(GL_MODELVIEW); 
    }

    
    if(keyStatus[(int)('a')])
    {
        if(arena.ableToMoveX(-inc*deltaTime, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.player.MoveX(-inc, deltaTime, arena.player.getJumping());
    }
    if(keyStatus[(int)('d')])
    {
        if(arena.ableToMoveX(inc*deltaTime, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.player.MoveX(inc, deltaTime, arena.player.getJumping());
    }   

    if(arena.player.getJumping())
    {
        arena.player.setAbleToJump(0);
        if(arena.ableToMoveY(incy*deltaTime, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles) && arena.player.getgY() < arena.player.getYIniJump() + arena.player.getgRadius()*6)
        {
            arena.player.MoveY(incy, deltaTime);
            // arena.player.setJumping(0);
            arena.player.setFalling(0);
        }
        else
        {
            arena.player.setJumping(0);
            arena.player.setAbleToJump(0);
            arena.player.setFalling(1);
        }
    }
    if(arena.player.getFalling())
    {
        if(arena.ableToMoveY(-incy*deltaTime, arena.player.getgX(), arena.player.getgY(), arena.player.getgRadius(),arena.player, arena.enemies, arena.obstacles))
        {
            arena.player.MoveY(-incy, deltaTime);
            arena.player.setAbleToJump(0);
        } 
        else
        {
            arena.player.setFalling(1);
            arena.player.setAbleToJump(1);
        }
    }    
    if(ia){
        for(int i = 0; i < arena.enemies.size(); i++)
        {
            if (arena.enemies.at(i).getRightSided())
            {
                if(arena.ableToMoveX(inc*deltaTime, arena.enemies.at(i).getgX(), arena.enemies.at(i).getgY(), arena.enemies.at(i).getgRadius(), arena.player, arena.enemies, arena.obstacles) && !arena.ableToMoveY(-incy, arena.enemies.at(i).getgX(), arena.enemies.at(i).getgY(), arena.enemies.at(i).getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.enemies.at(i).MoveX(inc, deltaTime, false);
                else arena.enemies.at(i).MoveX(-inc, deltaTime,false);
            }
            else
            {
                if(arena.ableToMoveX(-inc*deltaTime, arena.enemies.at(i).getgX(), arena.enemies.at(i).getgY(), arena.enemies.at(i).getgRadius(), arena.player, arena.enemies, arena.obstacles) && !arena.ableToMoveY(-incy, arena.enemies.at(i).getgX(), arena.enemies.at(i).getgY(), arena.enemies.at(i).getgRadius(),arena.player, arena.enemies, arena.obstacles)) arena.enemies.at(i).MoveX(-inc, deltaTime, false);
                else arena.enemies.at(i).MoveX(inc, deltaTime,false);
            }
            
        }   
    }
    
    for(int i = 0; i < arena.shots.size(); i++)
    {
        GLfloat x_shot;
        GLfloat y_shot;
        arena.shots.at(i) -> GetPos(x_shot,y_shot);
        arena.shots.at(i) -> Move(deltaTime);
        // if(!s->Valid())
        // {
        //     arena.shots.erase(arena.shots.begin() + aux);
        //     free(s);
        // }
        if (!arena.ableToMoveY(0, x_shot, y_shot, 0.3, arena.player, arena.enemies, arena.obstacles) || !arena.ableToMoveX(0, x_shot, y_shot, 0.3, arena.player, arena.enemies, arena.obstacles))
        {
            free(arena.shots.at(i));
            arena.shots.erase(arena.shots.begin() + i);            
        }    
    }
    // if(arena.player.getShot()){
    //     GLfloat x_shot;
    //     GLfloat y_shot;
    //     arena.player.getShot()->GetPos(x_shot,y_shot);

    //     arena.player.getShot()->Move(deltaTime);        

    //     if (!arena.player.getShot()->Valid()){ 
    //         arena.player.deleteShot();
    //     }
    //     if (!arena.ableToMoveY(0, x_shot, y_shot, 0.3, arena.player, arena.enemies, arena.obstacles) || !arena.ableToMoveX(0, x_shot, y_shot, 0.3, arena.player, arena.enemies, arena.obstacles))
    //     {
    //         arena.player.deleteShot();
    //     }
    // }
    if(ia){
        for(int i = 0; i < arena.enemies.size(); i++)
        {
            if(timeToShoot == 0)
            {
                arena.shots.push_back(arena.enemies.at(i).Shoot());
            }
        }
    }
    timeToShoot += deltaTime;
    if(timeToShoot > 1000)
        timeToShoot = 0;   
   
    glutPostRedisplay();
}
 
int main(int argc, char *argv[])
{   
    if (argc <= 1){
        cout << "Erro, por favor insira o caminho completo do arquivo" << endl;
        return 0;
    }else{
        arena.svg_path = argv[argc-1];
        arena.LoadComponents();
    }
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
