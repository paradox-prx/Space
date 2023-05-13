#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Bullet{
public:
Texture tex;
Sprite sprite;
float speed=-0.9;
int x, y;
bool destroyed;

Bullet(){
    tex.loadFromFile("img/PNG/Lasers/laserBlue01.png");
    sprite.setTexture(tex);
    destroyed=0;
}

void update(){
    sprite.move(0,speed);
}







};