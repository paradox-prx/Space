#include <SFML/Graphics.hpp>
#include<string.h>
#include"Bomb.h"
#include<cmath>
using namespace sf;
using namespace std;
class enemy{
public:
Texture tex;
Sprite sprite;
int* xPos;
int* yPos;

int num;
int BombSize;
Bomb* bombs;
int currentBomb;
enemy(){
    num=1;
    xPos=new int[num];
    yPos=new int[num];
    currentBomb=0;
    BombSize=15;
    bombs=new Bomb[BombSize];
}

enemy(int n){
    num=n;
    xPos=new int[num];
    yPos=new int[num];
    currentBomb=0;
    BombSize=20;
    bombs=new Bomb[BombSize];
}

virtual void display()=0;
virtual void shoot(int)=0;
virtual void initialize(int level)=0;
};


class Invader:public enemy{
public:
float width;
float height;
float interval;
bool shootTime;
bool* destroyed;
Texture bomb;
Sprite spBomb;
string type;
int Score;
Invader(){
    bomb.loadFromFile("img/enemy_laser.png");
    spBomb.setTexture(bomb);
}
void display(){
    for(int i=0;i<num;i++){
        if(!(destroyed[i])){
    sprite.setPosition(xPos[i],yPos[i]);
    sprite.setScale(0.6,.6);
        }
    }
}
void shoot(int num){
    if(currentBomb>=BombSize-3){
        currentBomb=0;
        for(int i=0;i<BombSize;i++){
            bombs[i].destroyed=0;
        }
    }
    
    int x=xPos[num]+30,y=yPos[num];
    bombs[currentBomb].sprite.setPosition(x,y);
    currentBomb++;
    
    
}

virtual void initialize(int level)=0;


};
class Alpha:public Invader{
public:
Alpha(){
    tex.loadFromFile("img/enemy_1.png");
    sprite.setTexture(tex);
    sprite.setScale(0.6,.6);
    interval=3;
    Score=10;
    shootTime=0;
    type="Alpha";
    width=124*0.6;
    height=63.6;

}


void initialize(int level){
if(level ==1){
    
    
    num=12;
    xPos=new int[12];
    yPos=new int[12];
    destroyed=new bool[num];
        for(int j=0;j<5;j++){
            xPos[j]=(j+1)*100+30;
            yPos[j]=100;
        }

        for(int j=5;j<10;j++){
            xPos[j]=(j-4)*100+30;
            yPos[j]=300;
        }
        xPos[10]=130;
        yPos[10]=200;
        xPos[11]=530;
        yPos[11]=200;
}
else if(level==4){
    num=13;
    int centX=340,centY=300;
    xPos=new int[num];
    yPos=new int[num];
    destroyed=new bool[num];
    xPos[0] = centX - 200;
    yPos[0] = centY;
    xPos[1] = centX + 200;
    yPos[1] = centY;
    xPos[2] = centX;
    yPos[2] = centY - 200;
    xPos[3] = centX;
    yPos[3] = centY + 200;
    xPos[4] = centX - 100;
    yPos[4] = centY - 100;
    xPos[5] = centX - 100;
    yPos[5] = centY + 100;
    xPos[6] = centX + 100;
    yPos[6] = centY - 100;
    xPos[7] = centX + 100;
    yPos[7] = centY + 100;
    xPos[8] = centX - 150;
    yPos[8] = centY - 150;
    xPos[9] = centX - 150;
    yPos[9] = centY + 150;
    xPos[10] = centX + 150;
    yPos[10] = centY - 150;
    xPos[11] = centX + 150;
    yPos[11] = centY + 150;
    xPos[12] = centX;
    yPos[12] = centY;

}

}

};

class Beta:public Invader{
public:
Beta(){
    tex.loadFromFile("img/enemy_2.png");
    sprite.setTexture(tex);
    sprite.setScale(0.6,.6);
    interval=2;
    Score=20;
    shootTime=0;
    type="Beta";
    width=120*0.6;
    height=154*0.6;
}


void initialize(int level){
if(level ==2){
    num=12;
    xPos=new int[num];
    yPos=new int[num];
    int radius=200;
    destroyed=new bool[num];
    int centX=350,centY=270;

    for (int i = 0; i < num; i++) {
    float angle = 2 * M_PI * i / num;
    xPos[i] = centX + radius * cos(angle);
    yPos[i] = centY + radius * sin(angle);
}
    
}
else if(level==5){
    num=14;
    xPos=new int[num];
    yPos=new int[num];
    destroyed=new bool[num];
    int centX = 340;
    int centY = 250;
    float angle = 0;
    float increment = (2 * M_PI) / (num - 1);
    float radius = 200;

    for (int i = 0; i < num - 2; i++) {
        xPos[i] = centX + radius * cos(angle);
        yPos[i] = centY - radius * sin(angle);
        angle += increment;
    }

    float semiCircleRadius = 100;
    xPos[num - 2] = centX - semiCircleRadius;
    yPos[num - 2] = centY - semiCircleRadius;
    xPos[num - 1] = centX + semiCircleRadius;
    yPos[num - 1] = centY - semiCircleRadius;
}

}
};


class Gamma:public Invader{
public:
Gamma(){
    
    tex.loadFromFile("img/enemy_3.png");
    sprite.setTexture(tex);
    sprite.setScale(0.6,.6);
    interval=0.9;
    Score=30;
    shootTime=0;
    type="Gamma";
    width=173*0.6;
    height=132*0.6;
}



void initialize(int level){
if(level ==3){
    num=9;
    xPos=new int[num];
    yPos=new int[num];
    destroyed=new bool[num];

    for (int i = 0; i <5; i++) {
        xPos[i] = (i)*100 +100;
        yPos[i] = (i)*100 +20;
    }
    for (int i = 5; i <9; i++) {
        xPos[i] = 500-((i-5)*100);
        yPos[i] = (i-5)*100 +20;
        if(i>=7){
            xPos[i] = 500-((i-5+1)*100);
            yPos[i] = (i-5+1)*100 +20;
        }
    }





    
}
    
}

};


class Dragon:public enemy{
public:
void update(){

}
void shoot(int num){

}

void display(){

}

void initialize(int level){

}

};
class Monster:public enemy{
public:
void update(){

}
void shoot(int num)
{

}
void display(){
    
}

void initialize(int level){

}
};