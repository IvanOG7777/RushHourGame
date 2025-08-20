//
// Created by elder on 8/18/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include "../Headers/Car.h"
#include "../Headers/Truck.h"
#include <vector>

class Board {
    public:
    int height;
    int width;
    std:: vector<std:: vector<char>> grid;
    Board(int height, int width);

    void printBoard();

    bool isInBounds(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical);

    bool collides(std:: vector<char> &pieceVector, std::vector<std::vector<char>> &board, int xCoord, int yCoord, bool isVertical);

    void placeCarPiece(Car &car, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical);

    void placeTruckPiece(Truck &truck, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical);

    void movePieceDynamically(std::vector<char>& pieceVector, std::vector<std::vector<char>>& board, int &xCoord, int &yCoord, bool isVertical, int dx, int dy);

    private:
    std::vector<std::vector<char>> initializeBoard();
};

#endif //BOARD_H
