//
// Created by elder on 8/16/2025.
//
#include <iostream>
#include <vector>
#include "../Headers/Car.h"


constexpr int BOARD_HEIGHT = 6;
constexpr int BOARD_WIDTH = 6;

class Car {
public:
    int carLength;
    std::vector<char> carVector;
    Car() : carLength(2) { carVector = initalizeCarVector(); }

    void printCar() {
        for (char i: carVector) {
            std::cout << i;
        }
    }

private:
    std::vector<char> initalizeCarVector() {
        std::vector<char> carVector(carLength);
        for (char &i: carVector) {
            i = 'c';
        }
        return carVector;
    }
};

class Truck {
public:
    int truckLength;
    std::vector<char> truckVector;
    Truck() : truckLength(3) { truckVector = initalizeTruckVector(); }

    void printTruck() {
        for (char i: truckVector) {
            std::cout << i;
        }
    }

private:
    std::vector<char> initalizeTruckVector() {
        std::vector<char> truckVector(truckLength);
        for (char &i: truckVector) {
            i = 't';
        }
        return truckVector;
    }
};

class Board {
public:
    int height;
    int width;
    std::vector<std::vector<char> > grid;
    Board(int passedHeight, int passedWidth) : height(passedHeight), width(passedWidth) { grid = initalizeBoard(); }

