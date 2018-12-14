#include "stdio.h"
#include "unistd.h"
#include "inttypes.h"

uintptr_t virt2phys(uintptr_t virtAddr)
{
    FILE *pageMap;
    intptr_t physAddr = 0;
    long pageSize = sysconf(_SC_PAGESIZE);
    uint64_t offset = ((virtAddr / pageSize) * sizeof(uint64_t));
    uint64_t buf;

    if ((pageMap = fopen("/proc/self/pagemap", "r")))
    {
        if (lseek(fileno(pageMap), offset, SEEK_SET) == offset)
        {
            if (fread(&buf, sizeof(uint64_t), 1, pageMap))
            {
                if (buf & (1ULL << 63))
                {
                    // Mask with page frame number
                    physAddr = (buf & ((1ULL << 54) - 1));
                    physAddr = (physAddr * pageSize);
                    // add offset within page
                    physAddr = (physAddr | (virtAddr & (pageSize - 1)));
                }
            }
        }
        fclose(pageMap);
    }
    return physAddr;
}

