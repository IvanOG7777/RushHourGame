//
// Created by elder on 8/16/2025.
//
#include <iostream>
#include <vector>


constexpr int BOARD_HEIGHT = 6;
constexpr int BOARD_WIDTH = 6;

// enum class Orientation {
//     Horizontal,
//     Vertical
// };

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

    bool isInbounds (std:: vector<char> &pieceVector, std:: vector< std:: vector<char>> &board, int xCoord, int yCoord, bool isVertical) {
        bool inBounds = false;

        if (board.empty() || board[0].empty()) {
            return inBounds;
        }

        int row = static_cast<int>(board.size());
        int col = static_cast<int>(board[0].size());
        int length = static_cast<int>(pieceVector.size());
        if ((isVertical == false)) { // checks the horizontal bounds of the piece that is being placed
            if (
                (yCoord >= 0 && yCoord < row) &&
                (xCoord >= 0) &&
                (xCoord + length - 1 < col)
                ) {
                inBounds = true;
            }
        } else if (isVertical == true) { // checks the vertical bounds of the piece that is being placed
            if (
                (xCoord >= 0 && xCoord < col) &&
                (yCoord >= 0) &&
                (yCoord + length - 1 < row)
                ) {
                inBounds = true;
            }
        }
        return inBounds;
    }

    //currently places the car piece horizontally
    void placeCarPiece(Car &car, std:: vector<std:: vector<char>> &board, int xCoord, int yCoord) {

        if (isInbounds(car.carVector, board, xCoord, yCoord, false) == false) {
            std:: cout << "Cant place piece" << std:: endl;
            return;
        }

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

    void placeCarPieceVertical(Car &car, std:: vector<std:: vector<char>> &board, int xCoord, int yCoord) {

        if (isInbounds(car.carVector, board, xCoord, yCoord, true) == false) {
            std:: cout << "Cant place piece" << std:: endl;
            return;
        }

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[yCoord][xCoord] == '0') {
                    board[yCoord][xCoord] = car.carVector[0];
                }
                if (board[yCoord + 1][xCoord] == '0')
                    board[yCoord + 1][xCoord] = car.carVector[1];
            }
        }
    }

    //currently places the truck piece horizontally
    void placeTruckPiece(Truck &truck, std:: vector<std:: vector<char>> &board, int xCoord, int yCoord) {

        if (isInbounds(truck.truckVector, board, xCoord, yCoord, false) == false) {
            std:: cout << "Cant place piece" << std:: endl;
            return;
        }

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

    void placeTruckPieceVertical(Truck &truck, std:: vector<std:: vector<char>> &board, int xCoord, int yCoord) {

        if (isInbounds(truck.truckVector, board, xCoord, yCoord, true) == false) {
            std:: cout << "Cant place piece" << std:: endl;
            return;
        }

        //board.size() = rows
        //board[0].size = cols
            std:: cout << "Can place piece" << std:: endl;
        for (int row = 0; row < board.size(); row++) {
            for (int col = 0; col < board[0].size(); col++) {
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


    std:: cout << "Initialized Board game" << std:: endl;
    Board board(BOARD_HEIGHT, BOARD_WIDTH);

    board.printBoard();

    std:: cout <<std:: endl;


    board.placeCarPiece(car, board.grid, 0, 0);
    board.placeCarPieceVertical(car, board.grid, 1, 6);

    board.placeTruckPiece(truck, board.grid, 2, 2);
    board.placeTruckPieceVertical(truck, board.grid, 5, 6);


    board.printBoard();

}
