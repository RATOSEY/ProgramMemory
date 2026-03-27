#include "CustomResource.hpp"
#include <iostream>

// Використовуємо стандартний алокатор системи як базовий
CustomResource::CustomResource() : upstream(std::pmr::new_delete_resource()) {}

void* CustomResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    std::cout << "[ALLOC] Запитано " << bytes << " байт (вирівнювання " << alignment << ")\n";
    return upstream->allocate(bytes, alignment);
}

void CustomResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    std::cout << "[FREE] Звільнено " << bytes << " байт\n";
    upstream->deallocate(p, bytes, alignment);
}

bool CustomResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}