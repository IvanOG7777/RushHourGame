//
// Created by elder on 8/18/2025.
//

#include "../Headers/Board.h"
#include "../Headers/Constants.h"
#include <iostream>
#include <vector>
#include <queue>
#include  <map>

Board::Board(int passedHeight, int passedWidth) : height(passedHeight), width(passedWidth) { // passes the height nad width of map
    //initializes the char grid and id grid
    grid = initializeBoard();
    idGrid = initializeIdBoard();
}


//function used to print board
void Board::printBoard(int cursorX, int cursorY) {

    if (grid.empty() || grid[0].empty()) return;

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            const char ch = grid[row][col];
            const bool isCursor = (col == cursorX && row == cursorY);

            if (isCursor) {
                std::cout << "\033[7m";
            }

            if (ch == 'c') {
                std::cout << "\033[31m";
            }
            else if (ch == 't') {
                std::cout << "\033[32m";
            }

            std::cout << ch << "\033[0m" << ' ';
        }
        std::cout << std::endl;
    }
}

//prints the id to the board
void Board::printIdBoard() {
    for (auto &row : idGrid) {
        for (auto element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

//function to check if piece is in bounds of the map
bool Board::isInBounds(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, int xCoord, int yCoord, bool isVertical) { // pass in the pieceVector, char board, x/t coord and if the piece is vertical or not

    if (board.empty() || board[0].empty()) { // check if board is empty if it is return out of function
        return false;
    }

    //initializes rows/cols/and length to use below
    int row = static_cast<int>(board.size());
    int col = static_cast<int>(board[0].size());
    int length = static_cast<int>(pieceVector.size());

    if ((isVertical == false)) { // checks the horizontal bounds of the piece that is being placed

        if (yCoord < 0 || yCoord >= row) {
            return false;
        }
        if (xCoord < 0 || xCoord + length - 1 >= col) {
            return false;
        }
    } else if (isVertical == true) { // checks the vertical bounds of the piece that is being placed
        if (xCoord < 0 || xCoord >= col) {
            return false;
        }

        if (yCoord < 0 || yCoord + length - 1 >= row) {
            return false;
        }
    }
    return true;
}

//function for collsion detector for pieces on the map
bool Board::collides(std::vector<char> &pieceVector, std::vector<std::vector<char> > &board, std::vector<std::vector <int>>& idBoard, int xCoord, int yCoord, bool isVertical) { //passes in the char pieceVector, char board, int idBoard, x/y coord and if piece is vertical
     
    bool collision = false; // assume there is no collision

        if (isInBounds(pieceVector, board, xCoord, yCoord, isVertical) == false) { // call isInBounds to check if our current parameters passed are even in the map, if in bounds returns false (not in map)
            // we have a 'collison' break out of this function
            return true;
        }

        //initlaizes length
        int length = static_cast<int>(pieceVector.size());

        // if piece is horizontal
        if (isVertical == false) {
            //loop through the length of piece
            //and if piece hits a c or k char we hit a piece
            for (int k = 0; k < length; k++) {
                if (board[yCoord][xCoord + k] != '0') return true;
            }

            for (int k = 0; k < length; k++) {
                if (idBoard[yCoord][xCoord + k] != 0) return true;
            }
        }
        // if piece is vetical
        if (isVertical == true) {
            //loop through the length of piece
            //and if piece hits a c or k char we hit a piece
            for (int k = 0; k < length; k++) {
                if (board[yCoord + k][xCoord] != '0') return true;
            }

            for (int k = 0; k < length; k++) {
                if (idBoard[yCoord + k][xCoord] != 0) return true;
            }
        }

        // if we pass the above we have NOT hit another piece
        // return false
        return false;
}


//function to move a selected piece
// pass in the char pieceVector, char board, int idBoard, initial x/y coord and our moving x/y coords (dx/dy)
void Board::movePieceDynamically(std::vector<char>& pieceVector, std:: vector<int> &pieceIdVector, std::vector<std::vector<char>>& board, std::vector<std::vector <int>>& idBoard, int &xCoord, int &yCoord, bool isVertical, int dx, int dy) {
    //create temps board to use within function
    auto &tempBoard = board;
    auto& tempIdBoard = idBoard;

    //initlaize bounds and length
    int rows = board.size();
    int cols = board[0].size();
    int length = pieceVector.size();

    //newly calucalted x/y values useing out anchor x/y coord and dx/dy
    int newX = xCoord + dx;
    int newY = yCoord + dy;


    // if the piece is vertical
    if (isVertical == true) {
        //bounds checker
        if (newY < 0 || (newY + length - 1) >= rows) return;
        if (newX < 0 || newX >= cols) return;
    }

    // if the piece is vertical
    if (isVertical == false) {
        //bounds checker
        if (newX < 0 || (newX + length - 1) >= cols) return;
        if (newY < 0 || newY >= rows) return;
    }

    if (collides(pieceVector, board, idBoard, newX, newY, isVertical) == true) return; // call the collision dectector to see if weve hit a piece
    // if we pass

    //out new anchor coords are newX/newY
    xCoord = newX;
    yCoord = newY;

    // if piece is vertical
    if (isVertical == true) {
        // place piece vertically using new anchor points in char and int board
        for (int k = 0; k < length; k++) {
            tempBoard[yCoord + k][xCoord] = pieceVector[k];
        }

        for (int k = 0; k < length; k++) {
            tempIdBoard[yCoord + k][xCoord] = pieceIdVector[k];
        }
    }

    // if piece is horizontal
    if (isVertical == false) {
        // place piece horizontally using new anchor points in char and int board
        for (int k = 0; k < length; k++) {
            tempBoard[yCoord][xCoord + k] = pieceVector[k];
        }

        for (int k = 0; k < length; k++) {
            tempIdBoard[yCoord][xCoord + k] = pieceIdVector[k];
        }
    }
}

// function to grab a selected piece on the map
HeldPiece Board::grabPiece(std::vector<std::vector<int>> &board, int xCoord, int yCoord) { // passes in the int board and x/y coords
    //inializes the row and cols
    int row = board.size();
    int col = board[0].size();
    HeldPiece result; // create new HeldPiece object called result

    if (yCoord < 0 || yCoord >= row || xCoord < 0 || xCoord >= col) return {}; //out of bounds check 

    int target = board[yCoord][xCoord]; // target id is the x y coord user selected
    if (target == 0) {
        std::cerr << "Selected invalid placement" << std::endl;
        return {};
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

    if (indexPairs.empty()) { // sanity check for if the vector is empty
        std::cerr << "index pair vector is empty returing" << std::endl;
        return {};
    }
    std::pair <int, int> firstPair = indexPairs.front(); // sets the first pair to whatever pair was at the fornt of the vector

    // sets inital x and y to the first pair within the unordered indexPairs
    int initialX = firstPair.first;
    int initialY = firstPair.second;
    int xCounter = 0;
    int yCounter = 0;

    // sets min and max for x/y tothe first pair first and second values
    int minX = firstPair.first;
    int maxX = firstPair.first;
    int minY = firstPair.second;
    int maxY = firstPair.second;

    // for loop to find the max and min x and y values
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

    // for loop to count if x or y values are equal to the size of pairs in vector of pair (indexPairs)
    for (int i = 0; i < static_cast<int>(indexPairs.size()); i++) {
        if (initialX == indexPairs[i].first) { // if we find an x that matches the initial xValue, xcounter++
            xCounter++;
        }

        if (initialY == indexPairs[i].second) {  // if we find an y that matches the initial xValue, ycounter++
            yCounter++;
        }
    }

    // checks if the current sum of xCounter and the length between cols is the same as the amount of pairs in index pairs
    if (xCounter == static_cast<int> (indexPairs.size()) && (maxY - minY + 1) == static_cast<int>(indexPairs.size())) {
        isVertical = true; // if the above is true the piece is vertical
    }

    // checks if the current sum of yCounter and the length between rows is the same as the amount of pairs in index pairs
    if (yCounter == static_cast<int> (indexPairs.size()) && (maxX - minX + 1) == static_cast<int> (indexPairs.size())) {
        isVertical = false; // if the above is true the piece is horizontal
    }


    // bubble sort to sort the paris in order of how they were place on the map
    if (isVertical == true) {
        for (int i = 0; i < static_cast<int>(indexPairs.size()) - 1; i++) {
            for (int j = 0; j < static_cast<int>(indexPairs.size()) - i - 1; j++) {
                if (indexPairs[j].second > indexPairs[j + 1].second)
                std::swap(indexPairs[j], indexPairs[j + 1]);
            }
        }
    }

    // bubble sort to sort the paris in order of how they were place on the map
    if (isVertical == false) {
        for (int i = 0; i < static_cast<int>(indexPairs.size()) - 1; i++) {
            for (int j = 0; j < static_cast<int>(indexPairs.size()) - i - 1; j++) {
                if (indexPairs[j].first > indexPairs[j + 1].first)
                    std::swap(indexPairs[j], indexPairs[j + 1]);
            }
        }
    }

    // pass all of our found values to result which if of struct HeldPiece

    result.originalCells = indexPairs;
    result.cells.clear();
    result.cells.reserve(indexPairs.size());
    for (const auto& pair : indexPairs) {
        result.cells.emplace_back(pair.first - minX, pair.second - minY);
    }

    result.validSelection = true;
    result.pieceId = target;
    result.glyph = grid[yCoord][xCoord];
    result.isVertical = (maxX == minX);
    result.originalAnchorX = minX;
    result.originalAnchorY = minY;
    result.currentX = minX;
    result.currentY = minY;

    // return the newly created struct
    return result;
}

void Board::placeCarPiece(Car &car, std::vector<std::vector<char> > &board, std::vector<std::vector <int>>& idBoard, int xCoord, int yCoord, bool isVertical) {
     if (collides(car.carVector, board, idBoard, xCoord, yCoord, isVertical) == true) {
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

                        if (idBoard[yCoord][xCoord] == 0) {
                            idBoard[yCoord][xCoord] = car.carId;
                        }

                        if (idBoard[yCoord][xCoord + 1] == 0) {
                            idBoard[yCoord][xCoord + 1] = car.carId;
                        }
                  
            } else if ((yCoord >= 0 && yCoord < row) && (xCoord >= 0) && (xCoord - (length - 1) >= 0)) {
                
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord][xCoord - 1] == '0') {
                            board[yCoord][xCoord - 1] = car.carVector[1];
                        }

                        if (idBoard[yCoord][xCoord] == 0) {
                            idBoard[yCoord][xCoord] = car.carId;
                        }

                        if (idBoard[yCoord][xCoord - 1] == 0) {
                            idBoard[yCoord][xCoord - 1] = car.carId;
                        }
            }
        }

        if (isVertical == true) {
            if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord + length - 1 < row)) {
               
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord + 1][xCoord] == '0') {
                            board[yCoord + 1][xCoord] = car.carVector[1];
                        }

                        if (idBoard[yCoord][xCoord] == 0) {
                            idBoard[yCoord][xCoord] = car.carId;
                        }
                        if (idBoard[yCoord + 1][xCoord] == 0) {
                            idBoard[yCoord + 1][xCoord] = car.carId;
                        }

                 
            } else if ((xCoord >= 0 && xCoord < col) && (yCoord >= 0) && (yCoord - (length - 1) >= 0)) {
                
                        if (board[yCoord][xCoord] == '0') {
                            board[yCoord][xCoord] = car.carVector[0];
                        }
                        if (board[yCoord - 1][xCoord] == '0') {
                            board[yCoord - 1][xCoord] = car.carVector[1];
                        }

                        if (idBoard[yCoord][xCoord] == 0) {
                            idBoard[yCoord][xCoord] = car.carId;
                        }
                        if (idBoard[yCoord - 1][xCoord] == 0) {
                            idBoard[yCoord - 1][xCoord] = car.carId;
                        }
            }
        }
        else {
            return;
        }
}

