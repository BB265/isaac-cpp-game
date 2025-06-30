// common/Commands.h

#pragma once

#include <functional>
#include "Direction.h"
#include<SFML/Graphics.hpp>
/**
 * @brief 简单命令类型
 */
using SimpleCommand = std::function<void()>;

/**
 * @brief 移动命令类型
 * @param Direction 移动方向
 */
using MoveCommand = std::function<void(Direction)>;

/**
 * @brief 射击命令类型
 * @param sf::Vector2f 射击方向
 */
using ShootCommand = std::function<void(sf::Vector2f)>;