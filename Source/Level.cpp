#include "../Headers/Level.h"
#include "../Headers/Constants.h"
#include <vector>
#include <stdexcept>


//vector of levels of Type Level
static const std::vector<Level> levels = {
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  3, 2, 2, false },
        { PieceKind::Truck,   1, 0, 0, true  },
        { PieceKind::Truck,   2, 3, 1, false },
        { PieceKind::Car,     4, 2, 3, true  },
    }},
     Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar, 10, 1, 2, false },
        { PieceKind::Truck,  11, 0, 0, true  },
        { PieceKind::Truck,  12, 4, 0, true  },
        { PieceKind::Car,    13, 3, 3, false },
        { PieceKind::Car,    14, 0, 4, false },
    }}
};

int levelCount() {
    return static_cast<int> (levels.size());
}

const Level& levelAt(int index) {
    if (index < 0 || index >= static_cast<int>(levels.size())) {
        throw std::out_of_range("Levels::levelAt index out of range");
    }
    return levels[static_cast<size_t>(index)];
}

bool hasLevel(int index) {
    return index >= 0 && index < static_cast<int>(levels.size());
}

int nextIndex(int index) {

    if (index + 1 < static_cast<int>(levels.size())) {
        return index + 1;
    }
    else {
        return index;
    }
}