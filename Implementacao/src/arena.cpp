#include "../include/arena.h"
#include <iostream>

void Arena::LoadComponents(string svg_path){
    
    tinyxml2::XMLDocument svg;
    tinyxml2::XMLNode* main_element;
    tinyxml2::XMLElement* element;
    double cx, cy, r, width, height;
    const char* fill;    
    svg.LoadFile(svg_path.c_str());
    main_element = svg.FirstChildElement("svg");
    
    element = main_element->FirstChildElement("rect");
    while (element != NULL){
        element->QueryDoubleAttribute("x", &cx);
        element->QueryDoubleAttribute("y", &cy);
        element->QueryDoubleAttribute("width", &width);
        element->QueryDoubleAttribute("height", &height);
        element->QueryStringAttribute("fill",&fill);
        if(!strcmp("blue",fill)){
            this -> centerX = cx;
            this -> centerY = cy;
            this -> width = width;
            this -> height = height;
        } else if(!strcmp("black",fill)){
            //antes x = -136  ----------- agora x = 27
            //antes y = 160  ------------- agora y = 65
            cy = cy - this->centerY - this->height/2;
            cx = cx - this->centerX - this->width/2;
            Obstacle ob(cx + width/2,-cy -height,width,height);
            this->obstacles.push_back(ob);
        } else{
            cout <<"Erro inesperado! " << endl;
        }        
        element = element -> NextSiblingElement("rect");
    }

    element = main_element->FirstChildElement("circle");
    while (element != NULL){
        element->QueryDoubleAttribute("cx", &cx);
        element->QueryDoubleAttribute("cy", &cy);
        element->QueryDoubleAttribute("r", &r);
        element->QueryStringAttribute("fill",&fill);        
        cy = cy - this->centerY - this->height/2;
        cx = cx - this->centerX - this->width/2;
        if(!strcmp("green",fill)){
            Player player(cx,-cy,r,1.0);
            this->player = &player;
        } else if(!strcmp("red",fill)){
            Enemy enemy(cx,-cy,r,1.0);
            this->enemies.push_back(enemy);
        } else{
            cout <<"Erro inesperado! " << endl;
        } 
        element = element -> NextSiblingElement("circle");
    }       
}

void Arena::DrawArena(GLint width, GLint height, GLfloat x, GLfloat y)
{
    glPushMatrix();
    // glTranslatef(0,0,0);    
    glColor3f (0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex2f (-width/2, -height/2);
        glVertex2f (width/2, -height/2);
        glVertex2f (width/2, height/2);
        glVertex2f (-width/2, height/2);
    glEnd();
    glPopMatrix();
}

void Arena::DrawPlayer(Player* player)
{
    player->Draw();
}

void Arena::DrawObstacle(vector<Obstacle> obstacles)
{
    for (Obstacle o : obstacles){
        o.Draw();
    }
}

void Arena::DrawEnemies(vector<Enemy> enemies)
{
    for (Enemy e : enemies){
        e.Draw();
    }
}