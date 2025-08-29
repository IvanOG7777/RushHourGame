//
// Created by elder on 8/18/2025.
//
#include "../Headers/Truck.h"

#include <iostream>


Truck::Truck(int passedId) : truckId(passedId), truckLength(3), truckVector(initializeTruck()) {}

void Truck:: printTruck() {
    for (char i : truckVector) {
        std:: cout << i << " ";
    }
}

std::vector<char> Truck:: initializeTruck() const {
    std:: vector<char> truckVector(truckLength);

    for (char &i : truckVector) {
        i = 't';
    }
    return truckVector;
}

std::vector <int> Truck::initializeTruckId(int truckId) const {
    std::vector<int> truckIdVector(truckLength);

    for (int& i : truckIdVector) {
        i = truckId;
    }

    return truckIdVector;
}

