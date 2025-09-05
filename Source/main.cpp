//
// Created by elder on 8/16/2025.
//
#include <iostream>
#include "../Headers/Board.h"
#include "../Headers/Constants.h"
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <cstdio>
#undef max
#undef min

int main() {

    enum GameState {
        Playing,
        Won,
        PackComplete
    };

    GameState state = Playing;

    int currentLevel = 0;
    int currentMoves = 0;
    using clock_t = std::chrono::steady_clock;
    using secondsDuration = std::chrono::duration<double>;
    clock_t::time_point levelStart;
    secondsDuration elapsedBeforePause{ 0.0 };
    bool isTimerRunning = false;
    double lastLevelTimeSeconds = 0.0;
    auto lastFrame = clock_t::now();
    const auto frameTime = std::chrono::milliseconds(100);

    bool running = true;
    Board board(BOARD_HEIGHT, BOARD_WIDTH);

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
        std::cout << "Current moves: " << currentMoves << std::endl;
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

                if (px >= board.width) {
                    board.grid[py][px - 1] = '0';
                    board.idGrid[py][px - 1] = 0;
                    return;
                }

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

                if (px >= board.width) {
                    board.grid[py][px - 1] = board.held.glyph;
                    board.idGrid[py][px - 1] = board.held.pieceId;
                    return;
                }

                board.grid[py][px] = board.held.glyph;
                board.idGrid[py][px] = board.held.pieceId;
            }
        }
        };

    auto loadLevelIndex = [&](int index) {
        if (isHolding) erasePreview();
        isHolding = false;
        previewGlyphs.clear();
        previewIds.clear();
        previewLen = 0;

        board.loadLevel(levelAt(index));
        cursorX = 0;
        cursorY = 0;
        state = GameState::Playing;
        board.hasWon = false;
        currentMoves = 0;

        redraw();
        };

    loadLevelIndex(currentLevel);

    redraw();

    while (running) {

            int ch = _getch();

            if (state == GameState::PackComplete && ch == 'r' || ch == 'R') {
                currentLevel = 0;
                loadLevelIndex(currentLevel);
                state = GameState::Playing;
                board.hasWon = false;
                redraw();
            }

            if (ch == 27 && state == GameState::Won || state == GameState::PackComplete) { // ESC key
                if (isHolding) { // if we are holding a piece and press esc
                    // return piece back to its inital state it was grabbed at
                    int ax = board.held.currentX;      // or board.held.originalAnchorX
                    int ay = board.held.currentY;
                    cursorX = ax;
                    cursorY = ay;
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
            if (ch == 224 && state == GameState::Playing) {
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

                    if (state != GameState::Playing) {
                        redraw();
                        continue;
                    };

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

                    //
                    int oldX = board.held.currentX;
                    int oldY = board.held.currentY;

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

                    if (board.hasWon == true) {
                        auto now = clock_t::now();
                        lastLevelTimeSeconds = std::chrono::duration_cast<secondsDuration>((now - levelStart) + elapsedBeforePause).count();
                        isTimerRunning = false;
                        erasePreview();
                        isHolding = false;
                        previewGlyphs.clear();
                        previewIds.clear();
                        previewLen = 0;
                        state = GameState::Won;

                        // Optional: print a banner line before redraw()
                        std::cout << std::endl;
                        std::cout << "Solved: " << currentLevel + 1 << " out of " << levelCount() << " levels! Press Enter for next level." << std::endl;
                        continue;
                    }

                    // if anchor changed, follow it with the highlight
                    if (board.held.currentX != oldX || board.held.currentY != oldY) {
                        cursorX = board.held.currentX;
                        cursorY = board.held.currentY;
                    }

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

                if (state == GameState::Playing) {
                    if (!isHolding) {
                        // Try to start holding a piece under the cursor
                        if (board.beginHold(cursorX, cursorY)) {
                            isHolding = true;
                            currentMoves++;

                            //syncs the cursor to the current held x/y coord
                            cursorX = board.held.currentX;
                            cursorY = board.held.currentY;

                            // Build preview payload once from held footprint length
                            previewLen = board.held.cells.size();
                            previewGlyphs.assign(previewLen, board.held.glyph);
                            previewIds.assign(previewLen, board.held.pieceId);

                            drawPreview();

                            // Draw initial preview at current anchor
                            drawPreview();
                        }
                        else {
                            std::cout << "No piece at (" << cursorX << "," << cursorY << ") to grab" << std::endl;
                            Sleep(750);
                        }
                    }
                    else {
                        // Commit the held piece to its current spot
                        int ax = board.held.currentX;
                        int ay = board.held.currentY;

                        // Commit the held piece to its current spot
                        erasePreview();          // remove preview
                        board.commitHold();      // write permanent cells

                        // keep highlight where the piece landed
                        cursorX = ax;
                        cursorY = ay;


                        previewGlyphs.clear();
                        previewIds.clear();
                        previewLen = 0;
                        isHolding = false;
                    }
                    redraw();
                    continue;
                }
                else if (state == GameState::Won) {
                    if (currentLevel + 1 < levelCount()) {
                        currentLevel = nextIndex(currentLevel);
                        loadLevelIndex(currentLevel);
                    }
                    else {
                        state = GameState::PackComplete;
                        std::cout << std::endl;
                        std::cout << "Pack complete! Press R to restart." << std::endl;
                    }
                    continue;
                }
        }
    }
    return 0;
}