#pragma once

class Entity {
public:
    virtual void update() {
        x_ += vx_;
        y_ += vy_;
    }
    virtual ~Entity() = default;

protected:
    Entity(int x, int y) : x_(x), y_(y) {}
    int getX() const { return x_; }
    int getY() const { return y_; }
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    int getVx() const { return vx_; }
    int getVy() const { return vy_; }
    void setVx(int vx) { vx_ = vx; }
    void setVy(int vy) { vy_ = vy; }

private:
    int x_;
    int y_;
    int vx_;
    int vy_;
};