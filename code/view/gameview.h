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
	std::map<std::string, sf::Sprite>sprites;
public:
	sf::RenderWindow window;
	gamewindow();
	~gamewindow(){}
	void run();
	void draw_and_display();
	Direction judgeDirection(int up, int right);
};
#endif