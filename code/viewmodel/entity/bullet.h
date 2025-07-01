#pragma once
#include "common/entity.h"
#include "player.h"
#include "common/Direction.h"

#include <cmath>

class Bullet : public Entity {
public:
    Bullet(int x, int y, const Player* owner, int damage, int speed, Direction initial_dir);
    ~Bullet() {}

    // validation
    bool isValid() const { return getX() > ROOM_LEFT && getX() < ROOM_RIGHT && getY() > ROOM_TOP && getY() < ROOM_BOTTOM; }

private:
    const Entity* owner_;
    int damage_;
    int speed_;
    int vx_;
    int vy_;
};
