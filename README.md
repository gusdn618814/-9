# 순차 리스트 (Sequential List with realloc)

배열 기반 순차 리스트를 C언어로 구현하였으며,  
포화 상태(Full) 발생 시 `realloc`을 사용해 배열을 동적으로 확장합니다.

---

## 파일 구조

```
├── seq_list.h   # 구조체 정의 및 함수 선언
├── seq_list.c   # 함수 구현
├── main.c       # 테스트 코드
└── README.md    # 프로젝트 설명
```

---

## 컴파일 및 실행

```bash
gcc main.c seq_list.c -o seq_list
./seq_list
```

---

## 자료구조 설명

### SeqList 구조체 (`seq_list.h`)

```c
typedef struct {
    Element *data;   // 동적 배열 포인터 (malloc/realloc으로 관리)
    int size;        // 현재 저장된 요소 수
    int capacity;    // 현재 배열의 최대 용량
} SeqList;
```

- 초기 용량: `INIT_CAPACITY = 4`
- 포화 상태 도달 시 `realloc`으로 용량을 **2배** 확장

---

## 핵심 동작: realloc을 이용한 동적 확장

```
capacity=4 → append(5) 호출 → isFull() → grow() → realloc → capacity=8
capacity=8 → append(9) 호출 → isFull() → grow() → realloc → capacity=16
```

기존 배열이 꽉 차면 `grow()` 함수가 자동 호출되어 메모리를 확장합니다.  
기존 데이터는 그대로 유지됩니다.

---

## 함수 목록

| 함수 | 설명 |
|------|------|
| `init(list)` | 리스트 초기화, 초기 용량 `INIT_CAPACITY`로 `malloc` |
| `isFull(list)` | `size == capacity` 이면 1 반환 |
| `isEmpty(list)` | `size == 0` 이면 1 반환 |
| `grow(list)` | `realloc`으로 용량 2배 확장 |
| `append(list, value)` | 끝에 요소 추가, 포화 시 `grow()` 자동 호출 |
| `insert(list, index, value)` | 특정 인덱스에 요소 삽입 (0-based) |
| `delete(list, index)` | 특정 인덱스 요소 삭제 (0-based) |
| `get(list, index)` | 특정 인덱스 요소 반환 |
| `printList(list)` | 리스트 전체 출력 (size, capacity 포함) |
| `destroy(list)` | `free()`로 동적 메모리 해제 |

---

## 실행 결과 예시

```
[init] 초기 용량 4으로 리스트 생성

--- append 테스트 ---
append( 1) → 리스트 (size=1, capacity=4): [1]
append( 4) → 리스트 (size=4, capacity=4): [1, 2, 3, 4]
append( 5) → [grow] 용량 확장: 4 → 8
             리스트 (size=5, capacity=8): [1, 2, 3, 4, 5]
append( 9) → [grow] 용량 확장: 8 → 16
             리스트 (size=9, capacity=16): [1, 2, 3, 4, 5, 6, 7, 8, 9]

--- insert 테스트: 인덱스 2에 99 삽입 ---
리스트 (size=11, capacity=16): [1, 2, 99, 3, 4, 5, 6, 7, 8, 9, 10]

--- delete 테스트: 인덱스 2 삭제 ---
리스트 (size=10, capacity=16): [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

--- get 테스트 ---
get(0) = 1
get(4) = 5
get(9) = 10

[destroy] 메모리 해제 완료
```
