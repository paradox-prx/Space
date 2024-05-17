#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Addon{
public:
Texture tex;
Sprite sprite;
string type;
float speed;
int x,y;
bool used;
Addon(){
    used=0;
}

void update(){
sprite.move(0,1);
}
void Spawn(){
    x=rand()%650+30;
    y=2;
    sprite.setPosition(x,y);
}
void Remove(){
    sprite.setPosition(-20,700);
}
};


class PowerUp:public Addon{
public:

PowerUp(){
    used=0;
    tex.loadFromFile("img/PNG/Power-ups/powerupBlue_bolt.png");
    sprite.setTexture(tex);
    type="power";
    used=0;
}

};

class Fire:public Addon{
public:
Fire(){
    used=0;
    tex.loadFromFile("img/fire.png");
    sprite.setTexture(tex);
    type="fire";
    used=0;
}

};


class Live:public Addon{
    public:
Live(){
    used=0;
    tex.loadFromFile("img/PNG/Power-ups/pill_blue.png");
    sprite.setTexture(tex);
    type="live";
    used=0;
}

};


class Danger:public Addon{
public:
Danger(){
    used=0;
    tex.loadFromFile("img/PNG/Meteors/meteorGrey_med2.png");
    sprite.setTexture(tex);
    type="danger";
    used=0;
}
};