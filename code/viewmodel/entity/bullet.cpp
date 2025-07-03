#include "bullet.h"
#include "enemy.h"

Bullet::Bullet(float x, float y, const Player* owner, int damage, int speed, Direction initial_dir)
    : Entity(x, y, EntityType::Bullet), owner_(owner), damage_(damage), speed_(speed) {
    switch (initial_dir) {
        case Direction::Up:    velocity_ = {0.0f, -(speed_)}; break;
        case Direction::Down:  velocity_ = {0.0f, (speed_)};  break;
        case Direction::Left:  velocity_ = {-(speed_), 0.0f}; break;
        case Direction::Right: velocity_ = {(speed_), 0.0f};  break;
        case Direction::UpLeft: velocity_ = {-(speed_ / sqrt(2.f)), -(speed_ / sqrt(2.f))}; break;
        case Direction::UpRight: velocity_ = {(speed_ / sqrt(2.f)), -(speed_ / sqrt(2.f))}; break;
        case Direction::DownLeft: velocity_ = {-(speed_ / sqrt(2.f)), (speed_ / sqrt(2.f))}; break;
        case Direction::DownRight: velocity_ = {(speed_ / sqrt(2.f)), (speed_ / sqrt(2.f))}; break;
        default:               velocity_ = {0.0f, 0.0f};        break;
    }
    velocity_ += owner_->getVelocity();
}

void Bullet::update() {
    if (broken_) {
        hit_f_num_++;
        if (hit_f_num_ >= hit_duration_f_) {
            hit_f_num_ = 0;
            is_valid_ = false;
            setType(EntityType::Bullet);
        }
        return;
    }
    setX(getX() + velocity_.x);
    setY(getY() + velocity_.y);

    // 处理边界
    if (getX() < ROOM_LEFT) {
        broken_ = true;
        setType(EntityType::BulletBroken);
    } else if (getX() > ROOM_RIGHT - BULLET_WIDTH) {
        broken_ = true;
        setType(EntityType::BulletBroken);
    }
    if (getY() < ROOM_TOP) {
        broken_ = true;
        setType(EntityType::BulletBroken);
    } else if (getY() > ROOM_BOTTOM - BULLET_HEIGHT) {
        broken_ = true;
        setType(EntityType::BulletBroken);
    }
}

void Bullet::collideWith(Entity* other) {
    if (broken_) return;
    if (other->getType() == EntityType::Enemy) {
        Enemy* enemy = static_cast<Enemy*>(other);
        int health = enemy->getHealth();
        enemy->setHealth(health - damage_);
        enemy->setType(EntityType::EnemyHit);
        enemy->knockBack(this);
        broken_ = true;
        setType(EntityType::BulletBroken);
    }
}