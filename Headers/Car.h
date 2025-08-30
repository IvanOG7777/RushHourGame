//
// Created by elder on 8/18/2025.
//
#ifndef CAR_H
#define CAR_H
#include <vector>

class Car {
    public:
    int carLength;
    int carId;
    std:: vector<char> carVector;
    std::vector<int> carIdVector;
    void printCar() const;
    Car(int passedId);

private:
    std:: vector <char> initalizeCarVector() const;
    std:: vector <int> initializeCarId(int passedId) const;
};

#endif //CAR_H
