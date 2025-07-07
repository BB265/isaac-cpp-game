cmake_minimum_required(VERSION 3.16)
project(IsaacCppGame)
find_package(SFML REQUIRED
    COMPONENTS Graphics Audio
)
enable_testing()

file(GLOB SOURCES 
    "code/view/*.cpp"
    "code/common/*.cpp"
    "code/viewmodel/*.cpp"
    "code/viewmodel/entity/*.cpp"
    "code/viewmodel/room/*.cpp"
    "code/app/*.cpp"
)
add_executable(isaac_game ${SOURCES} "code/main.cpp" )
# 为你的项目添加包含目录
target_include_directories(isaac_game PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${CMAKE_CURRENT_SOURCE_DIR}/code/view
    ${CMAKE_CURRENT_SOURCE_DIR}/code/common
    ${CMAKE_CURRENT_SOURCE_DIR}/code/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/code/viewmodel/entity
    ${CMAKE_CURRENT_SOURCE_DIR}/code/viewmodel/room
    ${CMAKE_CURRENT_SOURCE_DIR}/code/app
)

target_link_libraries(isaac_game PRIVATE 
    SFML::Graphics 
    SFML::Audio
)
# 设置测试目录
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

# 添加测试支持（Google Test）
find_package(GTest REQUIRED)

# 测试目标
file(GLOB TEST_SOURCES 
"${TEST_DIR}/*.cpp"
${SOURCES}

)
add_executable(isaac_tests ${TEST_SOURCES})

# 添加测试目标的包含目录
target_include_directories(isaac_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${CMAKE_CURRENT_SOURCE_DIR}/code/view
    ${CMAKE_CURRENT_SOURCE_DIR}/code/common
    ${CMAKE_CURRENT_SOURCE_DIR}/code/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/code/viewmodel/entity
    ${CMAKE_CURRENT_SOURCE_DIR}/code/viewmodel/room
    ${CMAKE_CURRENT_SOURCE_DIR}/code/app
    ${TEST_DIR}
)

# 链接 Google Test 和 SFML
target_link_libraries(isaac_tests PRIVATE 
    GTest::gtest 
    GTest::gtest_main 
    SFML::Graphics 
    SFML::Audio
)

# 添加到 CTest 测试套件
add_test(NAME GameTests COMMAND isaac_tests)