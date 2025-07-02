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
	auto player = std::make_shared<Player>(400, 300, 5);
	player->setMaxHealth(6);
	player->setHealth(6);
	m_player_ptr = player.get();
	m_entities.push_back(std::move(player));

	// 3. 创建敌人实体
    auto enemy = std::make_shared<Enemy>(ROOM_LEFT, ROOM_TOP, m_player_ptr);
    enemy->setHealth(2);
    enemy->setSpeed(1);
    enemy->setDamage(1);
    m_entities.push_back(std::move(enemy));

    // 4. 发布一个“游戏开始”的事件
    notify(GameEvent::GAME_STARTED);
}

void GameViewModel::update() {
	// 1. 更新实体状态
    for (auto& entity : m_entities) {
        entity->update(); // 会自动调用Player, Enemy, Bullet等各自的update方法
    }

    // 2. 碰撞检测
	collisionDetection();

	// 3. 删除无效实体
    m_entities.erase(
        std::remove_if(m_entities.begin(), m_entities.end(),
            [](const std::shared_ptr<Entity>& entity) {
                if (entity->getType() == EntityType::Bullet) {
                    const Bullet* bullet = static_cast<const Bullet*>(entity.get());
                    return !bullet->isValid();
                } else if (entity->getType() == EntityType::Enemy) {
                    const Enemy* enemy = static_cast<const Enemy*>(entity.get());
                    return !enemy->isAlive();
                }
                return false;
            }),
        m_entities.end()
    );

}

const Player* GameViewModel::getPlayer() const {
    return m_player_ptr;
}

const std::vector<std::shared_ptr<Entity>>* GameViewModel::getEntities() const {
    return &m_entities;
}

const int* GameViewModel::getCurrentHealth() const {
    if (!m_player_ptr) {
        return nullptr;
    }
    return &(m_player_ptr->getHealth());
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

void GameViewModel::updateCommand() {
    update();
    notify(GameEvent::RENDER_FLUSH);
}

void GameViewModel::moveCommand(Direction dir) {
    m_player_ptr->setDirection(dir);
}

void GameViewModel::shootCommand(Direction dir) {
    if (!m_player_ptr || m_player_ptr->atCoolDown()) {
        return;
    }
    m_entities.push_back(
        std::make_shared<Bullet>(
            m_player_ptr->getX() + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2,
            m_player_ptr->getY() + PLAYER_HEIGHT / 2 - BULLET_HEIGHT / 2,
            m_player_ptr,
            1,  // 子弹伤害
            10, // 子弹速度
            dir
        )
    );
    notify(GameEvent::PLAY_SOUND_SHOOT);
}

void GameViewModel::collisionDetection() {
	// 将每两个实体调用方法进行碰撞检测
    for(auto entity1 : m_entities) 
        for (auto entity2 : m_entities) {
            if (entity1 != entity2 && entity1->getBounds().findIntersection(entity2->getBounds())) {
                entity1->collideWith(entity2.get());
            }
        }
}

void GameViewModel::registerAllCommands() {
    // UpdateCommand
    registerCommand(
        CommandType::UpdateCommand,
        std::make_shared<Command<>>([this]() { updateCommand(); }));

    // MoveCommand
    registerCommand(
        CommandType::MoveCommand,
        std::make_shared<Command<Direction>>([this](Direction dir) { moveCommand(dir); }));

    // ShootCommand
    registerCommand(
        CommandType::ShootCommand,
        std::make_shared<Command<Direction>>([this](Direction dir) { shootCommand(dir); }));
}