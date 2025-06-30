#include <iostream>
#include"view/gameview.h"
#include "viewmodel/GameViewModel.h"
#include<optional>
int main() {

	GameViewModel gameViewModel;

	gamewindow gameview(gameViewModel);

	gameViewModel.startNewGame();

	sf::RenderWindow& current_window = gameview.window;
    while (current_window.isOpen())
    {
        while (const std::optional event = current_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                current_window.close();
            }
        }

        gameview.draw_and_display();
    }
	return 0;
}