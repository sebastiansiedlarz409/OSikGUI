#include "heap.h"
#include "common.h"

#include <stdint.h>

HeapSegment* HeapSegmentFree;

void InitHeap(uint64_t offset, uint64_t size){
    GetSystemContext()->heapAddress=offset;
    GetSystemContext()->heapSize=size;

    HeapSegmentFree = (HeapSegment*)offset;
    HeapSegmentFree->free = 0;
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
            HeapSegment* HeapSegmentNew = (uint8_t*)HeapSegmentCurrent+sizeof(HeapSegment)+size;

            //decrease size
            HeapSegmentNew->size = HeapSegmentCurrent->size-sizeof(HeapSegment)+size;

            HeapSegmentCurrent->next = HeapSegmentNew;
            HeapSegmentCurrent->nextFree = HeapSegmentNew;
            HeapSegmentCurrent->size = size; //this segment is returned so
            HeapSegmentCurrent->free = 1; //mark as taken

            HeapSegmentNew->prev = HeapSegmentCurrent;
            HeapSegmentNew->prevFree = HeapSegmentCurrent->prevFree;
            HeapSegmentNew->next = HeapSegmentCurrent->next;
            HeapSegmentNew->nextFree = HeapSegmentCurrent->nextFree;
            HeapSegmentNew->free = 0;
        }

        HeapSegmentCurrent = HeapSegmentCurrent->nextFree;
        HeapSegmentFree = HeapSegmentCurrent;

        return (void*)HeapSegmentCurrent->prev;
    }
    else{
        return 0;
    }

}