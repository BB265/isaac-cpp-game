#pragma once
#include "common/entity.h"

class Enemy : public Entity {
public:
    Enemy(float x, float y, const Entity* target) : Entity(x, y, EntityType::Enemy), target(target) {}
    ~Enemy() {}

    // move
    void setSpeed(float speed) { speed_ = speed; }
    float getSpeed() const { return speed_; }
    void update() override;

    // collision
    void collideWith(Entity* entity) override;
    sf::FloatRect getBounds() const override { return sf::FloatRect({getX() + 10, getY() + 10}, {ENEMY_WIDTH - 20, ENEMY_HEIGHT - 10}); }

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
    float speed_ = 1;
    const Entity* target;
    int hit_duration_f_ = 10;
    int hit_f_num_ = 0;
};