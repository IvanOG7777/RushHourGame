//
// Created by elder on 8/16/2025.
//
#include <iostream>
#include "../Headers//Board.h"
#include "../Headers/Constants.h"

int main() {
    Car car;
    Truck truck;


    std::cout << "Initialized Board game" << std::endl;
    Board board(BOARD_HEIGHT, BOARD_WIDTH);

    board.printBoard();

    std::cout << std::endl;


    board.placeCarPiece(car, board.grid, 0, 0, false);
    board.placeCarPiece(car, board.grid, 1, 1, true);
    board.placeCarPiece(car, board.grid, 5, 0, true);
    

    board.placeTruckPiece(truck, board.grid, 0, 2, true);
    board.placeTruckPiece(truck, board.grid, 5, 5, false);


    board.printBoard();
}
