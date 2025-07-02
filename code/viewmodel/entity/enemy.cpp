#include "enemy.h"
#include "player.h"

void Enemy::update() {
    int dx = target->getX() - getX();
    int dy = target->getY() - getY();
    // std::cout << "dx: " << dx << " dy: " << dy << std::endl;
    if (dx != 0 || dy != 0) {
        double distance = sqrt(dx * dx + dy * dy);
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
        std::cout << "Enemy collide with player" << std::endl;
        int health = player->getHealth();
        std:: cout << "player health: " << health - 1 << std::endl;
        player->setHealth(health - damage_);
    }
}
