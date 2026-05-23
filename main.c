#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 20;

typedef struct {
    int empID;
    int costSoFar;
    int lowerBound;
    bool assigned[MAX]; //Task tracking
}Node;

typedef struct{
    Node* data;
    int size; //Current ele in heap
    int capacity; //Max a heap can hold
}PriorityQueue;

PriorityQueue* initPriorityQueue(int capacity){
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (Node*)malloc(capacity * sizeof(Node));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PriorityQueue* pq, Node node){
    if(pq->size >= pq->capacity){
        printf("Priority queue is full\n");
        return;
    }
    pq->data[pq->size] = node;
    pq->size++;
    //Heapify up
    int i = pq-> size -1;
    while(i>0 && pq->data[i].lowerBound < pq->data[(i-1)/2].lowerBound){
        swap(&pq->data[i], &pq->data[(i-1)/2]);
        i = (i-1)/2;
    }
}

Node Pop(PriorityQueue* pq){
    if(pq->size <= 0){
        printf("Priority queue is empty\n");
        Node emptyNode;
        return emptyNode; // Return an empty node
    }
    Node minNode = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    //Heapify down
    int i = 0;
    while(true){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;
        if(left < pq->size && pq->data[left].lowerBound < pq->data[smallest].lowerBound){
            smallest = left;
        }
        if(right < pq->size && pq->data[right].lowerBound < pq->data[smallest].lowerBound){
            smallest = right;
        }
        if(smallest == i) break;
        swap(&pq->data[i], &pq->data[smallest]);
        i = smallest;
    }
    return minNode;
}


