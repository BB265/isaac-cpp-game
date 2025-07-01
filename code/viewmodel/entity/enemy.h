#pragma once
#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(int x, int y) : Entity(x, y) {}
    ~Enemy() {}

    // attack
    int getDamage() const { return damage_; }
    void setDamage(int damage) { damage_ = damage; }

    // health
    int getHealth() const { return health_; }
    void setHealth(int health) { health_ = health; }

private:
    int health_ = 1;
    int damage_ = 1;
};
