#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#define INIT_CAPACITY 4  

typedef int Element;

typedef struct {
    Element* data;   
    int size;        
    int capacity;    
} SeqList;

void init(SeqList* list);
int  isFull(SeqList* list);
int  isEmpty(SeqList* list);
void grow(SeqList* list);
void append(SeqList* list, Element value);
void insert(SeqList* list, int index, Element value);
void delete(SeqList* list, int index);
Element get(SeqList* list, int index);
void printList(SeqList* list);
void destroy(SeqList* list);

#endif 
