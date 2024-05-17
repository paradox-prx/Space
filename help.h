#include <SFML/Graphics.hpp>

using namespace sf;


class help{
public:
Texture tex;
Sprite sprite;
help(){
    tex.loadFromFile("img/help.png");
    sprite.setTexture(tex);
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
window.display();

}
}
};