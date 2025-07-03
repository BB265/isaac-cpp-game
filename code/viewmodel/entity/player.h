#pragma once
#include "common/entity.h"
#include "common/Commands.h"
#include "common/EventSystem.h"
#include "common/Direction.h"

class Player : public Entity {
public:
    Player(float x, float y, float speed) : Entity(x, y, EntityType::Player), direction_(Direction::None), speed_(speed) {}
    ~Player() {}

    // move
    void setDirection(Direction direction);
    Direction getDirection() const { return direction_; }
    void setSpeed(float speed);
    float getSpeed() const { return speed_; }
    sf::Vector2f getVelocity() const { return cur_velocity_; }
    bool isMoving() const { return direction_ != Direction::None; }
    void update() override;

    // collision
    sf::FloatRect getBounds() const override { return sf::FloatRect({getX() + 10, getY() + 10}, {PLAYER_WIDTH - 20, PLAYER_HEIGHT - 10}); }
    void collideWith(Entity* other) override {}
    void setInvincibleCd(sf::Time invincibleCd) { invincible_cd_ = invincibleCd; }
    sf::Time getInvincibleCd() const { return invincible_cd_; }
    bool isInvincible();

    // health
    void setHealth(int health) { health_ = health; }
    const int& getHealth() const { return health_; }
    void changeHealth(int delta) { health_ += delta; }
    void setMaxHealth(int maxHealth) { max_health_ = maxHealth; }
    const int& getMaxHealth() const { return max_health_; }
    void changeMaxHealth(int delta) { max_health_ += delta; }
    bool isAlive() const { return health_ > 0; }

    // attack
    void setDamage(int damage) { damage_ = damage; }
    int getDamage() const { return damage_; }
    void setCoolDown(sf::Time coolDown_) { shoot_cd_ = coolDown_; }
    sf::Time getCoolDown() const { return shoot_cd_; }
    bool atCoolDown();

private:
    Direction direction_;
    float speed_;
    sf::Vector2f start_velocity_;
    sf::Vector2f cur_velocity_;
    sf::Vector2f target_velocity_;
    int ease_duration_f_ = 35;
    int ease_f_num_ = 0;
    int max_health_ = 5;
    int health_ = max_health_;
    int damage_ = 1;
    sf::Clock clock_;
    sf::Time shoot_cd_ = sf::seconds(0.5);
    sf::Time last_shoot_ = sf::seconds(-1);
    sf::Time invincible_cd_ = sf::seconds(1);
    sf::Time last_invincible_ = sf::Time::Zero;
};