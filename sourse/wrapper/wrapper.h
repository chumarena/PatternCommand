#pragma once
#include "Interface_Command.h"
#include <vector>
#include <string>
#include <stdexcept>

template<typename Obj, typename Ret, typename ... Args>
class Wrapper : public Interface_command {
public:
    Wrapper(Obj* object, Ret(Obj::* method)(Args ...), const std::map<std::string, int>& args_default) 
        : object(object), method(method) {
        for (const auto& [key, value] : args_default) {
            argument_names.push_back(key);
        }
    }

    int execute(const std::map<std::string, int>& args) override {
        if (args.size() != sizeof...(Args)) {
            throw std::runtime_error("Количество аргументов не совпадает. Ожидалось: " + std::to_string(sizeof...(Args)));
        }
        return call_function(args, std::make_index_sequence<sizeof...(Args)>{});
    }

private:
    Obj* object;
    Ret(Obj::* method)(Args...);
    std::vector<std::string> argument_names;

    template<std::size_t... Is>
    int call_function(const std::map<std::string, int>& args, std::index_sequence<Is...>) {
        for (const auto& name : argument_names) {
            if (args.find(name) == args.end()) {
                throw std::out_of_range("Недостающий аргумент: " + name);
            }
        }
        return (object->*method)(args.at(argument_names[Is])...);
    }
};