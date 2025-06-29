#include "entity/player.h"

void Player::setDirection(Direction direction) {
    direction_ = direction;
    if (direction == Direction::Up) {
        setVy(-speed_);
    } else if (direction == Direction::Down) {
        setVy(speed_);
    } else if (direction == Direction::Left) {
        setVx(-speed_);
    } else if (direction == Direction::Right) {
        setVx(speed_);
    } else {
        setVx(0);
        setVy(0);
    }
}

void Player::changeSpeed(int delta) {
    speed_ += delta;
    if (speed_ < 0) {
        speed_ = 1;
    }
    setDirection(direction_);
}