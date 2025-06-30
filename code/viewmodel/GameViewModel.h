// viewmodel/GameViewModel.h
#pragma once

#include "../common/Commands.h"
#include "../common/EventSystem.h"
#include "../common/Direction.h"
#include "../common/MetaData.h"
#include "../entity/player.h"
#include "../entity/enemy.h"
#include "../common/EventSystem.h"
#include <vector>
#include <memory>

class GameViewModel : public Subject {
public:
    GameViewModel();
	void startNewGame();  // 开始新游戏，重置所有状态，生成实体
    void update();  // 每一帧都要调用，更新所有游戏实体的状态
    const Player& getPlayer() const;
    const std::vector<Enemy>& getEnemies() const;
    MoveCommand moveCommand;  // 提供给view层的命令，通过这个传递玩家移动的指令


private:
	Player m_player;  // 玩家实体
	std::vector<Enemy> m_enemies;  // 敌人实体列表
};