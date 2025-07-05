// common/Commands.h

#pragma once
#include <functional>
#include <any>
#include <tuple>
#include <iostream>
#include <string>
enum class CommandType
{
    MoveCommand,
    ShootCommand,
    UpdateCommand,
    StartGameCommand
};

using EXCommand = std::function<void(CommandType, const std::any&)>;

class ICommandBase {
public:
    virtual ~ICommandBase() = default;

    // 执行命令的接口，接收 std::any 类型的参数
    virtual void Execute(const std::any& args) = 0;
};

template <typename... Args>
class Command : public ICommandBase {
public:
    using ArgumentsTuple = std::tuple<Args...>;
    using CommandFunction = std::function<void(Args...)>;

    explicit Command(CommandFunction func) : m_function(func) {}

    void Execute(const std::any& args) override {
        // 将 std::any 转换为 std::tuple<Args...>
        if constexpr (sizeof...(Args) == 0) {
            // 如果没有参数，直接调用函数
            m_function();
        }
        else {
            if (args.type() == typeid(ArgumentsTuple)) {
                auto tupleArgs = std::any_cast<ArgumentsTuple>(args);
                // 使用 std::apply 解包 tuple 并调用函数
                std::apply(m_function, tupleArgs);
            }
            else {
                throw std::invalid_argument("Invalid argument type for command execution.");
            }
        }
    }

private:
    CommandFunction m_function;
};
