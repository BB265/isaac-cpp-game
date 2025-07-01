#include"isaacApp.h"
void IsaacApp::initialize() {
	m_game_window.set_actors(m_view_model.getEntities());
	m_game_window.set_command(m_view_model.getCommand());
	m_game_window.set_health(m_view_model.getCurrentHealth());
	m_game_window.set_maxhealth(m_view_model.getMaxHealth());
	m_view_model.addObserver(&m_game_window);

}
void IsaacApp::run() {
	m_view_model.startNewGame();
	m_game_window.run();
}