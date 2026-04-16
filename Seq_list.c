#include <stdio.h>
#include <stdlib.h>
#include "seq_list.h"

void init(SeqList* list) {
    list->capacity = INIT_CAPACITY;
    list->size = 0;
    list->data = (Element*)malloc(list->capacity * sizeof(Element));
    if (!list->data) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    printf("[init] 초기 용량 %d으로 리스트 생성\n", list->capacity);
}

int isFull(SeqList* list) {
    return list->size == list->capacity;
}

int isEmpty(SeqList* list) {
    return list->size == 0;
}

void grow(SeqList* list) {
    int newCapacity = list->capacity * 2;
    Element* newData = (Element*)realloc(list->data, newCapacity * sizeof(Element));
    if (!newData) {
        fprintf(stderr, "realloc 실패\n");
        exit(EXIT_FAILURE);
    }
    list->data = newData;
    list->capacity = newCapacity;
    printf("[grow] 용량 확장: %d → %d\n", newCapacity / 2, newCapacity);
}

void append(SeqList* list, Element value) {
    if (isFull(list)) {
        grow(list);
    }
    list->data[list->size++] = value;
}

void insert(SeqList* list, int index, Element value) {
    if (index < 0 || index > list->size) {
        printf("[insert] 잘못된 인덱스: %d\n", index);
        return;
    }
    if (isFull(list)) {
        grow(list);
    }
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    list->size++;
}

void delete(SeqList* list, int index) {
    if (isEmpty(list)) {
        printf("[delete] 리스트가 비어 있습니다.\n");
        return;
    }
    if (index < 0 || index >= list->size) {
        printf("[delete] 잘못된 인덱스: %d\n", index);
        return;
    }
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

Element get(SeqList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("[get] 잘못된 인덱스: %d\n", index);
        exit(EXIT_FAILURE);
    }
    return list->data[index];
}

void printList(SeqList* list) {
    printf("리스트 (size=%d, capacity=%d): [", list->size, list->capacity);
    for (int i = 0; i < list->size; i++) {
        printf("%d", list->data[i]);
        if (i < list->size - 1) printf(", ");
    }
    printf("]\n");
}

void destroy(SeqList* list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
    printf("[destroy] 메모리 해제 완료\n");
}
