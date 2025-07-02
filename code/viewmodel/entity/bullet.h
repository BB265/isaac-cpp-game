#pragma once
#include "common/entity.h"
#include "player.h"
#include "common/Direction.h"

#include <cmath>

class Bullet : public Entity {
public:
    Bullet(int x, int y, const Player* owner, int damage, int speed, Direction initial_dir);
    ~Bullet() {}
    void update() override;
    sf::IntRect getBounds() const override { return sf::IntRect({getX(), getY()}, {BULLET_WIDTH, BULLET_HEIGHT}); }

    // validation
    bool isValid() const { return is_valid_; }

private:
    const Player* owner_;
    int damage_;
    int speed_;
    sf::Vector2f velocity_;
    bool is_valid_ = true;
};
