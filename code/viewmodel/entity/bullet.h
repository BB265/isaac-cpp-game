#pragma once
#include "common/entity.h"
#include "player.h"
#include "common/Direction.h"

class Bullet : public Entity {
public:
    Bullet(float x, float y, const Player* owner, int damage, int speed, Direction initial_dir);
    ~Bullet() {}
    void update() override;

    // collision
    void collideWith(Entity* other) override;
    sf::FloatRect getBounds() const override { return sf::FloatRect({getX(), getY()}, {BULLET_WIDTH, BULLET_HEIGHT}); }
    sf::Vector2f getVelocity() const { return velocity_; }

    // validation
    bool isValid() const { return is_valid_; }

private:
    const Player* owner_;
    int damage_;
    float speed_;
    sf::Vector2f velocity_;
    bool broken_ = false;
    bool is_valid_ = true;
    int hit_duration_f_ = 20;
    int hit_f_num_ = 0;
};
