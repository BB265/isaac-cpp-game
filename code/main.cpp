#include <iostream>
#include"view/gameview.h"
#include<optional>
int main() {
	gamewindow gameview;
	sf::RenderWindow& current_window = gameview.window;
    while (current_window.isOpen())
    {   
        gameview.clear();
        while (const std::optional event = current_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                current_window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::W){
                    //W
                 }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                    //S
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                    //A
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                    //D
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
                    //shoot up
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                    //shoot down
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
                    //shoot left
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                    //shoot right
                }
            }
        }

        gameview.draw_and_display();
    }
	return 0;
}