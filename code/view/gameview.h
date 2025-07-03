#ifndef __GAMEVIEW_H_
#define __GAMEVIEW_H_
#include <SFML/Graphics.hpp>
#include"common/MetaData.h"
#include"common/Direction.h"
#include"common/Commands.h"
#include"common/EventSystem.h"
#include"common/entity.h"
#include"AssetManager.h"
#include<memory>
enum class GameState
{
	MAIN_WINDOW,
	GAMING,
	END_GAME
};
class gamewindow:public IObserver {
private:
	const int* health;
	const int* max_health;
	std::map<std::string, sf::Sprite>sprites;
	const std::vector<std::shared_ptr<Entity>>* actors;
	EXCommand excommand;
	GameState gamestate;
public:
	sf::RenderWindow window;
	gamewindow();
	~gamewindow(){}
	void run();
	void draw_and_display();
	void draw_issac(float x, float y);
	void draw_enemy(float x, float y);
	void draw_tears(float x, float y);
	void draw_enemyhit(float x, float y);
	void set_actors(const std::vector<std::shared_ptr<Entity>>* _actors) {
		actors = _actors;
	}
	void set_command(EXCommand func) {
		excommand = func;
	}
	void set_health(const int* _health) {
		health = _health;
	}
	void set_maxhealth(const int* _maxhealth) {
		max_health = _maxhealth;
	}
	void onNotify(GameEvent event) override;
	Direction judgeDirection(int up, int right);
};
#endif