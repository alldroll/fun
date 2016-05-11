#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "heap.h"

#define HEAP_DEBUG false

typedef struct {
    size_t size;
    size_t allocated_size;
    SequenceT* data;
} HeapImplT;

#define LEFT_CHILD(index) (index << 1) + 1
#define RIGHT_CHILD(index) LEFT_CHILD(index) + 1
#define PARENT(index) (index - 1) >> 1

inline static void swap(SequenceT* a, SequenceT* b) {
    SequenceT c = *a;
    *a = *b;
    *b = c;
}

static int allocate_policy(HeapImplT* heap) {
    /* TODO implement me!*/
    return 0;
}

HeapT* create_heap(SequenceT* arr, size_t size) {
    if (arr == NULL) {
        return NULL;
    }

    HeapImplT* heap = (HeapImplT*) malloc(sizeof(HeapImplT));
    if (heap == NULL) {
        return NULL;
    }

    heap->data = (SequenceT*) malloc(sizeof(SequenceT) * size);
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }

    memcpy(heap->data, arr, size * sizeof(SequenceT));
    heap->allocated_size = size;
    heap->size = size;
    return (HeapT*) heap;
}

void destroy_heap(HeapT* h) {
    if (h == NULL) {
        return;
    }

    HeapImplT* heap = (HeapImplT*) h;
    if (heap->data != NULL) {
        free(heap->data);
    }

    free(heap);
}

int get_heap_size(HeapT* h) {
    if (h == NULL) {
        return - 1;
    }

    HeapImplT* heap = (HeapImplT*) h;
    return heap->size;
}

SequenceT* get_heap_data(HeapT* h) {
    if (h == NULL) {
        return NULL;
    }

    HeapImplT* heap = (HeapImplT*) h;
    return heap->data;
}

void max_heapify(HeapT* h, size_t index) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
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

        if (largest_index == index) {
            break;
        }

        swap(&heap->data[largest_index], &heap->data[index]);
        index = largest_index;
    }
}

void min_heapify(HeapT* h, size_t index) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
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
        max_heapify(h, lowest_index);
    }
}

void build_max_heap(HeapT* h) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
    int index = PARENT(heap->size - 1);
    for (; index >= 0; --index) {
        max_heapify(h, index);
    }
}

void build_min_heap(HeapT* h) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
    int index = PARENT(heap->size - 1);
    for (; index >= 0; --index) {
        min_heapify(h, index);
    }
}

void heapsort(SequenceT* arr, size_t size) {
    if (arr == NULL || size <= 1) {
        return;
    }

    HeapT* h = create_heap(arr, size);
    HeapImplT* heap = (HeapImplT*) h;
    assert(h != NULL);

    build_max_heap(h);
    size_t index = size - 1;
    for (; index > 0; --index) {
        swap(&heap->data[index], &heap->data[0]);
        --heap->size;
        max_heapify(h, 0);
    }

    memcpy(arr, heap->data, size * sizeof(SequenceT));
    destroy_heap(h);
}

SequenceT heap_maximum(HeapT* h) {
    HeapImplT* heap = (HeapImplT*) h;
    assert(heap != NULL && heap->size != 0);
    return heap->data[0];
}

SequenceT heap_extract_max(HeapT* h) {
    HeapImplT* heap = (HeapImplT*) h;
    assert(heap != NULL && heap->size != 0);

    SequenceT max = heap_maximum(h);
    heap->data[0] = heap->data[heap->size - 1];
    --heap->size;
    max_heapify(h, 0);
    return max;
}

void heap_increase_key(HeapT* h, size_t index, SequenceT key) {
    HeapImplT* heap = (HeapImplT*) h;
    assert(heap != NULL && heap->size > index);
    assert(key > heap->data[index]);

    heap->data[index] = key;
    size_t parent_index = PARENT(index);
    while (index > 0 && heap->data[parent_index] < heap->data[index]) {
        swap(&heap->data[index], &heap->data[parent_index]);
        index = parent_index;
    }
}

#if HEAP_DEBUG == true

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

#define HEAP_ASSERT_DATA_EQUALS(expected, h)         \
    {                                                \
        assert(h != NULL);                           \
        HeapImplT* heapImp = (HeapImplT*) h;         \
        size_t i = 0;                                \
        for (; i < heapImp->size; ++i) {             \
            assert(expected[i] == heapImp->data[i]); \
        }                                            \
    }

        /* 6_2_1, 6_2_5 */
        {
            SequenceT arr[14] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
            SequenceT expected[14] = {27, 17, 10, 16, 13, 9, 1, 5, 7, 12, 4, 8, 3, 0};
            HeapT* heap = create_heap((SequenceT*) &arr, 14);
            max_heapify(heap, 2);

            HEAP_ASSERT_DATA_EQUALS(expected, heap);

            destroy_heap(heap);
        }

        /* 6_2_2 */
        {
            SequenceT arr[5] = {2, 6, 3, 7, 5};
            SequenceT expected[5] = {2, 5, 3, 7, 6};
            HeapT* heap = create_heap((SequenceT*) &arr, 5);
            min_heapify(heap, 1);

            HEAP_ASSERT_DATA_EQUALS(expected, heap);

            destroy_heap(heap);
        }

        /* 6_3_1 */
        {
            SequenceT arr[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
            SequenceT expected[10] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
            HeapT* heap = create_heap((SequenceT*) &arr, 10);
            build_max_heap(heap);

            HEAP_ASSERT_DATA_EQUALS(expected, heap);

            destroy_heap(heap);
        }

        {
            SequenceT arr[9] = {5, 13, 2, 25, 7, 17, 20, 8, 4};
            SequenceT expected[9] = {2, 4, 5, 7, 8, 13, 17, 20, 25};

            heapsort(arr, 9);
            size_t i = 0;
            for (; i < 9; ++i) {
                assert(expected[i] == arr[i]);
            }
        }

        return 0;
    }
#endif
