#include "CustomResource.hpp"

CustomResource::CustomResource() : upstream(std::pmr::new_delete_resource()) {}

void* CustomResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    // Читаємо поточне значення offset
    std::size_t current_offset = offset.load(std::memory_order_relaxed);
    std::size_t padding;
    std::size_t new_offset;

    // Lock-free цикл (CAS - Compare-And-Swap)
    do {
        padding = (alignment - (current_offset % alignment)) % alignment;
        new_offset = current_offset + bytes + padding;

        // Якщо пул переповнений, йдемо до ОС
        if (new_offset > buffer.size()) {
            return upstream->allocate(bytes, alignment);
        }
        
    // Намагаємося оновити offset. Якщо хтось нас випередив, 
    // current_offset автоматично оновиться до актуального, і цикл повториться.
    } while (!offset.compare_exchange_weak(current_offset, new_offset, 
                                           std::memory_order_acquire, 
                                           std::memory_order_relaxed));

    return &buffer[current_offset + padding];
}

void CustomResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    // Оскільки ми не звільняємо окремі шматочки в цьому пулі, 
    // тут навіть не потрібна синхронізація!
    if (p >= buffer.data() && p < buffer.data() + buffer.size()) {
        return; 
    }
    upstream->deallocate(p, bytes, alignment);
}

bool CustomResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}