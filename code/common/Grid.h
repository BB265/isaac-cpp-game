#pragma once

#include "MetaData.h"
#include <SFML/System/Vector2.hpp>

// 房间大小：13格长×7格宽
const int GRID_COLS = 13;
const int GRID_ROWS = 7;

class Grid {
public:
    /**
     * @brief 将格子坐标转换为屏幕像素坐标
     * @param gridX 格子的列索引 (0-12)
     * @param gridY 格子的行索引 (0-6)
     * @return sf::Vector2f 包含屏幕(x, y)坐标的向量
     */
    static sf::Vector2f getPixelPosition(int gridX, int gridY) {
        const float room_pixel_width = ROOM_RIGHT - ROOM_LEFT;
        const float room_pixel_height = ROOM_BOTTOM - ROOM_TOP;

        const float cell_width = room_pixel_width / GRID_COLS;
        const float cell_height = room_pixel_height / GRID_ROWS;

        // 计算目标格子中心点的像素坐标
        float pixel_x = ROOM_LEFT + gridX * cell_width + (cell_width / 2.f);
        float pixel_y = ROOM_TOP + gridY * cell_height + (cell_height / 2.f);
        pixel_x -= (ENEMY_WIDTH / 2.f);
        pixel_y -= (ENEMY_HEIGHT / 2.f);

        return sf::Vector2f(pixel_x, pixel_y);
    }
};