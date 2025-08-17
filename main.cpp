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
    int length;
    Car() : length(2) {}

private:
    static std:: vector<int> initalizeCarVector(int length) {
        std:: vector<int> carVector(length);
        for (int i = 0; i < length; i++) {
            carVector[i] = 'c';
        }
        return carVector;
    }
};

class Board {
    public:
    int height;
    int width;
    std::vector<std::vector<int>> grid;
    Board(int passedHeight, int passedWidth) : height(passedHeight), width(passedWidth) {grid = initalizeBoard();}

    void printBoard() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // void placePiece()

private:
    std:: vector<std:: vector<int>> initalizeBoard() {
        std::vector<std:: vector<int>> board(height, std::vector<int>(width, 0));

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                board[i][j] = 0;
            }
        }
        return board;
    }
};




int main() {

    std:: vector<int> Truck = {1,2,3};

    Car car;
    std:: cout << car.length << std::endl;

    Board boardclass(BOARD_HEIGHT, BOARD_WIDTH);

    boardclass.printBoard();

}
