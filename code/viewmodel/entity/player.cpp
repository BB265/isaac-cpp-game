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

        cur_velocity_ = start_velocity_ + eased_t * (target_velocity_ - start_velocity_);

        // 更新坐标
        setX(getX() + static_cast<int>(cur_velocity_.x));
        setY(getY() + static_cast<int>(cur_velocity_.y));
    } else {
        // 结束缓动后保持目标速度
        setX(getX() + target_velocity_.x);
        setY(getY() + target_velocity_.y);
        start_velocity_ = target_velocity_;
        cur_velocity_ = target_velocity_;
    }

    // 处理边界
    if (getX() < ROOM_LEFT) {
        setX(ROOM_LEFT);
        cur_velocity_.x = 0;
    } else if (getX() > ROOM_RIGHT - PLAYER_WIDTH) {
        setX(ROOM_RIGHT - PLAYER_WIDTH);
        cur_velocity_.x = 0;
    }
    if (getY() < ROOM_TOP) {
        setY(ROOM_TOP);
        cur_velocity_.y = 0;
    } else if (getY() > ROOM_BOTTOM - PLAYER_HEIGHT) {
        setY(ROOM_BOTTOM - PLAYER_HEIGHT);
        cur_velocity_.y = 0;
    }
}

void Player::setDirection(Direction direction) {
    if (direction_ == direction) return; // 同方向不用处理

    direction_ = direction;
    start_velocity_ = cur_velocity_;

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
