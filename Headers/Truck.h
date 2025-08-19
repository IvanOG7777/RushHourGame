//
// Created by elder on 8/18/2025.
//

#ifndef TRUCK_H
#define TRUCK_H
#include <vector>

class Truck {
public:
    int truckLength;
    std:: vector<char> truckVector;
    void printTruck();
    Truck();

private:
    std:: vector<char> initializeTruck() const;
};

#endif //TRUCK_H