void Board::placeTruckPiece(Truck &truck, std::vector<std::vector<char> > &board, std:: vector<std::vector<int>> &idBoard, int xCoord, int yCoord, bool isVertical) {
     if (collides(truck.truckVector, board, idBoard, xCoord, yCoord, isVertical) == true) {
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

//function to begin a hold of a piece
bool Board::beginHold(int cursorX, int cursorY) { // passes in the current cell at x y value
    HeldPiece hp = grabPiece(idGrid, cursorX, cursorY); // gets the absolute cells from the retunr in grabPiece ex: {(1,1), (1,2), (1,3)}

    if (!hp.validSelection) return false; // if we happen to return empty vector to absCells and absCells is empty we break out of the fuction

    hp.glyph = grid[cursorY][cursorX];

    held = std::move(hp); // hands over ownership of hp values to global held struct

    for (const auto& cell : held.originalCells) {
        const int x = cell.first;
        const int y = cell.second;
        grid[y][x] = '0';
        idGrid[y][x] = 0;
    }

    return true;
}

//function to comminit a hold of piece
void Board::commitHold() {
    if (!held.validSelection) return;

    // for each loop grabs the the normalized cells
    //and adds the current x/y values to it for proper placement
    for (auto& pair : held.cells) {
        int x = held.currentX + pair.first;
        int y = held.currentY + pair.second;

        grid[y][x] = held.glyph;
        idGrid[y][x] = held.pieceId;

    }
    held = {};
}
// function to cancel a hold
//just places the pice hack to its original points
void Board::cancelHold() {
    if (!held.validSelection) return;

    for (auto& pair : held.originalCells) {
        grid[pair.second][pair.first] = held.glyph;
        idGrid[pair.second][pair.first] = held.pieceId;
    }
    held = {};
}