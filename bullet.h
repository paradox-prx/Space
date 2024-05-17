#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Bullet{
public:
Texture tex;
Sprite sprite;
Texture fireTex;
float speed=-1.2;
int x, y;
bool destroyed;
string type;

Bullet(){
    fireTex.loadFromFile("img/PNG/Effects/fire09.png");
    tex.loadFromFile("img/PNG/Lasers/laserBlue01.png");
    sprite.setTexture(tex);
    destroyed=0;
    type="bullet";
}

void update(){
    if(!destroyed)
    sprite.move(0,speed);
    else
    sprite.setPosition(-10,-10);
}


};