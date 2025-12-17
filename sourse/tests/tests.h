#pragma once
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>
#include "../subject/subject.h"
#include "../wrapper/wrapper.h"
#include "../engine/engine.h"

#ifdef _WIN32
#include <windows.h>
#endif

inline void print_test_result(int num, const std::string& name, bool success, const std::string& msg = "") {
    std::cout << "[Тест " << num << "] " << name << ": " 
              << (success ? "ПРОЙДЕН" : "ПРОВАЛ");
    if (!msg.empty()) std::cout << " (" << msg << ")";
    std::cout << std::endl;
}

inline void run_all_tests() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    subject subj;
    engine eng;

    Wrapper wrapper_f3(&subj, &subject::function, {{"arg1", 0}, {"arg2", 0}});
    eng.register_command(&wrapper_f3, "command1");

    Wrapper wrapper_zero(&subj, &subject::zero, {});
    eng.register_command(&wrapper_zero, "get_const");

    Wrapper wrapper_sum5(&subj, &subject::sum_5, {{"a",0}, {"b",0}, {"c",0}, {"d",0}, {"e",0}});
    eng.register_command(&wrapper_sum5, "sum5");

    std::cout << "Тесты\n" << std::endl;

    //Sum
    int r1 = eng.execute("command1", {{"arg1", 10}, {"arg2", 20}});
    print_test_result(1, "Сложение 2 чисел", r1 == 30, "Результат: " + std::to_string(r1));

    //Zero
    int r2 = eng.execute("get_const", {});
    print_test_result(2, "Метод без аргументов", r2 == 12345, "Результат: " + std::to_string(r2));

    //Sum5
    int r3 = eng.execute("sum5", {{"a",1}, {"b",1}, {"c",1}, {"d",1}, {"e",1}});
    print_test_result(3, "Сложение 5 чисел", r3 == 5, "Результат: " + std::to_string(r3));

    //Ошибка команды
    try {
        eng.execute("unknown", {});
        print_test_result(4, "Неверная команда", false);
    } catch (const std::runtime_error& e) {
        print_test_result(4, "Неверная команда", true, e.what());
    }

    //Ошибка количества аргументов
    try {
        eng.execute("command1", {{"arg1", 1}});
        print_test_result(5, "Кол-во аргументов", false);
    } catch (const std::runtime_error& e) {
        print_test_result(5, "Кол-во аргументов", true, e.what());
    }

    //Ошибка имени аргумента
    try {
    eng.execute("command1", {{"wrong", 10}, {"arg2", 20}}); 
    print_test_result(6, "Имена аргументов", false, "Ошибка не поймана");
    } catch (const std::out_of_range& e) {
    print_test_result(6, "Имена аргументов", true, e.what());
    } 

    std::cout << "\nТестирование завершено" << std::endl;
}