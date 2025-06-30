#ifndef __GAMEVIEW_H_
#define __GAMEVIEW_H_
#include <SFML/Graphics.hpp>
#include "viewmodel/GameViewModel.h"
#include"common/MetaData.h"
#include"common/Direction.h"
#include"common/Commands.h"
#include"common/EventSystem.h"
class gamewindow {
private:
	GameViewModel& m_viewModel;
	sf::Texture normal_texture;
	sf::Texture background_Texture;
	sf::Texture character_Texture;
	sf::Texture heart_Texture;
	sf::Texture enemy_Texture;
	sf::Texture tears_Texture;
	sf::Sprite isaac_sprite;
	sf::Sprite enemy_sprite;
	sf::Sprite tears_sprite;
	sf::Sprite background_sprite;
	sf::Sprite heart_sprite;
public:
	sf::RenderWindow window;
	gamewindow(GameViewModel &vm);
	~gamewindow(){}
	void run();
	void draw_and_display();
	sf::Sprite createSprite(const std::string& filepath, sf::Texture& texture);
	void setposition(sf::Sprite& sprite, sf::Vector2f position);
	void set_isaac_position(int x, int y);
	void draw_enymy(int x, int y);
	void draw_tears(int x, int y);
	Direction judgeDirection(int up, int right);
};
#endif