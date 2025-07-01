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
		sf::Texture texture;
		texture.loadFromFile(path);
	}
private:
	AssetManager(){}
	std::map<std::string,>
};