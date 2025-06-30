cmake_minimum_required(VERSION 3.16)

project(IsaacCppGame)

find_package(SFML REQUIRED
    COMPONENTS Graphics Audio
)

add_executable(isaac_game
    code/main.cpp
    # 把你所有的 .cpp 源文件都列在这里
    code/view/gameview.cpp
    # viewmodel/GameViewModel.cpp
 "code/view/gameview.h")

# 为你的项目添加包含目录
target_include_directories(isaac_game PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${CMAKE_CURRENT_SOURCE_DIR}/code/view

)

target_link_libraries(isaac_game PRIVATE 
    SFML::Graphics 
    SFML::Audio
)