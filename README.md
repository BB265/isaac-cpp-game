# Isaac C++ Game

这是一个使用 C++ 和 SFML 制作的简单游戏，灵感来源于《以撒的结合》(The Binding of Isaac)。

## ✨ 功能

  * **玩家控制**: 通过键盘控制角色移动和发射子弹。
  * **敌人**: 敌人会自动追击玩家。
  * **随机房间**: 地图由随机生成的房间组成，每个房间都有不同的敌人配置。
  * **生命系统**: 玩家和敌人都有生命值，玩家生命值耗尽则游戏结束。
  * **MVVM 架构**: 项目采用 Model-View-ViewModel 设计模式（Model层合并进ViewModel里），分离了游戏逻辑和渲染。
  * **设计模式**: 命令模式来处理用户输入，通知模式来处理游戏事件。

## 🛠️ 技术栈

  * **语言**: C++
  * **图形库**: SFML
  * **构建系统**: CMake
  * **依赖管理**: vcpkg
  * **测试框架**: Google Test

## 🚀 如何开始

### 环境要求

  * C++ 编译器 (支持 C++17)
  * CMake
  * vcpkg

### 步骤

1.  **克隆仓库**

    ```bash
    git clone https://github.com/BB265/isaac-cpp-game.git
    cd isaac-cpp-game
    ```

2.  **安装依赖**

    项目使用 vcpkg 管理依赖项。请根据 [vcpkg 官方文档](https://github.com/microsoft/vcpkg) 进行安装和集成。然后，在项目根目录运行以下命令来安装所需的库：

    ```bash
    vcpkg install
    ```

3.  **构建项目**

    ```bash
    cmake --preset=default
    cmake --build build
    ```

4.  **运行游戏**

    ```bash
    ./build/isaac_game
    ```

 注：你可以通过CMake直接安装vcpkg依赖。

## 🧪 运行测试

项目包含一套使用 Google Test 编写的单元测试。

1.  **构建测试**

    CMake 会自动配置测试目标。

2.  **运行测试**

    ```bash
    cd build
    ctest --output-on-failure
    ```

    您也可以直接运行 `isaac_tests` 可执行文件。

## 📁 项目结构

```
isaac-cpp-game/
├── .github/workflows/      # CI/CD 配置文件
├── code/
│   ├── app/                # 应用主逻辑
│   ├── assets/             # 游戏资源
│   ├── common/             # 通用组件
│   ├── view/               # View层
│   └── viewmodel/          # ViewModel层
├── test/                   # 测试代码
├── CMakeLists.txt          # CMake 构建脚本
├── vcpkg.json              # vcpkg 依赖配置文件
└── README.md
```

## 🤝 贡献

欢迎通过 Pull Requests 提交您的贡献。对于重大的改动，请先开一个 issue 来讨论您想要改变的内容。

## 📄 许可证

本项目采用 MIT 许可证。


注：本文档的部分内容是在 AI 的辅助下润色的。
-----