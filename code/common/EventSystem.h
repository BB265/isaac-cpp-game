// common/EventSystem.h

#pragma once

#include <vector>
#include <algorithm>

/**
 * @brief 游戏事件枚举
 */
enum class GameEvent {
	GAME_STARTED,
    RENDER_FLUSH,
    PLAYER_DIED,
    ENEMY_KILLED,
    ITEM_PICKED_UP,
    PLAY_SOUND_SHOOT,
    PLAY_SOUND_HIT
};

/**
 * @brief 观察者：受到通知，并根据事件执行相应操作
 */
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify(GameEvent event) = 0;  // 事件发生后，观察者调用该函数进行操作
};

/**
 * @brief 主题：管理观察者列表 & 发布通知
 */
class Subject {
private:
    std::vector<IObserver*> observers_;

public:
    void addObserver(IObserver* observer) {
        observers_.push_back(observer);
    }

    void removeObserver(IObserver* observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

protected:
    // 通知所有观察者
    void notify(GameEvent event) {
        for (IObserver* observer : observers_) {
            observer->onNotify(event);
        }
    }
};