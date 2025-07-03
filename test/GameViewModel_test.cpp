#include <gtest/gtest.h>
#include "viewmodel/GameViewModel.h"
#include "viewmodel/entity/player.h"
#include "viewmodel/entity/enemy.h"
#include "viewmodel/entity/bullet.h"

// GameViewModel测试
class GameViewModelTest : public ::testing::Test {
protected:
    GameViewModel gameViewModel;

    void SetUp() override {
        gameViewModel.startNewGame();
    }
};

// 测试 startNewGame 是否正确初始化了玩家和敌人
TEST_F(GameViewModelTest, StartNewGame) {
    EXPECT_NE(gameViewModel.getPlayer(), nullptr);
    // 初始时有一个玩家和一个敌人
    EXPECT_EQ(gameViewModel.getEntities()->size(), 2);

    int playerCount = 0;
    int enemyCount = 0;
    for (const auto& entity : *gameViewModel.getEntities()) {
        if (entity->getType() == EntityType::Player) {
            playerCount++;
        }
        else if (entity->getType() == EntityType::Enemy) {
            enemyCount++;
        }
    }
    EXPECT_EQ(playerCount, 1);
    EXPECT_EQ(enemyCount, 1);
}

// 测试玩家移动指令
TEST_F(GameViewModelTest, PlayerMovement) {
    const Player* player = gameViewModel.getPlayer();
    float initialX = player->getX();

    // 向右移动
    gameViewModel.executeCommand(CommandType::MoveCommand, std::make_any<std::tuple<Direction>>(Direction::Right));
    gameViewModel.update();

    // 验证玩家的 X 坐标是否发生了变化
    EXPECT_GT(player->getX(), initialX);
}

// 测试发射子弹的指令
TEST_F(GameViewModelTest, ShootBullet) {
    size_t initialEntityCount = gameViewModel.getEntities()->size();

    // 发送向上发射子弹的指令
    gameViewModel.executeCommand(CommandType::ShootCommand, std::make_any<std::tuple<Direction>>(Direction::Up));

    // 验证实体数量
    EXPECT_EQ(gameViewModel.getEntities()->size(), initialEntityCount + 1);

    // 验证子弹数量
    bool bulletFound = false;
    for (const auto& entity : *gameViewModel.getEntities()) {
        if (entity->getType() == EntityType::Bullet) {
            bulletFound = true;
            break;
        }
    }
    EXPECT_TRUE(bulletFound);
}

// 测试玩家死亡事件
TEST_F(GameViewModelTest, PlayerDies) {
    const Player* player = gameViewModel.getPlayer();

    // 创建一个测试用的观察者来监听事件
    class TestObserver : public IObserver {
    public:
        bool playerDied = false;
        void onNotify(GameEvent event) override {
            if (event == GameEvent::PLAYER_DIED) {
                playerDied = true;
            }
        }
    };

    TestObserver observer;
    gameViewModel.addObserver(&observer);

    // 让敌人持续追击
    int cnt = 0;
    while (player->isAlive()) {
        gameViewModel.update();
        ++cnt;
        if(cnt > 10000000) {
            EXPECT_TRUE(cnt < 10000000);
            break;
		}
    }

    EXPECT_TRUE(observer.playerDied);
}