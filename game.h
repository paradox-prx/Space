
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include<fstream>
using namespace std;
#include "player.h"
#include "enemy.h"
#include"Addon.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
Sprite background; //Game background sprite
Texture bg_texture;
Sprite side;
Texture side_tex;
Player* p; //player 
enemy* en;
Invader* invader;
Addon* addon;
Fire fire;
PowerUp power;
Live live;
Danger danger;
bool paused;
Alpha alpha;
Beta beta;
Gamma gamma;
bool collAddon;
Dragon dragon;
Monster monster;
int level;
bool shoot;
float shootTimer;
float shootTimer2,shootTimer3;
bool add;
Font font;
float firetimer;
float leveltimer;
bool exit=0;
// add other game attributes


Game()
{
p=new Player("img/player_ship.png");
bg_texture.loadFromFile("img/background3.jpg");
background.setTexture(bg_texture);
side_tex.loadFromFile("img/side.jpg");
side.setTexture(side_tex);
side.setPosition(780,0);
shootTimer=0;
shootTimer2=0;
shootTimer3=0;
shoot=false;
level=1;
invader=&alpha;
en=nullptr;
paused=0;
int level;
collAddon=0;
font.loadFromFile("font/font.ttf");
firetimer=0;
leveltimer=0;
}

bool gameOver(bool end=0){
    if(p->lives<=0){
        return 1;
    }
    if(level>6){
        return 1;
    }
    
    return end;
}

void setScore(int num,string nm){

fstream file;
string name,score;
file.open("score.txt",ios::app);
file<<num<<endl;
file<<nm<<endl;
file.close();
file.open("score.txt",ios::in);
file>>name;
int count=0;
while(!file.eof()){
    file>>name;
    count++;
}
count/=2;

string* names=new string[count];
string* scores=new string[count];
file.close();
file.open("score.txt",ios::in);
for(int i=0;i<count;i++){
    file>>name;
    scores[i]=name;
    file>>name;
    names[i]=name;
}

file.close();

for(int i=0;i<count;i++){
    bool change=0;
    for(int j=0;j<count-i-1;j++){
        int num1=stoi(scores[j]);
        int num2=stoi(scores[j+1]);
        if(num1<num2){
            string temp1=scores[j];
            string temp2=names[j];

            scores[j]=scores[j+1];
            names[j]=names[j+1];

            scores[j+1]=temp1;
            names[j+1]=temp2;
            change=1;
        }
    }
}

file.open("score.txt",ios::out);
for(int i=0;i<count;i++){
    file<<scores[i]<<endl;
    file<<names[i]<<endl;
}
file.close();

}

void collision(){
    FloatRect player=p->sprite.getGlobalBounds();
    for(int i=0;i<p->currentBullet;i++){
        for(int j=0;j<invader->num;j++){
            if(!invader->destroyed[i]){
        if(p->bullet[i].sprite.getPosition().x>=invader->xPos[j] && !invader->destroyed[j]&& p->bullet[i].sprite.getPosition().x<=invader->xPos[j]+invader->width && p->bullet[i].sprite.getPosition().y>=invader->yPos[j] && p->bullet[i].sprite.getPosition().y<=invader->yPos[j]+invader->height ){
            invader->destroyed[j]=1;
            //cout<<j<<endl;
            if(p->bullet[i].type!="fire")
            p->bullet[i].destroyed=1;
            if(invader==&alpha){
                p->score+=10*level;
            }
            else if(invader==&beta){
                p->score+=20*level;
            }
            else if(invader==&gamma){
                p->score+=30*level;
            }
            
            
        }
        }
        }
    }
    for(int i=0;i<invader->BombSize;i++){
        if(invader->bombs[i].sprite.getPosition().x>=p->sprite.getPosition().x &&
         invader->bombs[i].sprite.getPosition().x<=p->sprite.getPosition().x+(103*0.75) && 
         invader->bombs[i].sprite.getPosition().y>=p->sprite.getPosition().y && 
         invader->bombs[i].sprite.getPosition().y<=p->sprite.getPosition().y+(107*0.75) )
         {
            invader->bombs[i].destroyed=1;
            p->lives--;
        }
        
    }

    for(int i=0;i<invader->num;i++){
        bool ouch=0;
        if(!invader->destroyed[i]){
        if(player.left>= invader->xPos[i] && player.left<= invader->xPos[i]+invader->width){
            if(player.top>=invader->yPos[i] && player.top<=invader->yPos[i]+invader->height){
                ouch=1;
            }
            if(player.top+player.height>=invader->yPos[i] && player.top+player.height<=invader->yPos[i]+invader->height){
                ouch=1;
            }

        }
        if(player.left+player.width>= invader->xPos[i] && player.left+player.width<= invader->xPos[i]+invader->width){
            if(player.top>=invader->yPos[i] && player.top<=invader->yPos[i]+invader->height){
                ouch=1;
            }
            if(player.top+player.height>=invader->yPos[i] && player.top+player.height<=invader->yPos[i]+invader->height){
                ouch=1;
            }

        }
        if(ouch){
            p->lives--;
            invader->destroyed[i]=1;
            ouch=0;
        }
        
        }
    }
    FloatRect pow=addon->sprite.getGlobalBounds();
    
    if(pow.left>=player.left && pow.left<=player.left + player.width && pow.top+pow.height>=player.top && pow.top<=player.top+player.height)
    collAddon=1;
    

    



}

