#include <SFML/Graphics.hpp>
#include<string.h>
#include"bullet.h"
using namespace sf;
class Player{
public:
Texture tex;
Sprite sprite;
float speed=1.2;
int x,y,currentBullet,bulletSize;
Bullet* bullet;
bool tilt;
int lives;
int score;
bool Fire;
bool power;
Player(std::string png_path)
{
tex.loadFromFile(png_path);
sprite.setTexture(tex);
x=340;y=700;
sprite.setPosition(x,y);
sprite.setScale(0.75,0.75);
currentBullet=0;
bulletSize=100;
bullet=new Bullet[bulletSize];
tilt=0;
lives=3;
Fire=0;
power=0;
score=0;
}
void fire()
{
if(currentBullet>bulletSize){
	currentBullet=0;
}


if(tilt){
	
	bullet[currentBullet].tex.loadFromFile("img/PNG/Lasers/laserBlue01R.png");
	bullet[currentBullet].sprite.setTexture(tex);
}

int xpos=sprite.getPosition().x+36,ypos=sprite.getPosition().y;
bullet[currentBullet].sprite.setPosition(xpos,ypos);


currentBullet++;


}

void reset(){
	sprite.setPosition(340,700);
	for(int i=0;i<currentBullet;i++){
		bullet[i].destroyed=1;
	}
}
void move(std::string s){
float delta_x=0,delta_y=0;
if(s=="l")
	//move the player left
	delta_x=-1;
else if(s=="r")
	delta_x=1;
	//move the player right
if(s=="u")
	delta_y=-1;
else if(s=="d")
	delta_y=1;

delta_x*=speed;
delta_y*=speed;

sprite.move(delta_x, delta_y);

}

void wrapAround(){
if(sprite.getPosition().x<-80){
sprite.setPosition(780,sprite.getPosition().y);
}
else if(sprite.getPosition().x>780){
sprite.setPosition(-80,sprite.getPosition().y);
}
else if(sprite.getPosition().y<-80)
sprite.setPosition(sprite.getPosition().x,780);
else if(sprite.getPosition().y>780)
sprite.setPosition(sprite.getPosition().x,-80);
}


};
