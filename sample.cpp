#include <iostream>
#include <memory>

#include "virt2phys.hpp"

int main()
{
    auto tmpMem = std::make_unique<uint64_t>(10);

    if (tmpMem == nullptr)
    {
        std::cout << "Allocation failed !" << std::endl;
        return 1;
    }

    uintptr_t physAddr = virt2phys(reinterpret_cast<uintptr_t>(tmpMem.get()));

    if (physAddr == 0)
    {
        std::cout << "Translation failed !" << std::endl;
        return 1;
    }

    std::cout << "virtual address  : " << tmpMem.get() << std::endl;
    std::cout << "physical address : " << physAddr << std::endl;

    return 0;
}

