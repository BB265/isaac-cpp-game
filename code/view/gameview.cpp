#include"gameview.h"
gamewindow::gamewindow() :isaac_sprite(normal_texture),enemy_sprite(normal_texture), tears_sprite(normal_texture), background_sprite(normal_texture), heart_sprite(normal_texture) {
    window = sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Isaac Game");
    background_sprite = createSprite("../code/assets/room.png", background_Texture);

    // load texture and sprite
    
    isaac_sprite = createSprite("../code/assets/isaac.png", character_Texture);
    isaac_sprite.setPosition(sf::Vector2f( 400, 300 )); // default position

    // load heart
    
    heart_sprite = createSprite("../code/assets/heart.png", heart_Texture);
    heart_sprite.setScale(sf::Vector2f(3.f, 3.f )); // set heart scale
    heart_count = 3;

    
    enemy_sprite= createSprite("../code/assets/Champion_Red.png", enemy_Texture);

    
    tears_sprite= createSprite("../code/assets/tear.png", tears_Texture);
}
void gamewindow::draw_and_display() {
    window.clear();
    window.draw(background_sprite);
    window.draw(isaac_sprite);

    // draw heart
    for (int i = 0; i < heart_count; ++i) {
        heart_sprite.setPosition({ 10.f + i * 30.f, 30.f }); 
        window.draw(heart_sprite);
    }
    //undone
    window.display();
}
sf::Sprite gamewindow::createSprite(const std::string& filepath, sf::Texture& texture) {
    if (!texture.loadFromFile(filepath)) {
        throw std::runtime_error("Failed to load texture: " + filepath);
    }
    return sf::Sprite(texture);
}
void gamewindow::setposition(sf::Sprite& sprite, sf::Vector2f position) {
    sprite.setPosition(position);
}
void gamewindow::set_heartcount(int count) {
    heart_count = count;
}
void gamewindow::set_isaac_position(int x, int y) {
    setposition(isaac_sprite, sf::Vector2f(x, y));
}