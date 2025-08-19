//
// Created by elder on 8/18/2025.
//
#ifndef CAR_H
#define CAR_H
#include <vector>

class Car {
    public:
    int carLength;
    std:: vector<char> carVector;
    void printCar() const;
    Car();

private:
    std:: vector<char> initalizeCarVector() const;
};

#endif //CAR_H
