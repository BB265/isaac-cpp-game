#pragma once
#include "common/entity.h"

class Enemy : public Entity {
public:
    Enemy(int x, int y, const Entity* target) : Entity(x, y, EntityType::Enemy), target(target) {}
    ~Enemy() {}

    // move
    void setSpeed(int speed) { speed_ = speed; }
    int getSpeed() const { return speed_; }
    void update() override;

    // collision
    void collideWith(Entity* entity) override;
    sf::IntRect getBounds() const override { return sf::IntRect({getX(), getY()}, {ENEMY_WIDTH, ENEMY_HEIGHT}); }

    // attack
    int getDamage() const { return damage_; }
    void setDamage(int damage) { damage_ = damage; }

    // health
    int getHealth() const { return health_; }
    void setHealth(int health) { health_ = health; }
    bool isAlive() const { return health_ > 0; }

private:
    int health_ = 2;
    int damage_ = 1;
    int speed_ = 1;
    const Entity* target;
};