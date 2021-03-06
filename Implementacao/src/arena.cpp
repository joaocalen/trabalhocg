#include "../include/arena.h"
#include <iostream>

void Arena::LoadComponents(){
    
    tinyxml2::XMLDocument svg;
    tinyxml2::XMLNode* main_element;
    tinyxml2::XMLElement* element;
    double cx, cy, r, width, height;
    const char* fill;
    svg.LoadFile(svg_path.c_str());
    main_element = svg.FirstChildElement("svg");
    this->win = false;
    this->loose = false;
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
            cy = cy - this->centerY - this->height/2;
            cx = cx - this->centerX - this->width/2;
            Obstacle ob(cx + width/2,-cy -height,width,height);
            this->obstacles.push_back(ob);
        } else{
            cout <<"Unknown error while reading the svg." << endl;
            return;
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
            this->player.setgX(cx);
            this->player.setgY(-cy);
            this->player.setgRadius(r);
            this->player.setgVel(0.6*r);
        } else if(!strcmp("red",fill)){
            Enemy enemy(cx,-cy,r,0.6*r);
            this->enemies.push_back(enemy);
        } else{
            cout <<"Unknown error while reading the svg." << endl;
            return;
        } 
        element = element -> NextSiblingElement("circle");
    }
    for(int i = 0; i < this->enemies.size();i++){
        while(ableToMoveY(-INC_KEYIDLE, this->enemies.at(i).getgX(), this->enemies.at(i).getgY(), this->enemies.at(i).getgRadius(), this->player, this->enemies, this->obstacles))
        {
            this->enemies.at(i).MoveY(-INC_KEYIDLE, 1);
        }
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

void Arena::DrawPlayer(Player player)
{
    player.Draw();
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

bool Arena::ableToMoveX(GLfloat dx, GLfloat x, GLfloat y, GLfloat radius, Player player, vector<Enemy> enemies, vector<Obstacle> obstacles)
{
    if(checkCollisionArenaBounds(x + dx, 0, radius))
    {
        if(x == player.getgX() && y == player.getgY() && x + dx + radius > this->width/2)
            win = true;
        return false;
    }     
    for(Obstacle o : obstacles)
    {
        GLfloat oX, oY;
        o.GetPos(oX,oY);
        if(checkCollisionObstacle(x + dx, y, oX, oY, radius, o.GetHeight(), o.GetWidth())) return false;
    }
    if((x != player.getgX() || y != player.getgY()) && checkCollisionCharacter(x + dx, y, player.getgX(), player.getgY(), radius/2, player.getgRadius()/2)){
        if(dx == 0){
            loose = true;
        }
        return false;
    } 
    
    int i = 0;
    for(Enemy e : enemies)
    {
        if((x != e.getgX() || y != e.getgY()) && checkCollisionCharacter(x + dx, y, e.getgX(), e.getgY(), radius/2, e.getgRadius()/2))
        {
            if(dx == 0){
                this->enemies.erase(this->enemies.begin()+i);                
            }
            return false;
        }
        i++; 
    }
    return true;
}

bool Arena::ableToMoveY(GLfloat dy, GLfloat x, GLfloat y, GLfloat radius, Player player, vector<Enemy> enemies, vector<Obstacle> obstacles)
{
    if(checkCollisionArenaBounds(0, y + dy, radius)) return false;    
    for(Obstacle o : obstacles)
    {
        GLfloat oX, oY;
        o.GetPos(oX,oY);
        if(checkCollisionObstacle(x, y + dy, oX, oY, radius, o.GetHeight(),o.GetWidth())) return false;
    }
    if((x != player.getgX() || y != player.getgY()) && checkCollisionCharacter(x, y + dy, player.getgX(), player.getgY(), radius, player.getgRadius()))
    {
        if(dy == 0)
        {
            loose = true;
        }
        return false;
    }    
    int i = 0;
    for(Enemy e : enemies)
    {
        if((x != e.getgX() || y != e.getgY()) && checkCollisionCharacter(x, y + dy, e.getgX(), e.getgY(), radius, e.getgRadius())){
            if(dy == 0){
                this->enemies.erase(this->enemies.begin()+i);                
            }            
            return false;
        }
        i++;
    }    
    return true;
}

bool Arena::checkCollisionArenaBounds(GLfloat x1, GLfloat y1, GLfloat radius1)
{
    return (x1 - radius1/2 < -this->width/2 || x1 + radius1/2 > this->width/2 || y1 - radius1 < -this->height/2 || y1 +radius1 > this->height/2);
}
bool Arena::checkCollisionCharacter(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat radius1, GLfloat radius2)
{
    if(((x1 +radius1/2) > (x2 - radius2/2) && ((x1 - radius1/2) < x2 + radius2/2)) && (y1 + radius1/2 + radius1/8 > y2 - radius2 && y1 - radius1 < y2 + radius2 +radius2/8 )) return true;
    return false;    
}

bool Arena::checkCollisionObstacle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat radius, GLfloat height, GLfloat width)
{
    if(((x1 +radius/2) > (x2 - width/2) && ((x1 - radius/2) < x2 + width/2)) && (y1 + radius +radius/8 > y2  && y1 - radius < y2 + height)) return true;
    return false;
}

void Arena::destroy()
{
    enemies.clear();
    obstacles.clear();
    shots.clear();
}

