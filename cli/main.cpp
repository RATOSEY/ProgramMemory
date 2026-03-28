#include <iostream>
#include <vector>
#include <windows.h> // Додаємо цю бібліотеку
#include "CustomResource.hpp"

int main() {
    // Вмикаємо відображення UTF-8 у консолі Windows
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "--- Старт тестування алокатора ---\n";

    CustomResource my_resource;
    std::pmr::vector<int> numbers(&my_resource);
    
    std::cout << "Додаємо елементи у вектор...\n";
    for (int i = 0; i < 5; ++i) {
        numbers.push_back(i * 10);
    }

    std::cout << "Вектор містить " << numbers.size() << " елементів.\n";
    std::cout << "--- Завершення роботи ---\n";
    


    return 0;
}