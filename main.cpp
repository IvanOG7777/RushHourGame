//
// Created by elder on 8/16/2025.
//
#include <iostream>
#include <vector>


constexpr int BOARD_HEIGHT = 6;
constexpr int BOARD_WIDTH = 6;

enum class Orientation {
    Horizontal,
    Vertical
};

// struct Vehicle {
//     int id;
//     int length;
//     Orientation orientation;
//     int row;
//     int column;
// };

class Car {
public:
    int carLength;
    std::vector<char> carVector;
    Car() : carLength(2) {carVector = initalizeCarVector();}

    void printCar() {
        for (char i : carVector) {
            std::cout << i;
        }
    }

private:
     std:: vector<char> initalizeCarVector() {
        std:: vector<char> carVector(carLength);
        for (char &i : carVector) {
            i = 'c';
        }
        return carVector;
    }
};

class Truck {
public:
    int truckLength;
    std::vector<char> truckVector;
    Truck() : truckLength(3) {truckVector = initalizeTruckVector();}

    void printTruck() {
        for (char i : truckVector) {
            std::cout << i;
        }
    }

private:
    std:: vector<char> initalizeTruckVector() {
        std:: vector<char> truckVector(truckLength);
        for (char &i : truckVector) {
            i = 't';
        }
        return truckVector;
    }
};

class Board {
    public:
    int height;
    int width;
    std::vector<std::vector<char>> grid;
    Board(int passedHeight, int passedWidth) : height(passedHeight), width(passedWidth) {grid = initalizeBoard();}

    void printBoard() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void placeCarPiece(Car &car, std:: vector<std:: vector<char>> &board, int xCoord, int yCoord) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[yCoord][xCoord] == '0') {
                    board[yCoord][xCoord] = car.carVector[0];
                }
                if (board[yCoord][xCoord + 1] == '0')
                    board[yCoord][xCoord + 1] = car.carVector[1];
            }
        }
    }

    void placeTruckPiece(Truck &truck, std:: vector<std:: vector<char>> &board, int xCoord, int yCoord) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[yCoord][xCoord] == '0') {
                    board[yCoord][xCoord] = truck.truckVector[0];
                }
                if (board[yCoord][xCoord + 1] == '0') {
                    board[yCoord][xCoord + 1] = truck.truckVector[1];
                }
                if (board[yCoord][xCoord + 2] == '0') {
                    board[yCoord][xCoord + 2] = truck.truckVector[2];
                }
            }
        }
    }



private:
    std:: vector<std:: vector<char>> initalizeBoard() {
        std::vector<std:: vector<char>> board(height, std::vector<char>(width, '0'));

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                board[i][j] = '0';
            }
        }
        return board;
    }
};




int main() {

    Car car;
    Truck truck;

    std:: cout << "Truck Length: " << truck.truckLength << std::endl;
    std:: cout << "Truck vector: ";
    truck.printTruck();
    std:: cout << std:: endl;

    std:: cout << "Initialized Board game" << std:: endl;
    Board board(BOARD_HEIGHT, BOARD_WIDTH);

    board.printBoard();

    std:: cout <<std:: endl;

    board.placeCarPiece(car, board.grid, 0, 0);
    board.placeTruckPiece(truck, board.grid, 2, 2);

    board.printBoard();

}
