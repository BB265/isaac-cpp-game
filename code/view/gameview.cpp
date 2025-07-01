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
    for (auto p : *actors) {
        int x = p.getX(), y = p.getY();
        if (p.getType() == EntityType::Player) {
            draw_issac(x, y);
        }
        else if (p.getType() == EntityType::Enemy) {
            draw_enemy(x, y);
        }
        else if (p.getType() == EntityType::Bullet) {
            draw_tears(x, y);
        }
    }
    // draw heart
    int mh = (*max_health), h = (*health),int hh;
    mh = mh / 2;
    hh = h % 2;
    h = h / 2;
    int i = 0;
    for (; i < h; i++) {
        sprites["heart"].setPosition({10.f + i * 30.f, 30.f});
        window.draw(sprites["heart"]);
    }
    for (; i < h + hh; i++) {
        sprites["half_heart"].setPosition({ 10.f + i * 30.f, 30.f });
        window.draw(sprites["half_heart"]);
    }
    for (; i < mh; i++) {
        sprites["empty_heart"].setPosition({ 10.f + i * 30.f, 30.f });
        window.draw(sprites["empty_heart"]);
    }
    window.display();
}
void gamewindow::draw_issac(int x, int y) {
    sprites["issac"].setPosition(sf::Vector2f(x, y));
    window.draw(sprites["issac"]);
}
void gamewindow::draw_enemy(int x, int y) {
    sprites["enemy"].setPosition(sf::Vector2f(x, y));
    window.draw(sprites["enemy"]);
}
void gamewindow::draw_tears(int x, int y) {
    sprites["tear"].setPosition(sf::Vector2f(x, y));
    window.draw(sprites["tear"]);
}
void gamewindow::run() {
    while (window.isOpen())
    {
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
        excommand(CommandType::MoveCommand, std::make_any<std::tuple<Direction>>(dir));
        if(sdir!=Direction::None)excommand(CommandType::ShootCommand, std::make_any<std::tuple<Direction>>(sdir));
        excommand(CommandType::UpdateCommand, std::make_any<>);
    }
}
Direction gamewindow::judgeDirection(int up, int right) {
    int value = 3 * right + up;
    if (value > 8)return Direction::None;
    return static_cast<Direction>(value);
}
void gamewindow::onNotify(GameEvent event) {
    switch (event)
    {
    case GameEvent::GAME_STARTED:
        window.clear();
        draw_and_display();
        break;
    case GameEvent::RENDER_FLUSH:
        window.clear();
        draw_and_display();
        break;
    case GameEvent::PLAYER_DIED:
        break;
    case GameEvent::ENEMY_KILLED:
        break;
    case GameEvent::ITEM_PICKED_UP:
        break;
    case GameEvent::PLAY_SOUND_SHOOT:
        break;
    case GameEvent::PLAY_SOUND_HIT:
        break;
    default:
        break;
    }
}