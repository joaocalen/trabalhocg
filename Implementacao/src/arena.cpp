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
            this -> width = width;
            this -> height = height;
        } else if(!strcmp("black",fill)){
            Obstacle ob(cx,cy,width,height);
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
        if(!strcmp("green",fill)){
            Player player(cx,cy,r*3,1.0);
            this->player = &player;
        } else if(!strcmp("red",fill)){
            Enemy enemy(cx,cy,r*3,1.0);
            this->enemies.push_back(enemy);
        } else{
            cout <<"Erro inesperado! " << endl;
        } 
        element = element -> NextSiblingElement("circle");
    }       
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