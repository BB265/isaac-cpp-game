#ifndef __GAMEVIEW_H_
#define __GAMEVIEW_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class gamewindow {
private:
	int heart_count;
	sf::Texture normal_texture;
	sf::Texture background_Texture;
	sf::Texture character_Texture;
	sf::Texture heart_Texture;
	sf::Texture enemy_Texture;
	sf::Texture tears_Texture;
public:
	sf::RenderWindow window;
	sf::Sprite isaac_sprite;
	sf::Sprite enemy_sprite;
	sf::Sprite tears_sprite;
	sf::Sprite background_sprite;
	sf::Sprite heart_sprite;
	gamewindow();
	void draw_and_display();
	sf::Sprite createSprite(const std::string& filepath, sf::Texture& texture);
	void setposition(sf::Sprite& sprite, sf::Vector2f position);
	void set_isaac_position(int x, int y);
	void set_heartcount(int count);
};
#endif