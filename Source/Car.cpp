//
// Created by elder on 8/18/2025.
//
#include "../Headers/Car.h"
#include <iostream>
#include <vector>


Car::Car(int passedId) : carId(passedId), carLength(2), carVector(initalizeCarVector()) {}

void Car::printCar() const {
    for (char i : carVector) {
        std:: cout << i << std:: endl;
    }
}

std::vector<char> Car::initalizeCarVector() const {
    std:: vector<char> carVector(carLength);
    for (char &i : carVector) {
        i = 'c';
    }
    return carVector;
}

std::vector<int> Car::initializeCarId(int passedId) const {
    std::vector<int> carVector(carLength);

    for (int& i : carVector) {
        i = passedId;
    }
    return carVector;
}

