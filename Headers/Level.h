#ifndef LEVEL_H
#define LEVEL_H
#include <vector>

enum class PieceKind {
    Car,
    Truck,
    RedCar,
};

struct LevelPiece {
    PieceKind kind;
    int id;
    int x, y;
    bool isVertical;
};

struct Level {
    int width, height;
    std::vector<LevelPiece> pieces;
};

int levelCount();

const Level &levelAt(int index);

bool hasLevel(int index);

int nextIndex(int index);

#endif //LEVEL_H