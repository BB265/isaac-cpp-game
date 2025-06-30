#pragma once
#include "common/MetaData.h"

class Entity {
public:
    Entity(int x, int y) : x_(x), y_(y) {}
    virtual ~Entity() = default;
    int getX() const { return x_; }
    int getY() const { return y_; }
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    int getVx() const { return vx_; }
    int getVy() const { return vy_; }

protected:
    void setVx(int vx) { vx_ = vx; }
    void setVy(int vy) { vy_ = vy; }

public:
    // update interfaces
    virtual void update() {
        x_ += vx_;
        y_ += vy_;
        if (x_ < ROOM_LEFT) {
            x_ = ROOM_LEFT;
        }
        if (x_ > ROOM_RIGHT) {
            x_ = ROOM_RIGHT;
        }
        if (y_ < ROOM_TOP) {
            y_ = ROOM_TOP;
        }
        if (y_ > ROOM_BPTTOM) {
            y_ = ROOM_BPTTOM;
        }
    }

private:
    int x_;
    int y_;
    int vx_;
    int vy_;
};