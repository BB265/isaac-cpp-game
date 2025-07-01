#include"gameview.h"
gamewindow::gamewindow() {
    window = sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Isaac Game");
    window.setFramerateLimit(60);
    const std::map < std::string, sf::Texture > textures = AssetManager::get_instance().get_textures();
    for (auto p : textures) {
        sprites[p.first] =sf::Sprite(p.second);
    }
    sprites["isaac"].setPosition(sf::Vector2f(400, 300)); // default position
    sprites["isaac"].setScale(sf::Vector2f(1.5, 1.5));
    sprites["heart"].setScale(sf::Vector2f(3.f, 3.f ));// set heart scale
    sprites["half_heart"].setScale(sf::Vector2f(3.f, 3.f));
    sprites["empty_heart"].setScale(sf::Vector2f(3.f, 3.f));
    sprites["tear"].setScale(sf::Vector2f(0.4f, 0.4f));
}
void gamewindow::draw_and_display() {
    window.draw(sprites["background"]);
    set_isaac_position(player.getX(), player.getY());
    window.draw(isaac_sprite);

    // draw heart
    for (int i = 0; i <player.getHealth(); ++i) {
        heart_sprite.setPosition({ 10.f + i * 30.f, 30.f }); 
        window.draw(heart_sprite);
    }
    //draw enemys
    const auto& enemies = m_viewModel.getEnemies();
    for (auto p : enemies) {
        draw_enymy(p.getX(), p.getY());
    }
    const auto& tears = m_viewModel.getBullets();
    for (auto p : tears) {
        draw_tears(p.getX(), p.getY());
    }
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
void gamewindow::set_isaac_position(int x, int y) {
    setposition(isaac_sprite, sf::Vector2f(x, y));
}
void gamewindow::draw_enymy(int x, int y) {
    setposition(enemy_sprite, sf::Vector2f(x, y));
    window.draw(enemy_sprite);
}
void gamewindow::draw_tears(int x, int y) {
    setposition(tears_sprite, sf::Vector2f(x, y));
    window.draw(tears_sprite);
}
void gamewindow::run() {
    while (window.isOpen())
    {
        window.clear();
        Direction dir = Direction::None;
        Direction sdir = Direction::None;
        int dir_up=1, dir_right=1;
        int shoot_up = 1, shoot_right = 1;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            dir_up += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            dir_up -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            dir_right -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            dir_right += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            shoot_up += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            shoot_up -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            shoot_right -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            shoot_right += 1;
        }
        dir = judgeDirection(dir_up, dir_right);
        sdir = judgeDirection(shoot_up, shoot_right);
        m_viewModel.moveCommand(dir);
        if(sdir!=Direction::None)m_viewModel.shootCommand(sdir);
        m_viewModel.update();
        draw_and_display();
    }
}
Direction gamewindow::judgeDirection(int up, int right) {
    int value = 3 * right + up;
    if (value > 8)return Direction::None;
    return static_cast<Direction>(value);
}