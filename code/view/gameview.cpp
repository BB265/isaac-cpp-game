#include"gameview.h"
gamewindow::gamewindow(GameViewModel& vm) :m_viewModel(vm),isaac_sprite(normal_texture),enemy_sprite(normal_texture), tears_sprite(normal_texture), background_sprite(normal_texture), heart_sprite(normal_texture) {
    window = sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Isaac Game");
    window.setFramerateLimit(60);
    background_sprite = createSprite("../code/assets/room.png", background_Texture);
    // load texture and sprite
    
    isaac_sprite = createSprite("../code/assets/isaac.png", character_Texture);
    isaac_sprite.setPosition(sf::Vector2f( 400, 300 )); // default position

    // load heart
    
    heart_sprite = createSprite("../code/assets/heart.png", heart_Texture);
    heart_sprite.setScale(sf::Vector2f(3.f, 3.f )); // set heart scale

    
    enemy_sprite= createSprite("../code/assets/Champion_Red.png", enemy_Texture);

    
    tears_sprite= createSprite("../code/assets/tear.png", tears_Texture);
}
void gamewindow::draw_and_display() {
    window.draw(background_sprite);
    const Player& player = m_viewModel.getPlayer();
    set_isaac_position(player.getX(), player.getY());
    window.draw(isaac_sprite);

    // draw heart
    for (int i = 0; i <player.getHealth(); ++i) {
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
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                    //W
                    dir = Direction::Up;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                    //S
                    dir = Direction::Down;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                    //A
                    dir = Direction::Left;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                    //D
                    dir = Direction::Right;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
                    //shoot up
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                    //shoot down
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
                    //shoot left
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                    //shoot right
                }
                m_viewModel.moveCommand(dir);
            }
        }
        draw_and_display();
    }
}
