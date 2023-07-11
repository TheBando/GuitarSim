// No Copyright
// Created by Derek Bandouveres
#pragma once

#include <stdint.h>


struct node {
    int16_t data;
    struct node *next;
    struct node *last;
};

class CircularBuffer{
 public:
        explicit CircularBuffer(int capacity);
        int size() { return curSize; }
        bool isEmpty() { return (size() == 0); }
        bool isFull() { return (size() == maxSize); }
        void enqueue(int16_t x);
        int16_t dequeue();
        int16_t peek();
        int16_t peekNext();
        void empty();

 private:
        int maxSize;
        int curSize;
        struct node* head = nullptr;
        struct node* tail = nullptr;
};
