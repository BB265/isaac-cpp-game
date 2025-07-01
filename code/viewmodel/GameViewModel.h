// viewmodel/GameViewModel.h

#pragma once

#include "../common/Commands.h"
#include "../common/EventSystem.h"
#include "../common/Direction.h"
#include "../common/MetaData.h"
#include "../common/entity.h"
#include "entity/player.h"
#include "entity/enemy.h"
#include "entity/bullet.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <iostream>

class GameViewModel : public Subject, public std::enable_shared_from_this<GameViewModel> {
public:
    GameViewModel();
	void startNewGame();  // 开始新游戏，重置所有状态，生成实体
    void update();  // 每一帧都要调用，更新所有游戏实体的状态
    const Player& getPlayer() const;
    const std::vector<Enemy>& getEnemies() const;
	const std::vector<Bullet>& getBullets() const;
	void registerCommand(CommandType type, std::shared_ptr<ICommandBase> command);
	void executeCommand(CommandType type, const std::any& args);
	void registerAllCommands();


private:
	Player m_player;  // 玩家实体
	std::vector<Enemy> m_enemies;  // 敌人实体列表
	std::vector<Bullet> m_bullets;  // 子弹实体列表
	std::unordered_map<CommandType, std::shared_ptr<ICommandBase>> m_commands;  // 命令映射表
};