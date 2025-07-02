cmake_minimum_required(VERSION 3.16)

project(IsaacCppGame)

find_package(SFML REQUIRED
    COMPONENTS Graphics Audio
)

file(GLOB SOURCES 
    "code/*.cpp" 
    "code/view/*.cpp"
    "code/common/*.cpp"
    "code/viewmodel/*.cpp"
    "code/viewmodel/entity/*.cpp"
    "code/app/*.cpp"
)
add_executable(isaac_game ${SOURCES} )
# 为你的项目添加包含目录
target_include_directories(isaac_game PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${CMAKE_CURRENT_SOURCE_DIR}/code/view
    ${CMAKE_CURRENT_SOURCE_DIR}/code/common
    ${CMAKE_CURRENT_SOURCE_DIR}/code/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/code/viewmodel/entity
    ${CMAKE_CURRENT_SOURCE_DIR}/code/app
)

target_link_libraries(isaac_game PRIVATE 
    SFML::Graphics 
    SFML::Audio
)