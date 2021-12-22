#pragma once

#include <stdint.h>

struct _HeapSegment{
    uint64_t size;
    uint8_t free;
    struct _HeapSegment* prev;
    struct _HeapSegment* next;
    struct _HeapSegment* prevFree;
    struct _HeapSegment* nextFree;
} __attribute__((packed)) ;

typedef struct _HeapSegment HeapSegment;

void InitHeap(uint64_t offset, uint64_t size);
void* MallocHeap(uint64_t size);