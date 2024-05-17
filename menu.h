
#include "game.h"
#include"score.h"
#include"help.h"
#include"fstream"
class Menu{
bool scoreMenu;
bool game;
bool inst;
bool exit;

public:

//add menu attributes here
Menu()
{
 scoreMenu=0;
 game=0;
 inst=0;
 exit=0;
}
void leaderboard(RenderWindow& window){
    fstream file;
    file.open("score.txt",ios::in);
    string names[3];
    //string scores[3];
    int i=0;
    string nm,sc;
    while(!file.eof() && i<3){
        file>>sc;
        file>>nm;
        names[i]=nm;
        //scores[i]=sc;
        i++;
    }
    Text text;
    Font font;
    font.loadFromFile("font/font.ttf");
    text.setFont(font);
    text.setScale(1.2,1.2);

    for(int j=0;j<i;j++){
        text.setString(names[j]);
        text.setPosition(760,195+j*120);
        window.draw(text);
        //window.display();
       // cout<<"Displaying "<<names[j]<<endl;
    }
}
string inputName(RenderWindow& window){
        Font font;
        sf::String input;
        sf::Text text;
        text.setFont(font);
        text.setPosition(210,310);
        text.setScale(1.5,1.5);
        string name;
        Event e;
        Texture in;
        Sprite inSprite;
        font.loadFromFile("font/font.ttf");
        in.loadFromFile("img/name.png");
        inSprite.setTexture(in);
    while(window.isOpen()){
        window.draw(inSprite);
         while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game     
            if (e.type == sf::Event::TextEntered)
            {   
                if (e.text.unicode == '\b') { // handle backspace explicitly
                    name.erase(name.size() - 1, 1);
                } 
                else { // all other keypresses
                    name += static_cast<char>(e.text.unicode);
                }

                //name +=e.text.unicode;
                text.setString(name);
                //name+=static_cast<char>(e.text.unicode);         	    
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter)) 
            return name;
    
        }

    window.draw(text);
    window.display();
    }

}

void display_menu()

{   
    score sc;
    Texture tex;
    Sprite sprite;
    
    tex.loadFromFile("img/menu.png");
    sprite.setTexture(tex);
    RenderWindow window(VideoMode(1180,780),"SPACE SHOOTER");
    while(window.isOpen()){
    
        Event e;
        
        help help;
    
    
    while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
    if (Keyboard::isKeyPressed(Keyboard::Enter)) 
            game=1;
    if (Keyboard::isKeyPressed(Keyboard::S)) //If left key is pressed
            scoreMenu=1;
    if (Keyboard::isKeyPressed(Keyboard::I)) //If left key is pressed
            inst=1;
    
    while(game){
        string name="";
        while(name=="")
        name=inputName(window);
        Game g; 
        if(!g.start_game(window,name))
        game=0;
    }
    while(scoreMenu){
        sc.display(window);
        scoreMenu=0;
    }
    while(inst){
        help.display(window);
        inst=0;
    }


    window.draw(sprite);
    leaderboard(window);
    window.display();
    

    }

}


};
