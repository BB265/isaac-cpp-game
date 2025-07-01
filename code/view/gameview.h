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
class gamewindow:public IObserver {
private:
	const int* health;
	const int* max_health;
	std::map<std::string, sf::Sprite>sprites;
	std::vector<std::shared_ptr<Entity>> actors;
	EXCommand excommand;
public:
	sf::RenderWindow window;
	gamewindow();
	~gamewindow(){}
	void run();
	void draw_and_display();
	void draw_issac(int x, int y);
	void draw_enemy(int x, int y);
	void draw_tears(int x, int y);
	void set_actors(const std::vector<std::shared_ptr<Entity>>& _actors) {
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