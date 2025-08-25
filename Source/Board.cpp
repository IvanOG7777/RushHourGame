//
// Created by elder on 8/18/2025.
//

#include "../Headers/Board.h"
#include "../Headers/Constants.h"
#include <iostream>
#include <vector>
#include <queue>
#include  <map>

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

    int target = board[yCoord][xCoord]; // target id is the x y coord user selected
    if (target == 0) {
        std::cerr << "Selected invalid placement" << std::endl;
        return;
    } // if the spot they selected is 0 (not a valid piece) return
    
    std::vector <std:: vector<bool>> visited(row, std:: vector<bool>(col, false)); // create a bool map of size height x width so we can check if we've seaerched that index
    std:: vector <std::pair<int, int>> indexPairs; // create a vector of pairs to hold all pairs that are the same as the target id
    std::queue<std::pair<int, int>> queue; // create a queue of pair to constanly check new passed pairs until its empty
    int anchorX = 0;
    int anchorY = 0;
    bool isVertical = false;
    
    queue.push({xCoord, yCoord}); // push our initial selected x and y coord to the queue
    visited[yCoord][xCoord] = true; // make visited map at initial x y coord to true meaning its already been searched


    while (!queue.empty()) { // while the queue is NOT empty
        std::pair<int, int> currentXYPair = queue.front(); // set currentXYPair to the single pair in queue 
        queue.pop(); // pop the current pair in the queue to make it ready for next valid pair
        indexPairs.push_back(currentXYPair); // push the currentXYPair into the vector of valid pairs

        const int dx[4] = { -1, 1, 0, 0 }; // created array of indices to search around x
        const int dy[4] = { 0, 0, -1, 1 }; // created array of indices to search around y

        for (int i = 0; i < 4; i++) {
            int nextX = currentXYPair.first + dx[i]; // adding dx at current index to the point we selected
            int nextY = currentXYPair.second + dy[i]; // adding dy at current index to point we selected

            if (nextX < 0 || nextX >= col || nextY < 0 || nextY >= row) continue; // used a as guard. if any of the following is out of bounds in the map we continue, skipping the rest of the code and moving to the next index
            if (visited[nextY][nextX]) continue; // if we have visited the spot already skip to next index
            if (board[nextY][nextX] != target) continue; // if the value at index on board does match the target id we skip to the next index
            visited[nextY][nextX] = true; // if we are able to pass all of the above we've found another id of the same value, we set that index to true on the visited board
            queue.push({ nextX, nextY }); // then we push that new x and y value into the queue so that we can use those values as our new currentXYPair
           
        }
    }

    if (indexPairs.empty()) {
        std::cerr << "index pair vector is empty returing" << std::endl;
        return;
    }
    std::pair <int, int> firstPair = indexPairs.front();

    int initialX = firstPair.first;
    int initialY = firstPair.second;
    int xCounter = 0;
    int yCounter = 0;

    int minX = firstPair.first;
    int maxX = firstPair.first;
    int minY = firstPair.second;
    int maxY = firstPair.second;

    for (int i = 1; i < static_cast<int>(indexPairs.size()); i++) {
        if (indexPairs[i].first > maxX) {
            maxX = indexPairs[i].first;
        }

        if (indexPairs[i].first < minX) {
            minX = indexPairs[i].first;
        }

        if (indexPairs[i].second > maxY) {
            maxY = indexPairs[i].second;
        }

        if (indexPairs[i].second < minY) {
            minY = indexPairs[i].second;
        }
    }

    for (int i = 0; i < static_cast<int>(indexPairs.size()); i++) {
        if (initialX == indexPairs[i].first) {
            xCounter++;
        }

        if (initialY == indexPairs[i].second) {
            yCounter++;
        }
    }

    int lengthY = (maxY - minY + 1);
    int lengthX = (maxX - minX + 1);

    if (xCounter == static_cast<int> (indexPairs.size()) && (maxY - minY + 1) == static_cast<int>(indexPairs.size())) {
        isVertical = true;
    }

    if (yCounter == static_cast<int> (indexPairs.size()) * (maxX - minX + 1) == static_cast<int> (indexPairs.size())) {
        isVertical = false;
    }

    anchorX = minX;
    anchorY = minY;

    std::cout << "Anchor Point" << "{" << minX << "," << minY << "}" << std::endl;
    std::cout << "Is piece vertical: " << (isVertical ? "True" : "False") << std::endl;

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