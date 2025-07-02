#include <gtest/gtest.h>
#include "../code/view/gameview.h"

// ���Թ��캯���Ƿ���ȷ��ʼ������
TEST(GameViewTest, ConstructorTest) {
    gamewindow window;
    EXPECT_TRUE(window.window.isOpen());
}

// ���� AssetManager ���������
TEST(AssetManagerTest, TextureLoadingTest) {
    AssetManager& manager = AssetManager::get_instance();
    const auto textures = manager.get_textures();

    EXPECT_NE(textures.find("background"), textures.end());
    EXPECT_NE(textures.find("isaac"), textures.end());
    EXPECT_NE(textures.find("heart"), textures.end());
}

// ���Է����жϺ���
TEST(GameViewTest, JudgeDirectionTest) {
    gamewindow window;
    EXPECT_EQ(window.judgeDirection(1, 1), Direction::UpRight);
    EXPECT_EQ(window.judgeDirection(2, 1), Direction::Up);
    EXPECT_EQ(window.judgeDirection(0, 0), Direction::None);
}