#include "bullet.h"

Bullet::Bullet(int x, int y, const Player* owner, int damage, int speed, Direction initial_dir)
    : Entity(x, y, EntityType::Bullet), owner_(owner), damage_(damage), speed_(speed) {
    switch (initial_dir) {
        case Direction::Up:    velocity_ = {0, -speed_}; break;
        case Direction::Down:  velocity_ = {0, speed_};  break;
        case Direction::Left:  velocity_ = {-speed_, 0}; break;
        case Direction::Right: velocity_ = {speed_, 0};  break;
        case Direction::UpLeft: velocity_ = {-speed_ / std::sqrt(2), -speed_ / std::sqrt(2)}; break;
        case Direction::UpRight: velocity_ = {speed_ / std::sqrt(2), -speed_ / std::sqrt(2)}; break;
        case Direction::DownLeft: velocity_ = {-speed_ / std::sqrt(2), speed_ / std::sqrt(2)}; break;
        case Direction::DownRight: velocity_ = {speed_ / std::sqrt(2), speed_ / std::sqrt(2)}; break;
        default:               velocity_ = {0, 0};        break;
    }
    velocity_ += owner_->getVelocity();
}

void Bullet::update() {
    setX(getX() + velocity_.x);
    setY(getY() + velocity_.y);

    // 处理边界
    if (getX() < ROOM_LEFT) {
        is_valid_ = false;
    } else if (getX() > ROOM_RIGHT - BULLET_WIDTH) {
        is_valid_ = false;
    }
    if (getY() < ROOM_TOP) {
        is_valid_ = false;
    } else if (getY() > ROOM_BOTTOM - BULLET_HEIGHT) {
        is_valid_ = false;
    }
}