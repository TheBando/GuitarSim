// No Copyright
// Created by Derek Bandouveres
#include <math.h>
#include <limits.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "CircularBuffer.h"
#include "StringSound.h"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

std::vector<sf::Int16> makeSamples(StringSound *gs) {
    std::vector<sf::Int16> samples;
    gs->pluck();
    int duration = 8;
    int i;
    int i2 = 1;
    for (i = 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs->tic();
        i2++;
        if (gs->isEmpty()) {
            gs->pluck();
        }
        samples.push_back(gs->sample());
        if (i2 >= (SAMPLES_PER_SEC/3)) {
            i = i + 3;
            samples.push_back(gs->sample()*(-1));
            samples.push_back(gs->sample()*(-1));
            samples.push_back(gs->sample()*(-1));
            i2 = 0;
        }
    }
    return samples;
}

int main() {
    sf::Keyboard::Key keys = {sf::Keyboard::A};
    sf::Text loading;
    sf::Font font;
    if (!font.loadFromFile("./Modern.ttf")) {
        std::cout << "Error: Font Not Found" << std::endl;
    }
    loading.setString("Loading...");
    loading.setFont(font);
    loading.setCharacterSize(36);
    loading.setFillColor(sf::Color::White);
    loading.setStyle(sf::Text::Bold);
    sf::RenderWindow window(sf::VideoMode(400, 275), "Title");

    loading.setPosition((window.getSize().x/2)-(window.getSize().x/6),
    (window.getSize().y/2)-(window.getSize().y/6));
    window.clear();
    window.draw(loading);
    window.display();
    sf::Event event;
    std::vector<sf::Int16> samples;

    std::vector<std::vector<sf::Int16>> v1;
    std::vector<sf::SoundBuffer> v2;
    std::vector<sf::Sound> v3;

    std::vector<int> iVec = {16, 28, 22, 4, 30, 17, 31, 19, 24,
    33, 20, 34, 8, 35, 14, 15, 56, 46, 55, 25, 23,
    3, 2, 5, 21, 6, 1, 13, 9, 12, 10, 49, 50, 48, 51, 57, 999};
    double f;
    for (int index = 0; index < 37; index++) {
        f = pow(2, static_cast<double>(index - 24) / 12.0) * CONCERT_A;
        StringSound *ss = new StringSound(f);
        samples = makeSamples(ss);
        v1.push_back(samples);
    }

    sf::SoundBuffer sb;
    for (int index = 1; index <= 37; index++) {
        if (!sb.loadFromSamples(&v1[index - 1][0],
         v1[index - 1].size(), 2, SAMPLES_PER_SEC)) {
            throw std::runtime_error
            ("sf::SoundBuffer: failed to load from samples");
        }
        v2.push_back(sb);
    }

    sf::Sound s;
    for (int index = 1; index <= 37; index++) {
        s.setBuffer(v2[index - 1]);
        v3.push_back(s);
    }
    float temp;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                int counter = 0;
                for (auto a : iVec) {
                    if (a == event.key.code) {
                        v3[counter].play();
                        break;
                    } else {
                        counter++;
                    }
                }
                break;
            }
            window.clear();
            window.display();
        }
    }

    return 0;
}
