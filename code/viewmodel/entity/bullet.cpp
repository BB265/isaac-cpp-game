#include "bullet.h"

Bullet::Bullet(int x, int y, const Player* owner, int damage, int speed, Direction initial_dir)
    : Entity(x, y, EntityType::Bullet), owner_(owner), damage_(damage), speed_(speed) {
    switch (initial_dir) {
        case Direction::Up:    velocity_ = {0.0f, -static_cast<float>(speed_)}; break;
        case Direction::Down:  velocity_ = {0.0f, static_cast<float>(speed_)};  break;
        case Direction::Left:  velocity_ = {-static_cast<float>(speed_), 0.0f}; break;
        case Direction::Right: velocity_ = {static_cast<float>(speed_), 0.0f};  break;
        case Direction::UpLeft: velocity_ = {-static_cast<float>(speed_ / sqrt(2)), -static_cast<float>(speed_ / sqrt(2))}; break;
        case Direction::UpRight: velocity_ = {static_cast<float>(speed_ / sqrt(2)), -static_cast<float>(speed_ / sqrt(2))}; break;
        case Direction::DownLeft: velocity_ = {-static_cast<float>(speed_ / sqrt(2)), static_cast<float>(speed_ / sqrt(2))}; break;
        case Direction::DownRight: velocity_ = {static_cast<float>(speed_ / sqrt(2)), static_cast<float>(speed_ / sqrt(2))}; break;
        default:               velocity_ = {0.0f, 0.0f};        break;
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