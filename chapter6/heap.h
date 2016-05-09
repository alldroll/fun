#ifndef __HEAP__
#define __HEAP__

#include <stddef.h>

typedef int SequenceT;

typedef struct {
    size_t size;
    size_t allocated_size;
    SequenceT* data;
} HeapT;

extern HeapT* create_heap(SequenceT* arr, size_t size);
extern void destroy_heap(HeapT* heap);
extern void max_heapify(HeapT* heap, size_t index);
extern void min_heapify(HeapT* heap, size_t index);
extern void build_max_heap(HeapT* heap);
extern void build_max_heap(HeapT* heap);
extern void heapsort(SequenceT* arr, size_t size);
extern SequenceT heap_maximum(HeapT* heap);
extern SequenceT heap_extract_max(HeapT* heap);
void heap_increase_key(HeapT* heap, size_t index, SequenceT key);

#endif
