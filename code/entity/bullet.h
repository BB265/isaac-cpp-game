#pragma once
#include "entity.h"
#include "common/Direction.h"

class Bullet : public Entity {
public:
    Bullet(int x, int y, Entity* owner, int damage, int speed, Direction initial_dir);
    ~Bullet() {}

private:
    Entity* owner_;
    int damage_;
};
