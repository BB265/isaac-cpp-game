#pragma once
#include "entity/entity.h"
#include "common/Commands.h"
#include "common/EventSystem.h"
#include "common/Direction.h"
#include <SFML/System.hpp>

class Player : public Entity {
public:
    Player(int x, int y, int speed) : Entity(x, y), direction_(Direction::None), speed_(speed) {
        setVx(0);
        setVy(0);
    }
    ~Player() {}

    // move
    void setDirection(Direction direction);
    Direction getDirection() const { return direction_; }
    void setSpeed(int speed);
    int getSpeed() const { return speed_; }
    bool isMoving() const { return direction_ != Direction::None; }

    // health
    void setHealth(int health) { health = health; }
    int getHealth() const { return health; }
    void changeHealth(int delta) { health += delta; }
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
    int maxHealth = 5;
    int health = maxHealth;
    int damage = 1;
    sf::Clock coolDownClock;
    sf::Time coolDown = sf::seconds(0.5);
    sf::Time lastShootTime = sf::Time::Zero;
};