//
// Created by elder on 8/18/2025.
//

#ifndef TRUCK_H
#define TRUCK_H
#include <vector>

class Truck {
public:
    int truckLength;
    int truckId;
    std:: vector<char> truckVector;
    std:: vector<int> truckIdVector;
    void printTruck();
    Truck(int passedId);

private:
    std:: vector <char> initializeTruck() const;
    std:: vector <int> initializeTruckId(int passedId) const;
};

#endif //TRUCK_H