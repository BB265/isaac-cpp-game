#pragma once
#include <iostream>
#include "../view/gameview.h"
#include "../viewmodel/GameViewModel.h"
#include "common/EventSystem.h"

class IsaacApp : public IObserver {
public :
	IsaacApp() {};
	void initialize();
	void run();
	void onNotify(GameEvent event) override;
private:
	GameViewModel m_view_model;
	gamewindow m_game_window;

};