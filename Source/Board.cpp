//
// Created by elder on 8/18/2025.
//

#include "../Headers/Board.h"
#include "../Headers/Constants.h"
#include <iostream>
#include <vector>
#include <queue>

Board::Board(int passedHeight, int passedWidth) : height(passedHeight), width(passedWidth) { 
    grid = initializeBoard();
    idGrid = initializeIdBoard();
}

void Board::printBoard() {
    for (auto &row: grid) {
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

void Board::printIdBoard() {
    for (auto &row : idGrid) {
        for (auto element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

bool Board::isInBounds(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {

    if (board.empty() || board[0].empty()) {
        return false;
    }

    int row = static_cast<int>(board.size());
    int col = static_cast<int>(board[0].size());
    int length = static_cast<int>(pieceVector.size());

    if ((isVertical == false)) {
        // checks the horizontal bounds of the piece that is being placed

        if (yCoord < 0 || yCoord >= row) {
            return false;
        }
        if (xCoord < 0 || xCoord + length - 1 >= col) {
            return false;
        }
    } else if (isVertical == true) {
        // checks the vertical bounds of the piece that is being placed
        if (xCoord < 0 || xCoord >= col) {
            return false;
        }

        if (yCoord < 0 || yCoord + length - 1 >= row) {
            return false;
        }
    }
    return true;
}

bool Board::collides(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) {
     bool collision = false;
        if (isInBounds(pieceVector, board, xCoord, yCoord, isVertical) == false) {
            return true;
        }

        int length = static_cast<int>(pieceVector.size());

        if (isVertical == false) {
            for (int k = 0; k < length; k++) {
                if (board[yCoord][xCoord + k] != '0') return true;
            }
        }

        if (isVertical == true) {
            for (int k = 0; k < length; k++) {
                if (board[yCoord + k][xCoord] != '0') return true;
            }
        }
        return false;
}

void Board::movePieceDynamically(std::vector<char>& pieceVector, std::vector<std::vector<char>>& board, int &xCoord, int &yCoord, bool isVertical, int dx, int dy) {
    auto &tempBoard = board;
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

    for (auto &row : tempBoard) {
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

void Board::grabPiece(std::vector<std::vector<int>> &board, int xCoord, int yCoord) {
    int row = board.size();
    int col = board[0].size();

    if (yCoord < 0 || yCoord >= row || xCoord < 0 || xCoord >= col) return; //out of bounds check 

    int target = idGrid[yCoord][xCoord];
    if (target == 0) return;
    
    std::vector <std:: vector<bool>> visited(row, std:: vector<bool>(col, false));
    std:: vector <std::pair<int, int>> indexPair;
    std::queue<std::pair<int, int>> queue;
    
    queue.push({xCoord, yCoord});
    visited[yCoord][xCoord] = true;


    while (!queue.empty()) {
        std::pair<int, int> cxcy = queue.front();
        queue.pop();
        indexPair.push_back(cxcy);

        const int dx[4] = { -1, 1, 0, 0 };
        const int dy[4] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int nx = cxcy.first + dx[i];
            int ny = cxcy.second + dy[i];

            if (nx < 0 || nx >= col || ny < 0 || ny >= row) continue;
            if (visited[ny][nx]) continue;
            if (board[ny][nx] != target) continue;
            visited[ny][nx] = true;
            queue.push({ nx, ny });
        }
    }

    for (auto pair : indexPair) {
        std::cout << "{" << pair.first << "," << pair.second << "}" << std::endl;
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
               
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord][xCoord + 1] == '0')
                            board[yCoord][xCoord + 1] = car.carVector[1];
                  
            } else if ((yCoord >= 0 && yCoord < row) && (xCoord >= 0) && (xCoord - (length - 1) >= 0)) {
                
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord][xCoord - 1] == '0')
                            board[yCoord][xCoord - 1] = car.carVector[1];
                  
            }
        }

        if (isVertical == true) {
            if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord + length - 1 < row)) {
               
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord + 1][xCoord] == '0')
                            board[yCoord + 1][xCoord] = car.carVector[1];
                 
            } else if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord - (length - 1) >= 0)) {
                
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord - 1][xCoord] == '0')
                            board[yCoord - 1][xCoord] = car.carVector[1];
            }
        }
        else {
            return;
        }
}

