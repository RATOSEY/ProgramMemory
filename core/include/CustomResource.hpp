#pragma once
#include <memory_resource>
#include <cstddef>
#include <array>
#include <atomic> // Використовуємо атомарні операції замість м'ютексів

class CustomResource : public std::pmr::memory_resource {
private:
    std::pmr::memory_resource* upstream;
    std::array<std::byte, 1024> buffer; 
    
    // Тепер це атомарна змінна. Процесор гарантує безпечний доступ до неї!
    std::atomic<std::size_t> offset{0};             

public:
    CustomResource();

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};