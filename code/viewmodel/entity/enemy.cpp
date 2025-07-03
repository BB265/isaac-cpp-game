#include "enemy.h"
#include "player.h"

void Enemy::update() {
    float dx = target->getX() - getX();
    float dy = target->getY() - getY();
    float distance = sqrt(dx * dx + dy * dy);
    if (distance != 0) {
        setX(getX() + dx * speed_ / distance);
        setY(getY() + dy * speed_ / distance);
    }

    // 设置受击效果
    if (getType() == EntityType::EnemyHit) {
        hit_f_num_++;
        if (hit_f_num_ == hit_duration_f_) {
            hit_f_num_ = 0;
            setType(EntityType::Enemy);
        }
    }
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
