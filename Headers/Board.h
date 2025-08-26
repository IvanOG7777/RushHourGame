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
    std:: vector<std::vector<int>> idGrid;
    Board(int height, int width);

    void printBoard();

    void printIdBoard();

    bool isInBounds(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical);

    bool collides(std:: vector<char> &pieceVector, std::vector<std::vector<char>> &board, int xCoord, int yCoord, bool isVertical);

    void placeCarPiece(Car &car, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical);

    void placeTruckPiece(Truck &truck, std::vector<std::vector<char> > &board, std::vector<std::vector<int>>& idBoard,int xCoord, int yCoord, bool isVertical);

    void movePieceDynamically(std::vector<char>& pieceVector, std::vector<std::vector<char>>& board, int &xCoord, int &yCoord, bool isVertical, int dx, int dy);

    std:: vector<std::pair<int,int>> grabPiece(std::vector<std::vector<int>>& board, int xCoord, int yCoord);

    private:
    std:: vector<std:: vector<char>> initializeBoard();
    std:: vector<std:: vector<int>> initializeIdBoard();
};

#endif //BOARD_H