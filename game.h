
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
#include "player.h"
#include "enemy.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
Sprite background; //Game background sprite
Texture bg_texture;
Player* p; //player 
enemy* en;
Invader* invader;
bool paused;
Alpha alpha;
Beta beta;
Gamma gamma;
Dragon dragon;
Monster monster;
int level;
bool shoot;
float shootTimer;
float shootTimer2,shootTimer3;
// add other game attributes


Game()
{
p=new Player("img/player_ship.png");
bg_texture.loadFromFile("img/background_1.png");
background.setTexture(bg_texture);
background.setScale(2, 1.5);
shootTimer=0;
shootTimer2=0;
shootTimer3=0;
shoot=false;
level=1;
invader=&alpha;
en=nullptr;
paused=0;
int level;
}

void collision(){
    
    for(int i=0;i<p->currentBullet;i++){
        for(int j=0;j<invader->num;j++){
            if(!invader->destroyed[i]){
        if(p->bullet[i].sprite.getPosition().x>=invader->xPos[j] && !invader->destroyed[j]&& p->bullet[i].sprite.getPosition().x<=invader->xPos[j]+invader->width && p->bullet[i].sprite.getPosition().y>=invader->yPos[j] && p->bullet[i].sprite.getPosition().y<=invader->yPos[j]+invader->height ){
            invader->destroyed[j]=1;
            p->bullet[i].destroyed=1;
        }
        }
        }
    }
    for(int i=0;i<invader->BombSize;i++){
        if(invader->bombs[i].sprite.getPosition().x>=p->sprite.getPosition().x && invader->bombs[i].sprite.getPosition().x<=p->sprite.getPosition().x+(103*0.75) && invader->bombs[i].sprite.getPosition().y>=p->sprite.getPosition().y && invader->bombs[i].sprite.getPosition().y<=p->sprite.getPosition().y+(107*0.75) ){
            invader->bombs[i].destroyed=1;
        }
        
    }

    for(int i=0;i<invader->num;i++){
        FloatRect player=p->sprite.getGlobalBounds();
        if(!invader->destroyed[i]){
        if(player.left>= invader->xPos[i] && player.left<= invader->xPos[i]+invader->width){
            if(player.top>=invader->yPos[i] && player.top<=invader->yPos[i]+invader->height){
                cout<<"SHIITTT "<<i<<endl;
            }
            if(player.top+player.height>=invader->yPos[i] && player.top+player.height<=invader->yPos[i]+invader->height){
                cout<<"SHIITTT "<<i<<endl;
            }

        }
        if(player.left+player.width>= invader->xPos[i] && player.left+player.width<= invader->xPos[i]+invader->width){
            if(player.top>=invader->yPos[i] && player.top<=invader->yPos[i]+invader->height){
                cout<<"SHIITTT "<<i<<endl;
            }
            if(player.top+player.height>=invader->yPos[i] && player.top+player.height<=invader->yPos[i]+invader->height){
                cout<<"SHIITTT "<<i<<endl;
            }

        }
        
        }
    }



}

bool levelUp(){
    bool up=1;
    for(int i=0;i<invader->num;i++){
        if(!invader->destroyed[i])
        up=0;
    }
    return up;
}

void start_game()
{
    invader=&alpha;
    invader->initialize(level);
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    Clock clock;
    float timer=0;
    int timeInt=0;
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time;  
        timeInt=timer;

        //cout<<time<<endl; 
 	Event e;
    if(levelUp()){
        level++;
        if(level==2){
            invader=&beta;
             invader->initialize(level);
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
        while (window.pollEvent(e)){
            if (e.type == Event::Closed)   {                //If cross/close is clicked/pressed
                window.close(); 
            }
        } 
        if (Keyboard::isKeyPressed(Keyboard::R)){   //Checks for Esc key Pressed
            paused=0;
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
    if (timer - shootTimer >= 0.6 && !(shoot) )
    {
        shoot = true;
        shootTimer = 0.0;
    }
    if (shoot )
    {
         //p->fire();
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

    


    
    
    
   
        
  
    
    
	////////////////////////////////////////////////
	/////  Call your functions here            ////
	//////////////////////////////////////////////
    for(int i=0;i<p->currentBullet;i++){
        if(!p->bullet[i].destroyed)
	    p->bullet[i].update();
    }
    
    for(int i=0;i<invader->currentBomb;i++){
    if(!invader->bombs[i].destroyed)
	invader->bombs[i].update();
    }
    
    
   
    p->wrapAround();
    //invader->display();
    collision();
	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background
	
    for(int i=0;i<p->currentBullet;i++){
        if(!p->bullet[i].destroyed)
            window.draw(p->bullet[i].sprite);
    }
    window.draw(p->sprite);   // setting player on screen
     
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

    
    

    
    
	window.display();  //Displying all the sprites
    }


}


};


