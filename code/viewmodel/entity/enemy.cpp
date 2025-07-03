#include "enemy.h"
#include "player.h"

void Enemy::update() {
    float dx = target->getX() - getX();
    float dy = target->getY() - getY();
    float distance = sqrt(dx * dx + dy * dy);

    sf::Vector2f v = {0, 0};
    if (distance != 0) {
        v.x = dx * speed_ / distance;
        v.y = dy * speed_ / distance;
    }

    // 设置受击效果
    if (getType() == EntityType::EnemyHit) {
        hit_f_num_++;
        float t = hit_f_num_ / (float)hit_duration_f_;
        v += knock_back_v_ * (1 - t);

        if (hit_f_num_ == hit_duration_f_) {
            hit_f_num_ = 0;
            setType(EntityType::Enemy);
            knock_back_v_ = {0, 0};
        }
    }

    // 移动
    setX(getX() + v.x);
    setY(getY() + v.y);
}

void Enemy::collideWith(Entity* entity) {
    if (entity->getType() == EntityType::Player) {
        Player* player = static_cast<Player*>(entity);
        if (player->isInvincible()) {
            return;
        }
        int health = player->getHealth();
        player->setHealth(health - damage_);
        player->setType(EntityType::PlayerHit);
    }
}

void Enemy::knockBack(Bullet* bullet) {
    knock_back_v_ = bullet->getVelocity() * 0.5f;
}