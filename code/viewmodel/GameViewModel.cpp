// viewmodel/GameViewModel.cpp

#include "GameViewModel.h"

GameViewModel::GameViewModel()
    : m_player(0, 0, 0) {

    moveCommand = [this](Direction dir) {
        m_player.setDirection(dir);
    };

}

void GameViewModel::startNewGame() {
    // 1. 清空之前状态
    m_enemies.clear();

    // 2. 初始化状态
    m_player.setPosition(400, 300);  // 玩家初始位置
    m_player.setSpeed(5);  // 玩家初始速度
    m_player.setHealth(5);  // 玩家初始血量

    /*
    // 3. 初始化本关卡的敌人
    m_enemies.emplace_back(100, 100, 2);
    m_enemies.emplace_back(700, 100, 2);
    m_enemies.emplace_back(100, 500, 2);
    m_enemies.emplace_back(700, 500, 2);
    */

    // 4. (可选) 发布一个“游戏开始”或“关卡加载完毕”的事件
     Subject::notify(GameEvent::GAME_STARTED);
}

void GameViewModel::update() {
    m_player.update();

    // TODO: 未来在这里遍历并更新所有敌人和子弹的状态
    // for (auto& enemy : m_enemies) {
    //     enemy.update();
    // }

    // TODO: 在这里执行碰撞检测等其他游戏逻辑
}

const Player& GameViewModel::getPlayer() const {
    return m_player;
}

const std::vector<Enemy>& GameViewModel::getEnemies() const {
    return m_enemies;
}