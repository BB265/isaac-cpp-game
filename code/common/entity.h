#pragma once
#include "common/MetaData.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System.hpp>

enum class EntityType {
    Player,
    Bullet,
    Enemy,
};

class Entity {
public:
    Entity(int x, int y, EntityType type) : x_(x), y_(y), type_(type) {}
    virtual ~Entity() = default;
    EntityType getType() const { return type_; }
    int getX() const { return x_; }
    int getY() const { return y_; }
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }

public:
    // update interfaces
    virtual void update() = 0;
    virtual sf::IntRect getBounds() const = 0;
    virtual void collideWith(Entity* other) = 0;

private:
    int x_;
    int y_;
    EntityType type_;
};