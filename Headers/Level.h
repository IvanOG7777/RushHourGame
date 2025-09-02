#ifndef LEVEL_H
#define LEVEL_H

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

#endif //LEVEL_H
