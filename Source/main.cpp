//
// Created by elder on 8/16/2025.
//
#include <iostream>
#include "../Headers//Board.h"
#include "../Headers/Constants.h"
#include <windows.h>
#include <conio.h>
#undef max
#undef min


int main() {

    bool running = true;
    bool hasPlacedPiece = false;
    Car car;
    bool isVertical = false;      // test vertical-only movement
    int x = 0, y = 1;
    Truck truck(1);
    Board board(BOARD_HEIGHT, BOARD_WIDTH);

    std::cout << "Charater Board" << std::endl;
    board.printBoard();

    std::cout << std::endl;

    std::cout << "ID Board" << std::endl;
    board.printIdBoard();
    
  /*  board.placeTruckPiece(truck, board.grid, idBoard.idGrid, 3, 1, false);*/




    //    while (running && !hasPlacedPiece) {
    //        board.movePieceDynamically(car.carVector, board.grid, x, y, isVertical, 0, 0);

    //        int dx = 0;
    //        int dy = 0;

    //        int ch = _getch();

    //        if (ch == 27) { // ESC
    //            running = false;
    //            break;
    //        }

    //        if (ch == 224) {
    //            int arrow = _getch();
    //            if (isVertical) {
    //                if (arrow == 72) dy -= 1;
    //                if (arrow == 80) dy += 1;
    //            }
    //            else {
    //                if (arrow == 75) dx -= 1;
    //                if (arrow == 77) dx += 1;
    //            }
    //        }

    //        if (ch == 13) {
    //            if (!board.collides(car.carVector, board.grid, x, y, isVertical)) {
    //                const int length = static_cast<int>(car.carVector.size());
    //                if (isVertical) {
    //                    for (int k = 0; k < length; k++) {
    //                        board.grid[y + k][x] = car.carVector[k];
    //                    }
    //                }
    //                else {
    //                    for (int k = 0; k < length; k++) {
    //                        board.grid[y][x + k] = car.carVector[k];
    //                    }
    //                }
    //                hasPlacedPiece = true;
    //                board.printBoard();
    //            }
    //            continue; 
    //        }

    //        if (dx != 0 || dy != 0) {
    //            board.movePieceDynamically(car.carVector, board.grid, x, y, isVertical, dx, dy);
    //        }
    //}
}
