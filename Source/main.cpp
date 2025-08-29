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
    Truck truck2(2); 
    Board board(BOARD_HEIGHT, BOARD_WIDTH);

    board.placeTruckPiece(truck, board.grid, board.idGrid, 3, 1, false);
    board.placeTruckPiece(truck2, board.grid, board.idGrid, 0, 0, true);



    int cursorX = 0;
    int cursorY = 0;
    bool isHolding = false;

    auto redraw = [&]() {
        system("cls");
        std::cout << "Use arrow keys to move cursor. Enter=Grab/PLace, Esc =Cancel" << std::endl;
        std::cout << "Cursor at (" << cursorX << "," << cursorY << ") | " << (isHolding ? "[Holding]" : "[Idle]") << std::endl;
        std::cout << std::endl;

        board.printBoard();
        std::cout << "Id board" << std::endl;
        board.printIdBoard();
    };

    redraw();

    while (running) {
        int ch = _getch();

        if (ch == 27) {
            if (isHolding) {
                board.cancelHold();
                isHolding = false;
                redraw();
            }
            else {
                running = false;
            }
            continue;
        }

        if (ch == 224) {
            int arrow = _getch();

            if (!isHolding) {
                if (arrow == 72 && cursorY > 0) cursorY--;
                if (arrow == 80 && cursorY < BOARD_HEIGHT) cursorY++;
                if (arrow == 75 && cursorX > 0) cursorX--;
                if (arrow == 77 && cursorX < BOARD_WIDTH) cursorX++;
            }
            else {
                int dx = 0;
                int dy = 0;
                if (arrow == 72) dy = -1;
                if (arrow == 80) dy = +1;
                if (arrow == 75) dx = -1;
                if (arrow == 77) dx = +1;

                board.updateHoldMove(dx, dy);
            }
            redraw();
            continue;
        }

        if (ch == 13) {
            if (!isHolding) {
                if (board.beginHold(cursorX, cursorY)) {
                    isHolding = true;
                }
                else {
                    std::cout << "No piece at (" << cursorX << "," << cursorY << ") to grab" << std::endl;
                    Sleep(500);
                }
            }
            else {
                board.commitHold();
                isHolding = false;
            }
            redraw();
            continue;
        }
    }

    return 0;

}