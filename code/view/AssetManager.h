#pragma once
#include<SFML/Graphics.hpp>
#include<map>
#include<string>
class AssetManager {
public:
	static AssetManager& get_instance() {
		static AssetManager instance;
		return instance;
	}
	void load_texture(const std::string& name, const std::string& path) {
		sf::Texture* texture = new sf::Texture;
		texture->loadFromFile(path);
		m_textures[name] = *texture;
	}
	const std::map < std::string, sf::Texture >& get_textures() {
		return m_textures;
	}
	AssetManager(){
		load_texture("background", "../code/assets/room.png");
		load_texture("isaac", "../code/assets/isaac.png");
		load_texture("half_heart", "../code/assets/half_heart.png");
		load_texture("empty_heart", "../code/assets/empty_heart.png");
		load_texture("heart", "../code/assets/heart.png");
		load_texture("enemy", "../code/assets/Champion_Red.png");
		load_texture("tear", "../code/assets/tear.png");
	}
private:
	std::map < std::string, sf::Texture > m_textures;
};