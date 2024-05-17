#include <SFML/Graphics.hpp>

using namespace sf;


class score{
public:
Texture tex;
Sprite sprite;
score(){
    tex.loadFromFile("img/hs.png");
    sprite.setTexture(tex);
}
void displayScores(RenderWindow& window){
    fstream file;
    file.open("score.txt",ios::in);
    string names[5];
    string scores[5];
    int i=0;
    string nm,sc;
    while(!file.eof() && i<5){
        file>>sc;
        file>>nm;
        names[i]=nm;
        scores[i]=sc;
        i++;
    }
    Text text;
    Font font;
    font.loadFromFile("font/font.ttf");
    text.setFont(font);
    text.setScale(1.6,1.6);

    for(int j=0;j<i;j++){
        text.setString(names[j]);
        text.setPosition(200,230+j*110);
        window.draw(text);
        text.setString(scores[j]);
        text.setPosition(700,230+j*110);
        window.draw(text);
    }
}
void display(RenderWindow& window){
while(window.isOpen()){
Event e;
while (window.pollEvent(e))
{  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game  
                              	    
}
if (Keyboard::isKeyPressed(Keyboard::Escape)) 
            return;

window.draw(sprite);
displayScores(window);
window.display();

}
}
};