#pragma once
#include "common/MetaData.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System.hpp>
#include <cmath>

enum class EntityType {
    Player,
    Bullet,
    Enemy,
};

class Entity {
public:
    Entity(float x, float y, EntityType type) : x_(x), y_(y), type_(type) {}
    virtual ~Entity() = default;
    EntityType getType() const { return type_; }
    float getX() const { return x_; }
    float getY() const { return y_; }
    void setX(float x) { x_ = x; }
    void setY(float y) { y_ = y; }

public:
    // update interfaces
    virtual void update() = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual void collideWith(Entity* other) = 0;

private:
    float x_;
    float y_;
    EntityType type_;
};