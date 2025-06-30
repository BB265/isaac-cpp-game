#include "entity/bullet.h"

Bullet::Bullet(int x, int y, const Entity* owner, int damage, int speed, Direction initial_dir)
    : Entity(x, y), owner_(owner), damage_(damage), speed_(speed) {
    int vx = 0;
    int vy = 0;
    if (initial_dir == Direction::Up) {
        vy = -speed_;
    } else if (initial_dir == Direction::Down) {
        vy = speed_;
    } else if (initial_dir == Direction::Left) {
        vx = -speed_;
    } else if (initial_dir == Direction::Right) {
        vx = speed_;
    } else if (initial_dir == Direction::UpLeft) {
        vx = (-speed_ * sqrt(2)) / 2;
        vy = (-speed_ * sqrt(2)) / 2;
    } else if (initial_dir == Direction::UpRight) {
        vx = (speed_ * sqrt(2)) / 2;
        vy = (-speed_ * sqrt(2)) / 2;
    } else if (initial_dir == Direction::DownLeft) {
        vx = (-speed_ * sqrt(2)) / 2;
        vy = (speed_ * sqrt(2)) / 2;
    } else if (initial_dir == Direction::DownRight) {
        vx = (speed_ * sqrt(2)) / 2;
        vy = (speed_ * sqrt(2)) / 2;
    }
    setVx(owner_->getVx() + vx);
    setVy(owner_->getVy() + vy);
}
