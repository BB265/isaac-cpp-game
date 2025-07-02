#include <gtest/gtest.h>
#include "../code/view/gameview.h"

// 测试构造函数是否正确初始化窗口
TEST(GameViewTest, ConstructorTest) {
    gamewindow window;
    EXPECT_TRUE(window.window.isOpen());
}

// 测试 AssetManager 的纹理加载
TEST(AssetManagerTest, TextureLoadingTest) {
    AssetManager& manager = AssetManager::get_instance();
    const auto textures = manager.get_textures();

    EXPECT_NE(textures.find("background"), textures.end());
    EXPECT_NE(textures.find("isaac"), textures.end());
    EXPECT_NE(textures.find("heart"), textures.end());
    EXPECT_NE(textures.find("half_heart"), textures.end());
    EXPECT_NE(textures.find("empty_heart"), textures.end());
    EXPECT_NE(textures.find("enemy"), textures.end());
    EXPECT_NE(textures.find("tear"), textures.end());
    EXPECT_NE(textures.find("background"), textures.end());
}

// 测试方向判断函数
TEST(GameViewTest, JudgeDirectionTest) {
    gamewindow window;
    EXPECT_EQ(window.judgeDirection(1, 1), Direction::None);
    EXPECT_EQ(window.judgeDirection(2, 1), Direction::Up);
    EXPECT_EQ(window.judgeDirection(0, 0), Direction::DownLeft);
    EXPECT_EQ(window.judgeDirection(0, 1), Direction::Down);
    EXPECT_EQ(window.judgeDirection(1, 0), Direction::Left);
    EXPECT_EQ(window.judgeDirection(0, 2), Direction::DownRight);
    EXPECT_EQ(window.judgeDirection(1, 2), Direction::Right);
    EXPECT_EQ(window.judgeDirection(2, 0), Direction::UpLeft);
    EXPECT_EQ(window.judgeDirection(2, 2), Direction::UpRight);
}