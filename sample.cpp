#include <iostream>
#include <stdlib.h>
#include "virt2phys.hpp"

int main()
{
    uintptr_t virtAddr = reinterpret_cast<uintptr_t>(malloc(1024));
    std::cout << "virtual address  : " << virtAddr << std::endl;

    // 物理アドレス取得
    uintptr_t physAddr = virt2phys(virtAddr);

    std::cout << "physical address : " << physAddr << std::endl;

    return 0;
}

