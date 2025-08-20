//
// Created by elder on 8/18/2025.
//

#include "../Headers/Board.h"
#include "../Headers/Constants.h"
#include <iostream>
#include <vector>

Board::Board(int passedHeight, int passedWidth) : height(passedHeight), width(passedWidth) { grid = initializeBoard();}

void Board::printBoard() {
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

bool Board::isInBounds(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {
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

bool Board::collides(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {
     bool collision = false;
        if (isInBounds(pieceVector, board, xCoord, yCoord, isVertical) == false) {
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

void Board::movePieceDynamically(std::vector<char>& pieceVector, std::vector<std::vector<char>>& board, int &xCoord, int &yCoord, bool isVertical, int dx, int dy) {
    auto tempBoard = board;
    int rows = board.size();
    int cols = board[0].size();
    int length = pieceVector.size();

    int newX = xCoord + dx;
    int newY = yCoord + dy;



    if (isVertical == true) {
        if (newY < 0 || (newY + length - 1) >= rows) return;
        if (newX < 0 || newX >= cols) return;
    }

    if (isVertical == false) {
        if (newX < 0 || (newX + length - 1) >= cols) return;
        if (newY < 0 || newY >= rows) return;
    }

    if (collides(pieceVector, board, newX, newY, isVertical) == true) return;

    xCoord = newX;
    yCoord = newY;

    if (isVertical == true) {
        for (int k = 0; k < length; k++) {
            tempBoard[yCoord + k][xCoord] = pieceVector[k];
        }
    }

    if (isVertical == false) {
        for (int k = 0; k < length; k++) {
            tempBoard[yCoord][xCoord + k] = pieceVector[k];
        }
    }

    system("cls");

    for (auto row : tempBoard) {
        for (auto element : row) {
            if (element == 'c') {
                std::cout << "\033[31m" << element << "\033[0m" << " ";
            }
            else if (element == 't') {
                std::cout << "\033[32m" << element << "\033[0m" << " ";
            }
            else {
                std::cout << element << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Board::placeCarPiece(Car &car, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {
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

void Board::placeTruckPiece(Truck &truck, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {
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

std::vector<std::vector<char> > Board::initializeBoard() {
    std::vector<std::vector<char> > board(height, std::vector<char>(width, '0'));

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            board[i][j] = '0';
        }
    }
    return board;
}