void Board::placeTruckPiece(Truck &truck, std::vector<std::vector<char> > &board, std:: vector<std::vector<int>> &idBoard, int xCoord, int yCoord, bool isVertical) {
     if (collides(truck.truckVector, board, xCoord, yCoord, isVertical) == true) {
            std::cout << "Cant place piece at:" << xCoord << ',' << yCoord << std::endl;
            return;
        }

        int row = static_cast<int>(board.size());
        int col = static_cast<int>(board[0].size());
        int length = static_cast<int>(truck.truckVector.size());

        if (isVertical == false) {
            if ((yCoord >= 0 && yCoord < row) && (xCoord >= 0) && (xCoord + length - 1 < col)) {

                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = truck.truckVector[0];
                        }
                        if (board[yCoord][xCoord + 1] == '0') {
                            board[yCoord][xCoord + 1] = truck.truckVector[1];
                        }
                        if (board[yCoord][xCoord + 2] == '0') {
                            board[yCoord][xCoord + 2] = truck.truckVector[2];
                        }


                        if (idBoard[yCoord][xCoord] == 0) {
                            idBoard[yCoord][xCoord] = truck.truckId;
                        }
                        if (idBoard[yCoord][xCoord + 1] == 0) {
                            idBoard[yCoord][xCoord + 1] = truck.truckId;
                        }
                        if (idBoard[yCoord][xCoord + 2] == 0) {
                            idBoard[yCoord][xCoord + 2] = truck.truckId;
                        }

            } else if ((yCoord >= 0 && yCoord < row) && (xCoord >= 0) && (xCoord - (length - 1) >= 0)){
                
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = truck.truckVector[0];
                        }
                        if (board[yCoord][xCoord - 1] == '0') {
                            board[yCoord][xCoord - 1] = truck.truckVector[1];
                        }
                        if (board[yCoord][xCoord - 2] == '0') {
                            board[yCoord][xCoord - 2] = truck.truckVector[2];
                        }

                        if (idBoard[yCoord][xCoord] == 0) {
                            idBoard[yCoord][xCoord] = truck.truckId;
                        }
                        if (idBoard[yCoord][xCoord - 1] == 0) {
                            idBoard[yCoord][xCoord - 1] = truck.truckId;
                        }
                        if (idBoard[yCoord][xCoord - 2] == 0) {
                            idBoard[yCoord][xCoord - 2] = truck.truckId;
                        }
                   
            }
            else {
                return;
            }
        }

        if (isVertical == true) {
            if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord + length - 1 < row)) {
                
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = truck.truckVector[0];
                        }
                        if (board[yCoord + 1][xCoord] == '0') {
                            board[yCoord + 1][xCoord] = truck.truckVector[1];
                        }
                        if (board[yCoord + 2][xCoord] == '0') {
                            board[yCoord + 2][xCoord] = truck.truckVector[2];
                        }
                  

               
                        if (idBoard[yCoord][xCoord] == 0) {
                            idBoard[yCoord][xCoord] = truck.truckId;
                        }
                        if (idBoard[yCoord + 1][xCoord] == 0) {
                            idBoard[yCoord + 1][xCoord] = truck.truckId;
                        }
                        if (idBoard[yCoord + 2][xCoord] == 0) {
                            idBoard[yCoord + 2][xCoord] = truck.truckId;
                        }
                   
            } else if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord - (length - 1) >= 0)) {
                
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = truck.truckVector[0];
                        }
                        if (board[yCoord - 1][xCoord] == '0') {
                            board[yCoord - 1][xCoord] = truck.truckVector[1];
                        }
                        if (board[yCoord - 2][xCoord] == '0') {
                            board[yCoord - 2][xCoord] = truck.truckVector[2];
                        }


                        if (idBoard[yCoord][xCoord] == 0) {
                            idBoard[yCoord][xCoord] = truck.truckId;
                        }
                        if (idBoard[yCoord - 1][xCoord] == 0) {
                            idBoard[yCoord - 1][xCoord] = truck.truckId;
                        }
                        if (idBoard[yCoord - 1][xCoord] == 0) {
                            idBoard[yCoord - 1][xCoord] = truck.truckId;
                        }
            }
            else {
                return;
            }
        }
}

std::vector<std::vector<char> > Board::initializeBoard() {
    std::vector<std::vector<char> > board(height, std::vector<char>(width, '0'));

    int row = board.size();
    int col = board[0].size();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            board[i][j] = '0';
        }
    }
    return board;
}

std::vector<std::vector<int>> Board::initializeIdBoard() {
    std::vector<std::vector<int> > board(height, std::vector<int>(width, 0));

    int row = board.size();
    int col = board[0].size();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            board[i][j] = 0;
        }
    }
    return board;
}