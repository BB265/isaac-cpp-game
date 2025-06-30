#pragma once
#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(int x, int y, const Entity* target) : Entity(x, y), target(target) {}
    ~Enemy() {}

    // move
    void setSpeed(int speed) { speed_ = speed; }
    int getSpeed() const { return speed_; }
    void update() override {
        int dx = target->getX() - getX();
        int dy = target->getY() - getY();
        int distance = sqrt(dx * dx + dy * dy);
        if (distance > 0) {
            setX(getX() + dx * speed_ / distance);
            setY(getY() + dy * speed_ / distance);
        }
    }

    // attack
    int getDamage() const { return damage_; }
    void setDamage(int damage) { damage_ = damage; }

    // health
    int getHealth() const { return health_; }
    void setHealth(int health) { health_ = health; }

private:
    int health_ = 1;
    int damage_ = 1;
    int speed_ = 3;
    const Entity* target;
};
