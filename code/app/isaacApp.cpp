#include"isaacApp.h"
void IsaacApp::initialize() {
	m_game_window.set_command(m_view_model.getCommand());
	m_view_model.addObserver(&m_game_window);
	m_view_model.addObserver(this);
}

void IsaacApp::run() {
	m_game_window.run();
}

void IsaacApp::onNotify(GameEvent event) {
	if (event == GameEvent::GAME_STARTED) {
		m_game_window.set_actors(m_view_model.getEntities());
		m_game_window.set_health(m_view_model.getCurrentHealth());
		m_game_window.set_maxhealth(m_view_model.getMaxHealth());
	} else if (event == GameEvent::PLAYER_DIED) {
		m_game_window.set_actors(nullptr);
		m_game_window.set_health(nullptr);
		m_game_window.set_maxhealth(nullptr);
	}
}
