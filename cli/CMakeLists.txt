add_executable(optimizer_cli main.cpp)
# Лінкуємо нашу бібліотеку до цього файлу
target_link_libraries(optimizer_cli PRIVATE core_lib)