//
// Created by elder on 8/16/2025.
//
#include <iostream>
#include "../Headers/Board.h"
#include "../Headers/Constants.h"
#include <windows.h>
#include <conio.h>
#undef max
#undef min

int main() {
    bool running = true;
    Board board(BOARD_HEIGHT, BOARD_WIDTH);

    // Demo pieces
    Truck truck1(1);
    Truck truck2(2);
    Car car1(3);
    Car car2(4);
    board.placeTruckPiece(truck1, board.grid, board.idGrid, 3, 1, false);
    board.placeTruckPiece(truck2, board.grid, board.idGrid, 0, 0, true);
    board.placeCarPiece(car1, board.grid, board.idGrid, 2, 2, true);
    board.placeCarPiece(car2, board.grid, board.idGrid, 5, 3, false);

    // Cursor + hold state
    int cursorX = 0, cursorY = 0;
    bool isHolding = false;

    // Preview buffers (what we draw as the piece while it's being moved)
    std::vector<char> previewGlyphs;
    std::vector<int>  previewIds;
    size_t previewLen = 0;

    //lambda function
    auto redraw = [&]() {
        system("cls");
        std::cout << "Use arrow keys to move cursor. Enter=Grab/Place, Esc=Cancel" << std::endl;
        std::cout << "Cursor at (" << cursorX << "," << cursorY << ") | "
            << (isHolding ? "[Holding]" : "[Idle]") << std::endl;
        std::cout << std::endl;
        board.printBoard(cursorX, cursorY);
        std::cout << "ID Board" << std:: endl;
        board.printIdBoard();
        };


    //lambda function
    auto erasePreview = [&]() {
        if (!isHolding || previewLen == 0) return;
        // Clear current preview from boards using held.currentX/currentY & orientation

        if (board.held.isVertical) {
            for (auto& pair : board.held.cells) {
                int px = board.held.currentX;
                int py = board.held.currentY + pair.second;

                board.grid[py][px] = '0';
                board.idGrid[py][px] = 0;
            }
        }
        else {
            for (auto& pair : board.held.cells) {
                int px = board.held.currentX + pair.first;
                int py = board.held.currentY;

                board.grid[py][px] = '0';
                board.idGrid[py][px] = 0;
            }
        }
        };

    //lambda function
    auto drawPreview = [&]() {
        if (!isHolding || previewLen == 0) return;

        if (board.held.isVertical) {
            for (auto& pair : board.held.cells) {
                int px = board.held.currentX;
                int py = board.held.currentY + pair.second;

                board.grid[py][px] = board.held.glyph;
                board.idGrid[py][px] = board.held.pieceId;
            }
        }
        else {
            for (auto& pair : board.held.cells) {
                int px = board.held.currentX + pair.first;
                int py = board.held.currentY;

                board.grid[py][px] = board.held.glyph;
                board.idGrid[py][px] = board.held.pieceId;
            }
        }
        };

    redraw();

    while (running) {
        int ch = _getch();

        if (ch == 27) { // ESC key
            if (isHolding) { // if we are holding a piece and press esc
                // return piece back to its inital state it was grabbed at
                erasePreview();
                board.cancelHold();
                previewGlyphs.clear();
                previewIds.clear();
                previewLen = 0;
                isHolding = false;
                redraw();
            }
            else { // else close the game
                running = false; 
            }
            continue; // skip all of the below
        }

        // Arrow keys
        if (ch == 224) {
            int arrow = _getch();

            if (!isHolding) {
                // Move cursor (keep within bounds)
                if (arrow == 72 && cursorY > 0) cursorY--;                           // Up
                if (arrow == 80 && cursorY < BOARD_HEIGHT - 1) cursorY++;            // Down
                if (arrow == 75 && cursorX > 0) cursorX--;                            // Left
                if (arrow == 77 && cursorX < BOARD_WIDTH - 1) cursorX++;            // Right
                redraw();
            }
            else {
                // Move the held piece preview (axis-limited)
                int dx = 0, dy = 0;
                if (board.held.isVertical) {
                    if (arrow == 72) dy = -1;   // Up
                    if (arrow == 80) dy = +1;   // Down
                }
                else {
                    if (arrow == 75) dx = -1;   // Left
                    if (arrow == 77) dx = +1;   // Right
                }

                if (dx == 0 && dy == 0) {
                    redraw();
                    continue;
                }

                // 1) erase old preview from boards
                erasePreview();

                // 2) ask board to move & draw the new preview in place
                board.movePieceDynamically(
                    previewGlyphs,            // glyphs for each cell of the held piece
                    previewIds,               // ids for each cell of the held piece
                    board.grid,
                    board.idGrid,
                    board.held.currentX,      // updated by ref on a legal move
                    board.held.currentY,      // updated by ref on a legal move
                    board.held.isVertical,
                    dx,
                    dy
                );

                drawPreview();

                // If move was illegal, nothing changed and cells remain cleared;
                // so redraw to reflect it. If legal, movePieceDynamically wrote
                // the new preview already.
                redraw();
            }
            continue;
        }

        // ENTER
        if (ch == 13) {
            if (!isHolding) {
                // Try to start holding a piece under the cursor
                if (board.beginHold(cursorX, cursorY)) {
                    isHolding = true;

                    // Build preview payload once from held footprint length
                    previewLen = board.held.cells.size();
                    previewGlyphs.assign(previewLen, board.held.glyph);
                    previewIds.assign(previewLen, board.held.pieceId);

                    // Draw initial preview at current anchor
                    drawPreview();
                }
                else {
                    std::cout << "No piece at (" << cursorX << "," << cursorY << ") to grab" << std::endl;
                    Sleep(500);
                }
            }
            else {
                // Commit the held piece to its current spot
                erasePreview();          // remove preview
                board.commitHold();      // write permanent cells
                previewGlyphs.clear();
                previewIds.clear();
                previewLen = 0;
                isHolding = false;
            }
            redraw();
            continue;
        }
    }
    return 0;
}