bool levelUp(){
    bool up=1;
    for(int i=0;i<invader->num;i++){
        if(!invader->destroyed[i])
        up=0;
    }
    return up;
}

bool start_game(RenderWindow& window,string name)
{   Texture life;
    Sprite lifeSprite;
    
    invader=&alpha;
    invader->initialize(level);
    srand(time(0));
    //RenderWindow window(VideoMode(1180, 780), title);
    Clock clock,levelClock;
    float timer=0;
    int timeInt=0;
    addon=&fire;
    //addon->Spawn();
    while (window.isOpen())
    {   
        
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time;  
        timeInt=timer;

        //cout<<time<<endl; 
 	Event e;
    if(levelUp()){
        delete[] invader->xPos;
        delete[] invader->yPos;
        delete[] invader->destroyed;
        for(int i=0;i<p->currentBullet;i++){
            p->bullet->destroyed=1;
        }
        
        time=levelClock.getElapsedTime().asSeconds();
        while(1){
            
            Texture levTex;
            Sprite levSp;
            Texture black;
            Sprite bl;
            black.loadFromFile("img/black.jpg");
            bl.setTexture(black);
            bl.setColor(Color(140,27,152,7));
            window.draw(bl);
            levTex.loadFromFile("img/level.png");
            levSp.setTexture(levTex);
            levSp.setPosition(267,212);
            window.draw(levSp);

            Texture rocket_filled;
            Texture rocket_empty;
            Sprite rock;
            rocket_filled.loadFromFile("img/rocket.png");
            rocket_empty.loadFromFile("img/rocket_empty.png");
            rock.setTexture(rocket_empty);
            for(int i=0;i<3;i++){
                rock.setPosition(465+(i*100),320);
                window.draw(rock);
            }
            rock.setTexture(rocket_filled);
            for(int i=0;i<p->lives;i++){
                if(i>=3)
                break;
                rock.setPosition(465+(i*100),320);
                window.draw(rock);
            }
            Text score;
            score.setFont(font);
            score.setString(to_string(p->score));
            score.setPosition(323+295,212+155);
            Text Timer;
            Timer.setFont(font);
            
            int min=(int)time/60;
            int sec=(int)time%60;
            Timer.setString(to_string(min)+" : "+to_string(sec));
            Timer.setPosition(323+267,440-15);
            window.draw(score);
            window.draw(Timer);            
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::X)) //If left key is pressed
            break;

        }
        levelClock.restart();
        level++;
        p->reset();
        if(level==2){
            invader=&beta;
             invader->initialize(level);
             bg_texture.loadFromFile("img/bg.jpg");
            background.setTexture(bg_texture);
        }
        if(level==3){
            invader=&gamma;
             invader->initialize(level);
        }
        if(level==4){
            invader=&alpha;
             invader->initialize(level);
        }
        if(level==5){
            invader=&beta;
             invader->initialize(level);
        }
        if(level>=6){
            gameOver(1);
        }
        
    }

        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
    
    p->tex.loadFromFile("img/player_ship.png");
    p->sprite.setTexture(p->tex);
    p->sprite.setScale(0.75,0.75);
    p->tilt=0;



    while(paused){
        Texture pause;
        Sprite ps;
        Texture black;
        Sprite bl;
        black.loadFromFile("img/black.jpg");
        bl.setTexture(black);
        bl.setColor(Color(87,28,87,7));
        window.draw(bl);
        pause.loadFromFile("img/pause.png");
        ps.setTexture(pause);
        ps.setPosition(177,117);
        window.draw(ps);
        window.display();
        while (window.pollEvent(e)){
            if (e.type == Event::Closed)   {                //If cross/close is clicked/pressed
                window.close(); 
            }
            if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::R)
                {
                    paused=0;
                }
                if (e.key.code == sf::Keyboard::Enter)
                {   
                    setScore(p->score,name);
                    return 1;
                }

                if (e.key.code == sf::Keyboard::E)
                {   setScore(p->score,name);
                     window.clear();
                    return 0;
                }
            }
        } 
        
    }
    if(gameOver())
    {
        setScore(p->score,name);
    }
    while(gameOver()){
        Texture over;
        Sprite ov;
        Texture black;
        Sprite bl;
        Text score;
        score.setFont(font);
        score.setString(to_string(p->score));
        score.setPosition(618,320);
        Text levels;
        levels.setFont(font);
        levels.setString(to_string(level));
        levels.setPosition(618,380);


        black.loadFromFile("img/black.jpg");
        bl.setTexture(black);
        bl.setColor(Color(112,65,229,7));
        window.draw(bl);
        over.loadFromFile("img/over.png");
        ov.setTexture(over);
        ov.setPosition(177,117);
        window.draw(ov);
        window.draw(levels);
        window.draw(score);
        window.display();
        while (window.pollEvent(e)){
            if (e.type == Event::Closed)   {                //If cross/close is clicked/pressed
                window.close(); 
            }
            if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::Enter)
                {
                    return 1;
                }

                if (e.key.code == sf::Keyboard::E)
                {   window.clear();
                    return 0;
                }
            }
        } 

    }



    if (Keyboard::isKeyPressed(Keyboard::Escape)) //If left key is pressed
            paused=1;
	if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
            p->move("l");    // Player will move to left
	if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            p->move("r");  //player will move to right
	if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
            p->move("u");    //playet will move upwards
	if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            p->move("d");  //player will move downwards
    if(Keyboard::isKeyPressed(Keyboard::Right)&& Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Left)&& Keyboard::isKeyPressed(Keyboard::Down)){
        p->tex.loadFromFile("img/player1.png");
        p->sprite.setTexture(p->tex);
        p->sprite.setScale(1.04,1.04);
        p->tilt=1;
    }
    if(Keyboard::isKeyPressed(Keyboard::Left)&& Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Right)&& Keyboard::isKeyPressed(Keyboard::Down)){
        p->tex.loadFromFile("img/player2.png");
        p->sprite.setTexture(p->tex);
        p->sprite.setScale(1.04,1.04);
        p->tilt=1;
    }

    /*if(Keyboard::isKeyPressed(Keyboard::Right)&& Keyboard::isKeyPressed(Keyboard::Down)){
        p->tex.loadFromFile("img/player3.png");
        p->sprite.setTexture(p->tex);
        p->sprite.setScale(1.04,1.04);
    }
    if(Keyboard::isKeyPressed(Keyboard::Left)&& Keyboard::isKeyPressed(Keyboard::Down)){
        p->tex.loadFromFile("img/player4.png");
        p->sprite.setTexture(p->tex);
        p->sprite.setScale(1.04,1.04);

    }*/
    if(p->Fire){
        for(int i=0;i<p->bulletSize;i++){
        p->bullet[i].sprite.setTexture(p->bullet[i].fireTex);
        p->bullet[i].type="fire";
        }
        firetimer=timer;
        p->Fire=0;
    }

    if(timer-firetimer>=5 && p->bullet[5].type=="fire"){
        for(int i=0;i<p->bulletSize;i++){
        p->bullet[i].sprite.setTexture(p->bullet[i].tex);
        p->bullet[i].type="bullet";
        }
        
    }
    if(timer-shootTimer3>=5 && !add){
        add=1;
        shootTimer3=timer;
    }
    if(add){
        int num=rand()%4;
        if(num==0){
        addon=&fire;
        }
        if(num==1){
        addon=&danger;
        }
        if(num==2){
        addon=&power;
        }
        if(num==3){
        addon=&live;
        }
        addon->Spawn();
        add=0;
    }
    if (timer - shootTimer >= 0.6 && !(shoot) )
    {
        shoot = true;
        shootTimer = 0.0;
    }
    if (shoot && !p->tilt)
    {
         p->fire();
         shootTimer = timer;
        shoot = 0;
    }

    if (timer - shootTimer2 >= invader->interval && !(invader->shootTime) )
    {
        invader->shootTime = true;
        shootTimer2 = 0;
    }
    if (invader->shootTime )
    {
        int num=rand()%invader->num;
        if(!invader->destroyed[num])
        invader->shoot(num);
        shootTimer2 = timer;
        invader->shootTime = 0;
    }

    
    if(p->lives==3){
            life.loadFromFile("img/life3.png");
        }
        else if(p->lives==2){
            life.loadFromFile("img/life2.png");

        }
        else if(p->lives==1){
            life.loadFromFile("img/life1.png");
        }
        lifeSprite.setTexture(life);

        lifeSprite.setPosition(p->sprite.getPosition().x-5,p->sprite.getPosition().y+70);
        lifeSprite.setScale(0.8,0.8);
	////////////////////////////////////////////////
	/////  Call your functions here            ////
	//////////////////////////////////////////////
    collision();
    if(collAddon){
        if(addon==&danger){
            p->lives--;
        }
        if(addon==&live){
            p->lives++;
        }
        if(addon==&power){
            p->score+=10;
        }
        if(addon==&fire){
            p->Fire=1;
        }

        addon->Remove();
        collAddon=0;
    }
    for(int i=0;i<p->currentBullet;i++){
	    p->bullet[i].update();
    }
    
    for(int i=0;i<invader->currentBomb;i++){
    
	invader->bombs[i].update();
    }
    addon->update();
    
    
   
    p->wrapAround();
    //invader->display();
    
	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background
    
	
    for(int i=0;i<p->currentBullet;i++){
        if(!p->bullet[i].destroyed)
            window.draw(p->bullet[i].sprite);
    }
    window.draw(p->sprite);   // setting player on screen
    window.draw(lifeSprite);
     
    for(int j=0;j<invader->num;j++){
    for(int i=0;i<invader->currentBomb;i++){
    if(!invader->bombs[i].destroyed)
	window.draw(invader->bombs[i].sprite);
    }
    }

    
    for(int i=0;i<invader->num;i++){
    if(!(invader->destroyed[i])){
    invader->sprite.setPosition(invader->xPos[i],invader->yPos[i]);
    //invader->sprite.setScale(0.6,.6);
    window.draw(invader->sprite);
    }
    }
window.draw(side);
    
    

    Text text;
    text.setFont(font);
    text.setString("SPACE SHOOTER");
    text.setPosition(800,20);
    
    Text lives;
    lives.setFont(font);
    lives.setString("Lives: "+to_string(p->lives));
    lives.setPosition(800,150);
    Text score;
    score.setFont(font);
    score.setString("Score: "+to_string(p->score));
    score.setPosition(800,100);
    Text levels;
    levels.setFont(font);
    levels.setString("Level: "+to_string(level));
    levels.setPosition(800,200);
    Text status;
    status.setFont(font);
    status.setString("PLAYER:\n"+name);
    status.setPosition(800,250);
    
    
    window.draw(text);
    window.draw(score);
    window.draw(lives);
    window.draw(levels);
    window.draw(status);
    
    window.draw(addon->sprite);
	window.display();  //Displying all the sprites
    }


}


};


