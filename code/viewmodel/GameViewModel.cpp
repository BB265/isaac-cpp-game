// viewmodel/GameViewModel.cpp

#include "GameViewModel.h"

GameViewModel::GameViewModel()
    : m_player(0, 0, 0) {

    moveCommand = [this](Direction dir) {
        m_player.setDirection(dir);
    };

    shootCommand = [this](Direction dir) {
        m_bullets.emplace_back(
            m_player.getX(),
            m_player.getY(),
            &m_player,
            1,  // 子弹伤害
            10, // 子弹速度
            dir
		);

		notify(GameEvent::PLAY_SOUND_SHOOT);
    };

}

void GameViewModel::startNewGame() {
    // 1. 清空之前状态
    m_enemies.clear();
	m_bullets.clear();

    // 2. 初始化状态
    m_player.setX(400);  // 玩家初始位置x
    m_player.setY(300);  // 玩家初始位置y
    m_player.setSpeed(5);  // 玩家初始速度
    m_player.setHealth(5);  // 玩家初始血量

    /*
    // 3. 初始化本关卡的敌人
    m_enemies.emplace_back(100, 100, 2);
    m_enemies.emplace_back(700, 100, 2);
    m_enemies.emplace_back(100, 500, 2);
    m_enemies.emplace_back(700, 500, 2);
    */

    // 4. 发布一个“游戏开始”的事件
    notify(GameEvent::GAME_STARTED);
}

void GameViewModel::update() {
	// 1. 更新玩家状态
    m_player.update();

	// 2. 更新敌人状态
    for (auto& enemy : m_enemies) {
        enemy.update();
    }

	// 3. 更新子弹状态
    for (auto& bullet : m_bullets) {
        bullet.update();
	}

    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](const Bullet& p) {
                return !p.isValid();
            }),
        m_bullets.end()
    );

}

const Player& GameViewModel::getPlayer() const {
    return m_player;
}

const std::vector<Enemy>& GameViewModel::getEnemies() const {
    return m_enemies;
}

const std::vector<Bullet>& GameViewModel::getBullets() const {
    return m_bullets;
}