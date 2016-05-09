#ifndef __HEAP__
#define __HEAP__

#define HEAP_DEBUG true

typedef int SequenceT;

typedef struct {
    int size;
    SequenceT* data;
} HeapT;

extern HeapT* create_heap(SequenceT* arr, size_t size);
extern void destroy_heap(HeapT* heap);
extern void max_heapify(HeapT* heap, size_t index);
extern void min_heapify(HeapT* heap, size_t index);
extern void build_max_heap(HeapT* heap);
extern void build_max_heap(HeapT* heap);

#endif