    void newPrintBoard() {
        for (auto row: grid) {
            for (auto element: row) {
                if (element == 'c') {
                    std::cout << "\033[31m" << element << "\033[0m" << " ";
                } else if (element == 't') {
                    std::cout << "\033[32m" << element << "\033[0m" << " ";
                } else {
                    std::cout << element << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    bool isInbounds(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {
        bool inBounds = false;

        if (board.empty() || board[0].empty()) {
            return inBounds;
        }

        int row = static_cast<int>(board.size());
        int col = static_cast<int>(board[0].size());
        int length = static_cast<int>(pieceVector.size());

        if ((isVertical == false)) {
            // checks the horizontal bounds of the piece that is being placed

            if ( // checks piece doing from left to right
                (yCoord >= 0 && yCoord < row) &&
                (xCoord >= 0) &&
                (xCoord + length - 1 < col)
            ) {
                inBounds = true;
            }

            if ( // checks piece doing from right to left
                (yCoord >= 0 && yCoord < row) &&
                (xCoord >= 0) &&
                (xCoord - (length - 1) >= 0)
            ) {
                inBounds = true;
            }
        } else if (isVertical == true) {
            // checks the vertical bounds of the piece that is being placed

            if ( // checks vertical going from up to down
                (xCoord >= 0 && xCoord < col) &&
                (yCoord >= 0) &&
                (yCoord + length - 1 < row)
            ) {
                inBounds = true;
            }

            if ( // checks vertical going from down to up
                (xCoord >= 0 && xCoord < col) &&
                (yCoord >= 0) &&
                (yCoord - (length - 1) >= 0)
            ) {
                inBounds = true;
            }
        }

        return inBounds;
    }

    bool collides(std:: vector<char> &pieceVector, std::vector<std::vector<char>> &board, int xCoord, int yCoord, bool isVertical) {
        bool collision = false;
        if (isInbounds(pieceVector, board, xCoord, yCoord, isVertical) == false) {
            return true;
        }

        const int rows = static_cast<int>(board.size());
        const int cols = static_cast<int>(board[0].size());
        const int len  = static_cast<int>(pieceVector.size());

        if (isVertical == false) {
            if (xCoord + len - 1 < cols) {
                collision = false;
                for (int k = 0; k < len; k++) {
                    if (board[yCoord][xCoord + k] != '0') {
                        collision = true;
                        break;
                    }
                }
                if (collision == false) {
                    return collision;
                }
            }

            if (xCoord - (len - 1) >= 0 ) {
                collision = false;
                for (int k = 0; k < len; k++) {
                    if (board[yCoord][xCoord - k] != '0') {
                        collision = true;
                        break;
                    }
                }
                if (collision == false) {
                    return collision;
                }
            }
        }

        if (isVertical == true) {
            if (yCoord + len - 1 < rows) {
                collision = false;
                for (int k = 0; k < len; k++) {
                    if (board[yCoord + k][xCoord] != '0') {
                        collision = true;
                        break;
                    }
                }
                if (collision == false) {
                    return collision;
                }
            }

            if (yCoord - (len - 1) >= 0 ) {
                collision = false;
                for (int k = 0; k < len; k++) {
                    if (board[yCoord - k][xCoord] != '0') {
                        collision = true;
                        break;
                    }
                }
                if (collision == false) {
                    return collision;
                }
            }
        }
        return collision;
    }

    //currently places the car piece horizontally
    void placeCarPiece(Car &car, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {
        if (collides(car.carVector, board, xCoord, yCoord, isVertical) == true) {
            std::cout << "Cant place piece at:" << xCoord << ',' << yCoord << std::endl;
            return;
        }

        int row = static_cast<int>(board.size());
        int col = static_cast<int>(board[0].size());
        int length = static_cast<int>(car.carVector.size());

        if (isVertical == false) {
            if ((yCoord >= 0 && yCoord < row) && (xCoord >= 0) && (xCoord + length - 1 < col)) {
                for (int i = 0; i < board.size(); i++) {
                    for (int j = 0; j < board[0].size(); j++) {
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord][xCoord + 1] == '0')
                            board[yCoord][xCoord + 1] = car.carVector[1];
                    }
                }
            } else if ((yCoord >= 0 && yCoord < row) && (xCoord >= 0) && (xCoord - (length - 1) >= 0)) {
                for (int i = 0; i < board.size(); i++) {
                    for (int j = 0; j < board[0].size(); j++) {
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord][xCoord - 1] == '0')
                            board[yCoord][xCoord - 1] = car.carVector[1];
                    }
                }
            }
        }

        if (isVertical == true) {
            if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord + length - 1 < row)) {
                for (int i = 0; i < board.size(); i++) {
                    for (int j = 0; j < board[0].size(); j++) {
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord + 1][xCoord] == '0')
                            board[yCoord + 1][xCoord] = car.carVector[1];
                    }
                }
            } else if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord - (length - 1) >= 0)) {
                for (int i = 0; i < board.size(); i++) {
                    for (int j = 0; j < board[0].size(); j++) {
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord - 1][xCoord] == '0')
                            board[yCoord - 1][xCoord] = car.carVector[1];
                    }
                }
            }
        }
    }

    //currently places the truck piece horizontally
    void placeTruckPiece(Truck &truck, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {
        if (collides(truck.truckVector, board, xCoord, yCoord, isVertical) == true) {
            std::cout << "Cant place piece at:" << xCoord << ',' << yCoord << std::endl;
            return;
        }

        int row = static_cast<int>(board.size());
        int col = static_cast<int>(board[0].size());
        int length = static_cast<int>(truck.truckVector.size());

        if (isVertical == false) {
            if ((yCoord >= 0 && yCoord < row) && (xCoord >= 0) && (xCoord + length - 1 < col)) {
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
            } else if ((yCoord >= 0 && yCoord < row) && (xCoord >= 0) && (xCoord - (length - 1) >= 0)){
                for (int i = 0; i < board.size(); i++) {
                    for (int j = 0; j < board[0].size(); j++) {
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = truck.truckVector[0];
                        }
                        if (board[yCoord][xCoord - 1] == '0') {
                            board[yCoord][xCoord - 1] = truck.truckVector[1];
                        }
                        if (board[yCoord][xCoord - 2] == '0') {
                            board[yCoord][xCoord - 2] = truck.truckVector[2];
                        }
                    }
                }
            }
        }

        if (isVertical == true) {
            if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord + length - 1 < row)) {
                for (int i = 0; i < board.size(); i++) {
                    for (int j = 0; j < board[0].size(); j++) {
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = truck.truckVector[0];
                        }
                        if (board[yCoord + 1][xCoord] == '0') {
                            board[yCoord + 1][xCoord] = truck.truckVector[1];
                        }
                        if (board[yCoord + 2][xCoord] == '0') {
                            board[yCoord + 2][xCoord] = truck.truckVector[2];
                        }
                    }
                }
            } else if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord - (length - 1) >= 0)){
                for (int i = 0; i < board.size(); i++) {
                    for (int j = 0; j < board[0].size(); j++) {
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = truck.truckVector[0];
                        }
                        if (board[yCoord - 1][xCoord] == '0') {
                            board[yCoord - 1][xCoord] = truck.truckVector[1];
                        }
                        if (board[yCoord - 2][xCoord] == '0') {
                            board[yCoord - 2][xCoord] = truck.truckVector[2];
                        }
                    }
                }
            }
        }
    }

private:
    std::vector<std::vector<char> > initalizeBoard() {
        std::vector<std::vector<char> > board(height, std::vector<char>(width, '0'));

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


    std::cout << "Initialized Board game" << std::endl;
    Board board(BOARD_HEIGHT, BOARD_WIDTH);

    board.newPrintBoard();

    std::cout << std::endl;


    board.placeCarPiece(car, board.grid, 0, 0, false);
    board.placeCarPiece(car, board.grid, 1, 1, true);
    board.placeCarPiece(car, board.grid, 5, 0, true);

    board.placeTruckPiece(truck, board.grid, 0, 2, true);
    board.placeTruckPiece(truck, board.grid, 5, 5, false);


    board.newPrintBoard();
}
