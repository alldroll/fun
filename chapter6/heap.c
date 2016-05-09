#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"

#define LEFT_CHILD(index) (index << 1) + 1
#define RIGHT_CHILD(index) LEFT_CHILD(index) + 1
#define PARENT(index) (index - 1) >> 1

inline void swap(SequenceT* a, SequenceT* b) {
    SequenceT c = *a;
    *a = *b;
    *b = c;
}

HeapT* create_heap(SequenceT* arr, size_t size) {
    if (arr == NULL) {
        return NULL;
    }

    HeapT* heap = (HeapT*) malloc(sizeof(HeapT));
    if (heap == NULL) {
        return NULL;
    }

    heap->data = (SequenceT*) malloc(sizeof(SequenceT) * size);
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }

    memcpy(heap->data, arr, size * sizeof(SequenceT));
    heap->size = size;
    return heap;
}

void destroy_heap(HeapT* heap) {
    if (heap == NULL) {
        return;
    }

    if (heap->data != NULL) {
        free(heap->data);
    }

    free(heap);
}

void max_heapify(HeapT* heap, size_t index) {
    if (heap == NULL) {
        return;
    }

    size_t largest_index, left_index, right_index;

    while (1) {
        left_index = LEFT_CHILD(index);
        right_index = RIGHT_CHILD(index);
        largest_index = index;

        if (heap->size > left_index &&
            heap->data[left_index] > heap->data[largest_index]
        ) {
            largest_index = left_index;
        }

        if (heap->size > right_index &&
            heap->data[right_index] > heap->data[largest_index]
        ) {
            largest_index = right_index;
        }

        if (largest_index != index) {
            swap(&heap->data[largest_index], &heap->data[index]);
            index = largest_index;
        } else {
            break;
        }
    }
}

void min_heapify(HeapT* heap, size_t index) {
    if (heap == NULL) {
        return;
    }

    size_t left_index = LEFT_CHILD(index);
    size_t right_index = RIGHT_CHILD(index);
    size_t lowest_index = index;

    if (heap->size > left_index &&
        heap->data[left_index] < heap->data[lowest_index]
    ) {
        lowest_index = left_index;
    }

    if (heap->size > right_index &&
        heap->data[right_index] < heap->data[lowest_index]
    ) {
        lowest_index = right_index;
    }

    if (lowest_index != index) {
        swap(&heap->data[lowest_index], &heap->data[index]);
        max_heapify(heap, lowest_index);
    }
}

void build_max_heap(HeapT* heap) {
    if (heap == NULL) {
        return;
    }

    int index = PARENT(heap->size - 1);
    for (; index >= 0; --index) {
        max_heapify(heap, index);
    }
}

void build_min_heap(HeapT* heap) {
    if (heap == NULL) {
        return;
    }

    int index = PARENT(heap->size - 1);
    for (; index >= 0; --index) {
        min_heapify(heap, index);
    }
}

#if HEAP_DEBUG == true
    #include <assert.h>

    int main() {

        assert(LEFT_CHILD(0) == 1);
        assert(RIGHT_CHILD(0) == 2);
        assert(PARENT(1) == 0);

        assert(LEFT_CHILD(1) == 3);
        assert(RIGHT_CHILD(1) == 4);
        assert(PARENT(3) == 1);
        assert(PARENT(4) == 1);

        assert(LEFT_CHILD(2) == 5);
        assert(RIGHT_CHILD(2) == 6);
        assert(PARENT(5) == 2);
        assert(PARENT(6) == 2);

        assert(LEFT_CHILD(3) == 7);
        assert(RIGHT_CHILD(3) == 8);
        assert(PARENT(7) == 3);
        assert(PARENT(8) == 3);

        /* 6_2_1, 6_2_5 */
        {
            SequenceT arr[14] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
            SequenceT expected[14] = {27, 17, 10, 16, 13, 9, 1, 5, 7, 12, 4, 8, 3, 0};
            HeapT* heap = create_heap((SequenceT*) &arr, 14);
            max_heapify(heap, 2);

            size_t i = 0;
            for (; i < heap->size; ++i) {
                assert(expected[i] == heap->data[i]);
            }

            destroy_heap(heap);
        }

        /* 6_2_2 */
        {
            SequenceT arr[5] = {2, 6, 3, 7, 5};
            SequenceT expected[5] = {2, 5, 3, 7, 6};
            HeapT* heap = create_heap((SequenceT*) &arr, 5);
            min_heapify(heap, 1);

            size_t i = 0;
            for (; i < heap->size; ++i) {
                assert(expected[i] == heap->data[i]);
            }

            destroy_heap(heap);
        }

        /* 6_3_1 */
        {
            SequenceT arr[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
            SequenceT expected[10] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
            HeapT* heap = create_heap((SequenceT*) &arr, 10);
            build_max_heap(heap);

            size_t i = 0;
            for (; i < heap->size; ++i) {
                assert(expected[i] == heap->data[i]);
            }

            destroy_heap(heap);
        }

        return 0;
    }
#endif
