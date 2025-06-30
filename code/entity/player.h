#pragma once
#include "entity/entity.h"
#include "common/Commands.h"
#include "common/EventSystem.h"
#include "common/Direction.h"

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
    void setSpeed(int speed) { speed_ = speed; }
    int getSpeed() const { return speed_; }
    bool isMoving() const { return direction_ != Direction::None; }

    // health
    void setHealth(int health) { health = health; }
    int getHealth() const { return health; }
    void changeHealth(int delta) { health += delta; }

    // attack
    void setDamage(int damage) { damage = damage; }
    int getDamage() const { return damage; }

private:
    Direction direction_;
    int speed_;
    int maxHealth = 5;
    int health = maxHealth;
    int damage = 1;
};