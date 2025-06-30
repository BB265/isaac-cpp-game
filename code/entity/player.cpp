#include "entity/player.h"

void Player::setDirection(Direction direction) {
    direction_ = direction;
    if (direction == Direction::Up) {
        setVx(0);
        setVy(-speed_);
    } else if (direction == Direction::Down) {
        setVx(0);
        setVy(speed_);
    } else if (direction == Direction::Left) {
        setVx(-speed_);
        setVy(0);
    } else if (direction == Direction::Right) {
        setVx(speed_);
        setVy(0);
    } else if (direction == Direction::UpLeft) {
        setVx((-speed_) * sqrt(2) / 2);
        setVy((-speed_) * sqrt(2) / 2);
    } else if (direction == Direction::UpRight) {
        setVx((speed_) * sqrt(2) / 2);
        setVy((-speed_) * sqrt(2) / 2);
    } else if (direction == Direction::DownLeft) {
        setVx((-speed_) * sqrt(2) / 2);
        setVy((speed_) * sqrt(2) / 2);
    } else if (direction == Direction::DownRight) {
        setVx((speed_) * sqrt(2) / 2);
        setVy((speed_) * sqrt(2) / 2);
    } else {
        setVx(0);
        setVy(0);
    }
}
