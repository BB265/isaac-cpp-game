#pragma once
#include "common/entity.h"
#include "common/Commands.h"
#include "common/EventSystem.h"
#include "common/Direction.h"

class Player : public Entity {
public:
    Player(int x, int y, int speed) : Entity(x, y, EntityType::Player), direction_(Direction::None), speed_(speed) {}
    ~Player() {}

    // move
    void setDirection(Direction direction);
    Direction getDirection() const { return direction_; }
    void setSpeed(int speed);
    int getSpeed() const { return speed_; }
    sf::Vector2f getVelocity() const { return cur_velocity_; }
    bool isMoving() const { return direction_ != Direction::None; }
    void update() override;
    sf::IntRect getBounds() const override { return sf::IntRect({getX(), getY()}, {PLAYER_WIDTH, PLAYER_HEIGHT}); }

    // health
    void setHealth(int health) { health = health; }
    int getHealth() const { return health; }
    void changeHealth(int delta) { health += delta; }
    void setMaxHealth(int maxHealth) { maxHealth = maxHealth; }
    int getMaxHealth() const { return maxHealth; }
    void changeMaxHealth(int delta) { maxHealth += delta; }
    bool isAlive() const { return health > 0; }

    // attack
    void setDamage(int damage) { damage = damage; }
    int getDamage() const { return damage; }
    void setCoolDown(sf::Time coolDown) { coolDown = coolDown; }
    sf::Time getCoolDown() const { return coolDown; }
    bool atCoolDown();

private:
    Direction direction_;
    int speed_;
    sf::Vector2f start_velocity_;
    sf::Vector2f cur_velocity_;
    sf::Vector2f target_velocity_;
    int ease_duration_f_ = 50;
    int ease_f_num_ = 0;
    int maxHealth = 5;
    int health = maxHealth;
    int damage = 1;
    sf::Clock coolDownClock;
    sf::Time coolDown = sf::seconds(0.5);
    sf::Time lastShootTime = sf::Time::Zero;
};