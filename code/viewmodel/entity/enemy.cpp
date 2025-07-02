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
}

void Enemy::collideWith(Entity* entity) {
    if (entity->getType() == EntityType::Player) {
        Player* player = static_cast<Player*>(entity);
        if (player->isInvincible()) {
            return;
        }
        int health = player->getHealth();
        player->setHealth(health - damage_);
    }
}
