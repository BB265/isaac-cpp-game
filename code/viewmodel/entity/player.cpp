#include "player.h"

float easeOutQuad(float t) {
    return 1 - (1 - t) * (1 - t);
}

void Player::update() {
    // 每次 update 增加缓动帧计数
    if (ease_f_num_ < ease_duration_f_) {
        ease_f_num_++;
        float t = static_cast<float>(ease_f_num_) / ease_duration_f_;
        float eased_t = easeOutQuad(t);

        sf::Vector2f cur_velocity_ = start_velocity_ + eased_t * (target_velocity_ - start_velocity_);

        // 更新坐标
        setX(getX() + static_cast<int>(cur_velocity_.x));
        setY(getY() + static_cast<int>(cur_velocity_.y));
    } else {
        // 结束缓动后保持目标速度
        setX(getX() + target_velocity_.x);
        setY(getY() + target_velocity_.y);
        start_velocity_ = target_velocity_;
    }
}

void Player::setDirection(Direction direction) {
    if (direction_ == direction) return; // 同方向不用处理

    direction_ = direction;

    // 根据方向设置目标速度
    switch (direction) {
        case Direction::Up:    target_velocity_ = {0, -speed_}; break;
        case Direction::Down:  target_velocity_ = {0, speed_};  break;
        case Direction::Left:  target_velocity_ = {-speed_, 0}; break;
        case Direction::Right: target_velocity_ = {speed_, 0};  break;
        case Direction::UpLeft: target_velocity_ = {-speed_ / std::sqrt(2), -speed_ / std::sqrt(2)}; break;
        case Direction::UpRight: target_velocity_ = {speed_ / std::sqrt(2), -speed_ / std::sqrt(2)}; break;
        case Direction::DownLeft: target_velocity_ = {-speed_ / std::sqrt(2), speed_ / std::sqrt(2)}; break;
        case Direction::DownRight: target_velocity_ = {speed_ / std::sqrt(2), speed_ / std::sqrt(2)}; break;
        default:               target_velocity_ = {0, 0};        break;
    }

    ease_f_num_ = 0; // 重置缓动帧数
}

void Player::setSpeed(int speed) {
    speed_ = speed;
    setDirection(direction_);
}

bool Player::atCoolDown() {
    if (coolDownClock.getElapsedTime() - lastShootTime >= coolDown) {
        lastShootTime = coolDownClock.getElapsedTime();
        return false;
    }
    return true;
}
