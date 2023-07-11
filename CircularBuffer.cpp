// Copyright this isnt...
#include <stdexcept>
#include <iostream>

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int capacity) {
    curSize = 0; maxSize = capacity;
}

void CircularBuffer::enqueue(int16_t x) {
    if (isFull())
    {throw std::runtime_error("enqueue: can't enqueue to a full ring");} else {
        if (head == nullptr || tail == nullptr) {
            tail = new node;
            tail->data = x;
            head = tail;
            curSize++;
        } else if (&head == &tail) {
            tail = new node;
            tail->data = x;
            tail->next = head;
            head->last = tail;
            curSize++;
        } else {
            struct node *tempNode = tail;
            tail = new node;
            tail->data = x;
            tempNode->last = tail;
            tail->next = tempNode;
            curSize++;
        }
    }
}

int16_t CircularBuffer::dequeue() {
    if (isEmpty()) { throw std::runtime_error
    ("dequeue: can't dequeue an empty ring");} else {
        struct node *tempNode = head;
        head = tempNode->last;
        curSize--;
        return tempNode->data;
    }
}

int16_t CircularBuffer::peek() {
    if (isEmpty()) {throw std::runtime_error
    ("peek: can't peek an empty ring");} else {return head->data;}
}
int16_t CircularBuffer::peekNext() {
    if (isEmpty()) {
        throw std::runtime_error("peek: can't peek an empty ring");
    } else {return head->next->data;}
}

void CircularBuffer::empty() {
    head = nullptr;
    tail = nullptr;
    curSize = 0;
}
