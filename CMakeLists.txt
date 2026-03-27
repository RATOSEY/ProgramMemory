cmake_minimum_required(VERSION 3.15)
project(MemoryOptimizer CXX)

# Встановлюємо стандарт C++17 (це обов'язково для std::pmr)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Підключаємо наші папки
add_subdirectory(core)
add_subdirectory(cli)