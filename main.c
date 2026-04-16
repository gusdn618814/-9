#include <stdio.h>
#include "seq_list.h"

int main(void) {
    SeqList list;
    init(&list);

    printf("\n--- append 테스트 (초기 용량 %d 초과 시 realloc 발생) ---\n", INIT_CAPACITY);
    for (int i = 1; i <= 10; i++) {
        printf("append(%2d) → ", i);
        append(&list, i);
        printList(&list);
    }

    printf("\n--- insert 테스트: 인덱스 2에 99 삽입 ---\n");
    insert(&list, 2, 99);
    printList(&list);

    printf("\n--- delete 테스트: 인덱스 2 삭제 ---\n");
    delete(&list, 2);
    printList(&list);

    printf("\n--- get 테스트 ---\n");
    printf("get(0) = %d\n", get(&list, 0));
    printf("get(4) = %d\n", get(&list, 4));
    printf("get(9) = %d\n", get(&list, 9));

    printf("\n");
    destroy(&list);
    return 0;
}
