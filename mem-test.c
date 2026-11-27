#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("First argument needs to be memory test size in bytes\n");
        return 1;
    }

    char* mem_size = argv[1];
    size_t bytes = strtoull(mem_size, NULL, 10);
    void* addr = (void*)0;

    unsigned char* buf = mmap(addr, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(buf == MAP_FAILED)
    {
        printf("memory map failed\n");
        return 1;
    }

    mlock(buf, bytes);

    // write a pattern and read it back
    unsigned char* curr = buf;
    while(curr < buf + bytes)
    {
        *curr = 0xAA; // 10101010
        curr++;
    } 
    curr = buf;
    while(curr < buf + bytes)
    {
        if((*curr) != 0xAA)
        {
            printf("mismatch at byte %zud\n", (size_t) curr);
            printf("go get memory address from /proc/self/pagemap and then ctrl+c to kill this process\n");
            while(1);
        }
        curr++;
    }




}
