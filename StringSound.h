// No Copyright
// Created by Derek Bandouveres
#pragma once

#include <stdint.h>
#include <vector>
#include <SFML/Audio/Export.hpp>
#include <SFML/Audio/AlResource.hpp>

#include "CircularBuffer.h"

class StringSound{
 public:
        explicit StringSound(double freq);
        explicit StringSound(std::vector<sf::Int16> init);
        StringSound(const StringSound &obj) = delete;
        ~StringSound();

        StringSound* GetThis() { return this; }
        void pluck();

        void tic();

        sf::Int16 sample() { return _cb->peek(); }
        int time() { return _time; }

        bool isEmpty() { return _cb->isEmpty(); }
 private:
        CircularBuffer *_cb;
        int _time;
};
