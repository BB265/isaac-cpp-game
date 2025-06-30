#include <iostream>
#include"view/gameview.h"
#include "viewmodel/GameViewModel.h"
#include<optional>
int main() {

	GameViewModel gameViewModel;

	gamewindow gameview(gameViewModel);

	gameViewModel.startNewGame();
	gameview.run();
    
	return 0;
}