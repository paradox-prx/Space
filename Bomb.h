#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Bomb{
public:
Texture tex;
Sprite sprite;
float speed=0.7;
int x, y;
bool destroyed;

Bomb(){
    tex.loadFromFile("img/enemy_laser.png");
    sprite.setTexture(tex);
    sprite.setScale(0.6,0.6);
    destroyed=0;
    
}

void update(){
    if(!destroyed)
    sprite.move(0,speed);
    else
    sprite.setPosition(-10,-10);
}







};