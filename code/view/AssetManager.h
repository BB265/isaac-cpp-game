#pragma once
#include<SFML/Graphics.hpp>
#include<map>
#include<string>
#include<stdexcept>
class AssetManager {
public:
	static AssetManager& get_instance() {
		static AssetManager instance;
		return instance;
	}
	void load_texture(const std::string& name, const std::string& path) {
		sf::Texture* texture = new sf::Texture;
		if (!texture->loadFromFile(path)) {
			throw std::runtime_error("load file fail " + path);
		}
		m_textures[name] = texture;
	}
	const std::map < std::string, sf::Texture* >& get_textures() {
		return m_textures;
	}
	AssetManager(){
		load_texture("room", "../code/assets/room.png");
		load_texture("main_window", "../code/assets/main_window.png");
		load_texture("end_window","../code/assets/end_window.png");
		load_texture("isaac", "../code/assets/isaac.png");
		load_texture("half_heart", "../code/assets/half_heart.png");
		load_texture("empty_heart", "../code/assets/empty_heart.png");
		load_texture("heart", "../code/assets/heart.png");
		load_texture("enemy", "../code/assets/enemy.png");
		load_texture("door", "../code/assets/door.png");
		load_texture("tear", "../code/assets/tear.png");
	}
private:
	std::map < std::string, sf::Texture* > m_textures;
};