#include "include/heap.h"
#include "include/common.h"

#include <stdint.h>

HeapSegment* HeapSegmentFree;

void InitHeap(uint64_t offset, uint64_t size){
    GetSystemContext()->heapAddress=offset;
    GetSystemContext()->heapSize=size;

    HeapSegmentFree = (HeapSegment*)offset;
    HeapSegmentFree->free = 1;
    HeapSegmentFree->next = 0;
    HeapSegmentFree->prev = 0;
    HeapSegmentFree->nextFree = 0;
    HeapSegmentFree->prevFree = 0;

    if(size <= sizeof(HeapSegment)){
        //create heap with min 100 byte space for allocation
        HeapSegmentFree->size = sizeof(HeapSegment) + 100;
    }
    else{
        HeapSegmentFree->size = size - sizeof(HeapSegment);
    }
}

void* MallocHeap(uint64_t size){

    HeapSegment* HeapSegmentCurrent = HeapSegmentFree;

    if(HeapSegmentCurrent->size > size){
        //check if we have enough space for next segment
        if(size+sizeof(HeapSegment) <= HeapSegmentCurrent->size){
            //move segment pointer
            HeapSegment* HeapSegmentNew = (HeapSegment*)((uint8_t*)HeapSegmentCurrent+sizeof(HeapSegment)+size);

            //decrease size
            HeapSegmentNew->size = HeapSegmentCurrent->size-sizeof(HeapSegment)+size;

            HeapSegmentCurrent->next = HeapSegmentNew;
            HeapSegmentCurrent->nextFree = HeapSegmentNew;
            HeapSegmentCurrent->size = size; //this segment is returned so
            HeapSegmentCurrent->free = 0; //mark as taken

            HeapSegmentNew->prev = HeapSegmentCurrent;
            HeapSegmentNew->prevFree = HeapSegmentCurrent->prevFree;
            HeapSegmentNew->next = HeapSegmentCurrent->next;
            HeapSegmentNew->nextFree = HeapSegmentCurrent->nextFree;
            HeapSegmentNew->free = 1;
        }

        HeapSegmentCurrent = HeapSegmentCurrent->nextFree;
        HeapSegmentFree = HeapSegmentCurrent;

        GetSystemContext()->heapNextFree = (uint64_t)HeapSegmentFree;

        return (void*)((uint8_t*)HeapSegmentCurrent->prev+sizeof(HeapSegment));
    }
    else{
        return 0;
    }

}

void ConcatSegments(HeapSegment* a, HeapSegment* b){
    if (a == 0 || b == 0)
        return;

    if(a < b){
        a->size += b->size + sizeof(HeapSegment);
        a->next = b->next;
        a->nextFree = b->nextFree;
        b->next->prev = a;
        b->next->prevFree = a;
        b->nextFree->prevFree = a;
    }
    else{
        b->size += a->size + sizeof(HeapSegment);
        b->next = a->next;
        b->nextFree = a->nextFree;
        a->next->prev = b;
        a->next->prevFree = b;
        a->nextFree->prevFree = b;
    }
}

void FreeHeap(void* ptr){
    HeapSegment* HeapSegmentCurrent = ((HeapSegment*)((uint8_t*)ptr-sizeof(HeapSegment)));

    HeapSegmentCurrent->free = 1;

    if(HeapSegmentCurrent < HeapSegmentFree){
        HeapSegmentFree = HeapSegmentCurrent;
    }

    if(HeapSegmentCurrent->nextFree != 0){
        if(HeapSegmentCurrent->nextFree->prevFree < HeapSegmentCurrent){
            HeapSegmentCurrent->nextFree->prevFree = HeapSegmentCurrent;
        }
    }

    if(HeapSegmentCurrent->prevFree != 0){
        if(HeapSegmentCurrent->prevFree->nextFree > HeapSegmentCurrent){
            HeapSegmentCurrent->prevFree->nextFree = HeapSegmentCurrent;
        }
    }

    if(HeapSegmentCurrent->next != 0){
        HeapSegmentCurrent->next->prev = HeapSegmentCurrent;
        if(HeapSegmentCurrent->next->free)
            ConcatSegments(HeapSegmentCurrent, HeapSegmentCurrent->next);
    }

    if(HeapSegmentCurrent->prev != 0){
        HeapSegmentCurrent->prev->next = HeapSegmentCurrent;
        if(HeapSegmentCurrent->prev->free)
            ConcatSegments(HeapSegmentCurrent, HeapSegmentCurrent->prev);
    }

    GetSystemContext()->heapNextFree = (uint64_t)HeapSegmentFree;
}