#pragma once
#include"../view/gameview.h"
#include"../viewmodel/GameViewModel.h"
class IsaacApp {
public :
	IsaacApp() {};
	void initialize();
	void run();
private:
	GameViewModel m_view_model;
	gamewindow m_game_window;

};