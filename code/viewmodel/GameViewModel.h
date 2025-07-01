// viewmodel/GameViewModel.h

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include "../common/Commands.h"
#include "../common/EventSystem.h"
#include "../common/Direction.h"
#include "../common/MetaData.h"
#include "../common/entity.h"
#include "entity/player.h"
#include "entity/enemy.h"
#include "entity/bullet.h"

class GameViewModel : public Subject, public std::enable_shared_from_this<GameViewModel> {
public:
    GameViewModel();
	void startNewGame();  // 开始新游戏，重置所有状态，生成实体
    void update();  // 每一帧都要调用，更新所有游戏实体的状态
    const Player* getPlayer() const;
	const std::vector<std::shared_ptr<Entity>>& getEntities() const;
	const int* getCurrentHealth() const;
	const int* getMaxHealth() const;
	void registerCommand(CommandType type, std::shared_ptr<ICommandBase> command);
	void executeCommand(CommandType type, const std::any& args);
	EXCommand getCommand();
	void registerAllCommands();


private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	Player* m_player_ptr;  // 玩家实体

	std::unordered_map<CommandType, std::shared_ptr<ICommandBase>> m_commands;  // 命令映射表
};