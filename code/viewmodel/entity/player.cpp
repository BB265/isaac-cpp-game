#include "player.h"

float easeOutQuad(float t) {
    return 1 - std::pow(1 - t, 4);
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
        case Direction::Up:    target_velocity_ = {0.0f, -(speed_)}; break;
        case Direction::Down:  target_velocity_ = {0.0f, (speed_)};  break;
        case Direction::Left:  target_velocity_ = {-(speed_), 0.0f}; break;
        case Direction::Right: target_velocity_ = {(speed_), 0.0f};  break;
        case Direction::UpLeft: target_velocity_ = {-(speed_ / sqrt(2.f)), -(speed_ / sqrt(2.f))}; break;
        case Direction::UpRight: target_velocity_ = {(speed_ / sqrt(2.f)), -(speed_ / sqrt(2.f))}; break;
        case Direction::DownLeft: target_velocity_ = {-(speed_ / sqrt(2.f)), (speed_ / sqrt(2.f))}; break;
        case Direction::DownRight: target_velocity_ = {(speed_ / sqrt(2.f)), (speed_ / sqrt(2.f))}; break;
        default:               target_velocity_ = {0.0f, 0.0f};        break;
    }

    ease_f_num_ = 0; // 重置缓动帧数
}

void Player::setSpeed(float speed) {
    speed_ = speed;
    setDirection(direction_);
}

bool Player::atCoolDown() {
    if (clock_.getElapsedTime() - last_shoot_ >= shoot_cd_) {
        last_shoot_ = clock_.getElapsedTime();
        return false;
    }
    return true;
}

bool Player::isInvincible() {
    if (clock_.getElapsedTime() - last_invincible_ >= invincible_cd_) {
        last_invincible_ = clock_.getElapsedTime();
        return false;
    }
    return true;
}
