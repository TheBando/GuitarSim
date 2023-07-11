// No Copyright
// Created by Derek Bandouveres
#include "StringSound.h"
#include <math.h>
#include <random>
#include <iostream>



StringSound::StringSound(double freq) {
    _cb = new CircularBuffer(ceil(freq));
    _time = 0;
}

StringSound::StringSound(std::vector<sf::Int16> init) {
    _cb = new CircularBuffer(ceil(init.size()));
    _time = 0;
    for (int i = 0; i < init.size(); i++) {
        _cb->enqueue(init[i]);
    }
}


StringSound::~StringSound() {
    delete[] _cb;
}

void StringSound::pluck() {
    if (_cb->isFull()) {
        _cb->empty();
    }
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-32768.0, 32768.0);
    while ( !(_cb->isFull()) ) {
        int16_t i = dist(mt);
        _cb->enqueue(i);
    }
}
void StringSound::tic() {
    _time++;
    int16_t i = _cb->peek();
    _cb->dequeue();
    i = (i+_cb->peek())/2;
    _cb->enqueue(i);
}
