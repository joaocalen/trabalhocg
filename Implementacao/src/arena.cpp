#include "../include/arena.h"
#include <iostream>

void Arena::LoadComponents(){
    
    tinyxml2::XMLDocument svg;
    tinyxml2::XMLNode* main_element;
    tinyxml2::XMLElement* element;
    double cx, cy, r, width, height;
    const char* fill;    
    svg.LoadFile(this->svg_path.c_str());
    main_element = svg.FirstChildElement("svg");
    
    element = main_element->FirstChildElement("rect");
    while (element != NULL){
        element->QueryDoubleAttribute("x", &cx);
        element->QueryDoubleAttribute("y", &cy);
        element->QueryDoubleAttribute("width", &width);
        element->QueryDoubleAttribute("height", &height);
        element->QueryStringAttribute("fill",&fill);
        if(!strcmp("blue",fill)){
            this -> width_absolute = width;
            this -> height_absolute = height;
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
            Player player(cx,cy,r,1.0);
            this->player = player;
        } else if(!strcmp("red",fill)){
            Enemy enemy(cx,cy,r,1.0);
            this->enemies.push_back(enemy);
        } else{
            cout <<"Erro inesperado! " << endl;
        } 
        element = element -> NextSiblingElement("circle");
    }       
}