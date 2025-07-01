// viewmodel/GameViewModel.cpp

#include "GameViewModel.h"

GameViewModel::GameViewModel() {
	registerAllCommands();
}

void GameViewModel::startNewGame() {
    // 1. 清空之前状态
	m_entities.clear();
    m_player_ptr = nullptr;

	// 2. 创建玩家实体
	auto player = std::make_unique<Player>(400, 300, 5);
	player->setMaxHealth(6);
	player->setHealth(6);
	m_player_ptr = player.get();
	m_entities.push_back(std::move(player));

	// 3. 创建敌人实体

    // 4. 发布一个“游戏开始”的事件
    notify(GameEvent::GAME_STARTED);
}

void GameViewModel::update() {
	// 1. 更新实体状态
    for (auto& entity : m_entities) {
        entity->update(); // 会自动调用Player, Enemy, Bullet等各自的update方法
    }

    // 2. 碰撞检测

	// 3. 删除无效实体
    m_entities.erase(
        std::remove_if(m_entities.begin(), m_entities.end(),
            [](const std::unique_ptr<Entity>& entity) {
                if (entity->getType() == EntityType::Bullet) {
                    const Bullet* bullet = static_cast<const Bullet*>(entity.get());
                    return !bullet->isValid();
                }
                return false;
            }),
        m_entities.end()
    );

}

const Player* GameViewModel::getPlayer() const {
    return m_player_ptr;
}

const std::vector<std::unique_ptr<Entity>>& GameViewModel::getEntities() const {
    return m_entities;
}

const int* GameViewModel::getCurrentHealth() const {
    if (!m_player_ptr) {
        return nullptr;
    }
    return &m_player_ptr->getHealth();
}

const int* GameViewModel::getMaxHealth() const {
    if (!m_player_ptr) {
        return nullptr;
    }
    return &m_player_ptr->getMaxHealth();
}

void GameViewModel::registerCommand(CommandType type, std::shared_ptr<ICommandBase> command) {
	m_commands[type] = command;
}

void GameViewModel::executeCommand(CommandType type, const std::any& args) {
    if(m_commands.find(type) != m_commands.end()) {
        m_commands[type]->Execute(args);
    }
    else {
        std::cerr << "Command not found: " << static_cast<int>(type) << std::endl;
	}
}

EXCommand GameViewModel::getCommand() {
    return [this](CommandType type, const std::any& args) {
        this->executeCommand(type, args);
    };
}

void GameViewModel::registerAllCommands() {
    // UpdateCommand
    registerCommand(
        CommandType::UpdateCommand,
        std::make_shared<Command<void>>(
            [weak_self = weak_from_this()]() {
                if (auto shared_self = weak_self.lock()) {
                    shared_self->update();
                    shared_self->notify(GameEvent::RENDER_FLUSH);
                }
                else {
                    std::cout << "GameViewModel is expired." << std::endl;
                }
			}));

    // MoveCommand
    registerCommand(
        CommandType::MoveCommand,
        std::make_shared<Command<Direction>>(
            [weak_self = weak_from_this()](Direction dir) {
                // 尝试将 weak_ptr 提升为 shared_ptr
                if (auto shared_self = weak_self.lock()) {
                    if (shared_self->m_player_ptr) {
                        shared_self->m_player_ptr->setDirection(dir);
                    }
                    else {
						std::cout << "Player entity is not initialized." << std::endl;
                    }
                }
                else {
                    std::cout << "GameViewModel is expired." << std::endl;
                }
            }));
    
	// ShootCommand
    registerCommand(
        CommandType::ShootCommand,
        std::make_shared<Command<Direction>>(
            [weak_self = weak_from_this()](Direction dir) {
                if (auto shared_self = weak_self.lock()) {
                    auto& m_player_ptr = shared_self->m_player_ptr;
                    if (!m_player_ptr || m_player_ptr->atCoolDown()) {
                        return;
                    }

                    shared_self->m_entities.push_back(
                        std::make_unique<Bullet>(
                            m_player_ptr->getX() + 20,
                            m_player_ptr->getY() + 20,
                            m_player_ptr,
                            1,  // 子弹伤害
                            10, // 子弹速度
                            dir
                        )
                    );

                    shared_self->notify(GameEvent::PLAY_SOUND_SHOOT);
                }
                else {
                    std::cout << "GameViewModel is expired." << std::endl;
                }
            }));
}
