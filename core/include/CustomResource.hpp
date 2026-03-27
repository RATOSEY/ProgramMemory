#pragma once
#include <memory_resource>
#include <cstddef>

class CustomResource : public std::pmr::memory_resource {
private:
    std::pmr::memory_resource* upstream;

public:
    CustomResource();

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};