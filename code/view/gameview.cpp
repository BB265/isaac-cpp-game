#include"gameview.h"
gamewindow::gamewindow() {
    window = sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Isaac Game");
    window.setFramerateLimit(60);
    const std::map < std::string, sf::Texture* > textures = AssetManager::get_instance().get_textures();
    for (auto &p : textures) {
        if (!p.first.empty()) {
            sprites.emplace(p.first, sf::Sprite((*p.second)));
        }
    }
    sprites.find("isaac")->second.setPosition(sf::Vector2f(400, 300)); // default position
    sprites.find("isaac")->second.setScale(sf::Vector2f(1.5, 1.5));
    sprites.find("enemy")->second.setScale(sf::Vector2f(1.5, 1.5));
    sprites.find("heart")->second.setScale(sf::Vector2f(3.f, 3.f ));// set heart scale
    sprites.find("half_heart")->second.setScale(sf::Vector2f(3.f, 3.f));
    sprites.find("empty_heart")->second.setScale(sf::Vector2f(3.f, 3.f));
    sprites.find("tear")->second.setScale(sf::Vector2f(0.4f, 0.4f));
    gamestate = GameState::MAIN_WINDOW;
    sprites.emplace("background", sprites.find("main_window")->second);
    health = nullptr;
    max_health = nullptr;
    actors = nullptr;
}
void gamewindow::draw_and_display() {
    window.draw(sprites.find("background")->second);
    if (actors != nullptr) {
        const std::vector<std::shared_ptr<Entity>> _actors = *actors;
        for (auto p : _actors) {
            float x = p->getX(), y = p->getY();
            if (p->getType() == EntityType::Player) {
                draw_issac(x, y);
            }
            else if (p->getType() == EntityType::Enemy) {
                draw_enemy(x, y);
            }
            else if (p->getType() == EntityType::Bullet) {
                draw_tears(x, y);
            }
        }
    }
    
    // draw heart
    if (health != nullptr) {
        int mh = (*max_health), h = (*health);
        mh = mh / 2;
        int hh = h % 2;
        h = h / 2;
        int i = 0;
        for (; i < h; i++) {
            sprites.find("heart")->second.setPosition({ 10.f + i * 30.f, 30.f });
            window.draw(sprites.find("heart")->second);
        }
        for (; i < h + hh; i++) {
            sprites.find("half_heart")->second.setPosition({ 10.f + i * 30.f, 30.f });
            window.draw(sprites.find("half_heart")->second);
        }
        for (; i < mh; i++) {
            sprites.find("empty_heart")->second.setPosition({ 10.f + i * 30.f, 30.f });
            window.draw(sprites.find("empty_heart")->second);
        }
    }
    window.display();
}
void gamewindow::draw_issac(float x, float y) {
    sprites.find("isaac")->second.setPosition(sf::Vector2f(x, y));
    window.draw(sprites.find("isaac")->second);
}
void gamewindow::draw_enemy(float x, float y) {
    sprites.find("enemy")->second.setPosition(sf::Vector2f(x, y));
    window.draw(sprites.find("enemy")->second);
}
void gamewindow::draw_tears(float x, float y) {
    sprites.find("tear")->second.setPosition(sf::Vector2f(x, y));
    window.draw(sprites.find("tear")->second);
}
void gamewindow::run() {
    while (window.isOpen())
    {
        if (gamestate == GameState::MAIN_WINDOW) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                excommand(CommandType::StartGameCommand, std::make_any<std::tuple<>>);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }
            window.clear();
            draw_and_display();
        }
        else if (gamestate == GameState::GAMING) {
            Direction dir = Direction::None;
            Direction sdir = Direction::None;
            int dir_up = 1, dir_right = 1;
            int shoot_up = 1, shoot_right = 1;
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
            if (sdir != Direction::None)excommand(CommandType::ShootCommand, std::make_any<std::tuple<Direction>>(sdir));
            excommand(CommandType::UpdateCommand, std::make_any<std::tuple<>>);
        }
        else if (gamestate == GameState::END_GAME) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                excommand(CommandType::StartGameCommand, std::make_any<std::tuple<>>);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                excommand(CommandType::ExitGameCommand, std::make_any<std::tuple<>>);
            }
            window.clear();
            draw_and_display();
        }
        
    }
}
Direction gamewindow::judgeDirection(int up, int right) {
    int value = 3 * right + up;
    if (value > 8)return Direction::None;
    return static_cast<Direction>(value);
}
void gamewindow::onNotify(GameEvent event) {
    const std::map < std::string, sf::Texture* > textures = AssetManager::get_instance().get_textures();
    switch (event)
    {
    case GameEvent::GAME_STARTED:
        gamestate = GameState::GAMING;
        sprites.find("background")->second.setTexture(*textures.at("room"));
        break;
    case GameEvent::RENDER_FLUSH:
        window.clear();
        draw_and_display();
        break;
    case GameEvent::PLAYER_DIED:
        gamestate = GameState::END_GAME;
        sprites.find("background")->second.setTexture(*textures.at("end_window"));
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