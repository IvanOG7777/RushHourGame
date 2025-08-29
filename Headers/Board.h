//
// Created by elder on 8/18/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include "../Headers/Car.h"
#include "../Headers/Truck.h"
#include <vector>

struct HeldPiece {

    bool validSelection = false; // validation to check if we can place the piece
    int pieceId = 0; // id from the id Board
    char glyph = '0'; // charater from the charater board
    bool isVertical = false; // checks if piece is vertical or not

    int originalAnchorX = 0; // holds the original x coord
    int originalAnchorY = 0; // holds the original y coord

    std::vector<std::pair<int, int>> originalCells; // vector that holds the original vector if pairs from the selected piece

    int currentX = 0; // holds the current x coord, constantly changing when moving a piece
    int currentY = 0; // holds the current y coord, constantly changing when moving a piece
    std::vector<std::pair<int, int>> cells; // holds the normalized vector of pairs from the piece
};

class Board {
    public:

        int height;
        int width;
        std:: vector<std:: vector<char>> grid;
        std:: vector<std::vector<int>> idGrid;
        Board(int height, int width);
        
        HeldPiece held;
        
        void printBoard();
        
        void printIdBoard();
        
        bool isInBounds(
            std::vector<char>
            &pieceVector, std::vector<std::vector<char>> &board,
            int xCoord,
            int yCoord,
            bool isVertical
        );
        
        bool collides(
            std:: vector<char> &pieceVector,
            std::vector<std::vector<char>> &board,
            std:: vector<std:: vector <int>> &idBoard,
            int xCoord,
            int yCoord,
            bool isVertical
        );
        
        void placeCarPiece(
            Car &car,
            std::vector<std::vector<char>> &board,
            std::vector<std::vector <int>>& idBoard,
            int xCoord,
            int yCoord,
            bool isVertical
        );
        
        void placeTruckPiece(
            Truck &truck,
            std::vector<std::vector<char>> &board,
            std::vector<std::vector<int>> &idBoard,
            int xCoord,
            int yCoord,
            bool isVertical
        );
        
        void movePieceDynamically(
            std::vector<char>& pieceVector,
            std::vector<std::vector<char>>& board,
            std::vector<std::vector <int>>& idBoard,
            int &xCoord,
            int &yCoord,
            bool isVertical,
            int dx,
            int dy
        );
        
        HeldPiece grabPiece(
            std::vector<std::vector<int>>& board,
            int xCoord,
            int yCoord
        );
        
        bool beginHold(
            int cursorX,
            int cursorY
        );
        
        void updateHoldMove(
            int dx, 
            int dy
        );
        
        bool canPlaceHeldAt(
            int anchorX, 
            int anchorY
        ) const;
        
        void commitHold();
        
        void cancelHold();

private:
    std:: vector<std:: vector<char>> initializeBoard();
    
    std:: vector<std:: vector<int>> initializeIdBoard();
};

#endif //BOARD_H