#include "../Headers/Level.h"
#include "../Headers/Constants.h"
#include <vector>
#include <stdexcept>

const int REDCARID = 1;


//vector of levels of Type Level
static const std::vector<Level> levels = {

    //L1
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 1, 2, false },
        { PieceKind::Truck,   2, 0, 1, true},
        { PieceKind::Car,     3, 0, 4, true},
        { PieceKind::Truck,   4, 3, 1, true},
        { PieceKind::Car,     5, 4, 4, false},
        { PieceKind::Truck,   6, 2, 5, false},
        { PieceKind::Car,     7, 4, 4, false},
        { PieceKind::Car,     8, 0, 0, false},
    }},

    //L2
     Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar, REDCARID, 1, 2, false },
        { PieceKind::Truck,  2, 0, 0, true  },
        { PieceKind::Truck,  3, 4, 0, true  },
        { PieceKind::Car,    4, 3, 3, false },
        { PieceKind::Car,    5, 0, 4, false },
    }},

    // L3
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 1, 2, false },
        { PieceKind::Truck,   3, 0, 0, true  },
        { PieceKind::Truck,   4, 4, 0, true  },
        { PieceKind::Car,     5, 0, 3, false },
        { PieceKind::Car,     6, 2, 0, true  },
        { PieceKind::Car,     7, 3, 4, false },
        { PieceKind::Car,     8, 5, 1, true  },
    }},
    // L4
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 2, 2, false },
        { PieceKind::Truck,   31, 0, 0, true  },
        { PieceKind::Truck,   32, 1, 0, false },
        { PieceKind::Truck,   33, 5, 0, true  },
        { PieceKind::Car,     34, 0, 3, true  },
        { PieceKind::Car,     35, 2, 4, false },
        { PieceKind::Car,     36, 3, 1, false },
    }},
    // L5
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 0, 2, false },
        { PieceKind::Truck,   41, 2, 0, true  },
        { PieceKind::Truck,   42, 4, 1, true  },
        { PieceKind::Car,     43, 1, 0, false },
        { PieceKind::Car,     44, 5, 3, true  },
        { PieceKind::Car,     45, 3, 4, false },
        { PieceKind::Car,     46, 0, 4, true  },
    }},
    // L6
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 3, 2, false },
        { PieceKind::Truck,   51, 5, 0, true  },
        { PieceKind::Truck,   52, 0, 0, true  },
        { PieceKind::Car,     53, 1, 0, false },
        { PieceKind::Car,     54, 2, 3, true  },
        { PieceKind::Car,     55, 0, 5, false },
        { PieceKind::Car,     56, 4, 3, true  },
    }},
    // L7
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 1, 2, false },
        { PieceKind::Truck,   61, 0, 0, false },
        { PieceKind::Truck,   62, 3, 0, true  },
        { PieceKind::Truck,   63, 5, 2, true  },
        { PieceKind::Car,     64, 0, 3, true  },
        { PieceKind::Car,     65, 2, 4, false },
        { PieceKind::Car,     66, 3, 5, false },
    }},
    // L8
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 2, 2, false },
        { PieceKind::Truck,   71, 0, 1, true  },
        { PieceKind::Truck,   72, 1, 0, false },
        { PieceKind::Truck,   73, 4, 2, true  },
        { PieceKind::Car,     74, 5, 0, true  },
        { PieceKind::Car,     75, 0, 4, false },
        { PieceKind::Car,     76, 2, 5, false },
    }},
    // L9
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 3, 2, false },
        { PieceKind::Truck,   81, 1, 0, true  },
        { PieceKind::Truck,   82, 2, 0, false },
        { PieceKind::Truck,   83, 5, 1, true  },
        { PieceKind::Car,     84, 0, 3, true  },
        { PieceKind::Car,     85, 3, 4, false },
        { PieceKind::Car,     86, 2, 3, true  },
    }},
    // L10
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar,  REDCARID, 0, 2, false },
        { PieceKind::Truck,   91, 5, 0, true  },
        { PieceKind::Truck,   92, 3, 0, true  },
        { PieceKind::Truck,   93, 0, 0, false },
        { PieceKind::Car,     94, 2, 4, false },
        { PieceKind::Car,     95, 1, 3, true  },
        { PieceKind::Car,     96, 4, 3, true  },
    }},
    // L11
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar, REDCARID, 2, 2, false },
        { PieceKind::Truck,  101, 0, 0, true  },
        { PieceKind::Truck,  102, 1, 0, false },
        { PieceKind::Truck,  103, 5, 1, true  },
        { PieceKind::Car,    104, 3, 3, true  },
        { PieceKind::Car,    105, 2, 4, false },
        { PieceKind::Car,    106, 4, 1, true  },
    }},
    // L12
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar, REDCARID, 1, 2, false },
        { PieceKind::Truck,  111, 0, 0, true  },
        { PieceKind::Truck,  112, 5, 0, true  },
        { PieceKind::Truck,  113, 2, 0, false },
        { PieceKind::Car,    114, 3, 3, true  },
        { PieceKind::Car,    115, 0, 4, false },
        { PieceKind::Car,    116, 2, 5, false },
    }},
    // L13
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar, REDCARID, 4, 2, false },
        { PieceKind::Truck,  121, 5, 0, true  },
        { PieceKind::Truck,  122, 2, 0, true  },
        { PieceKind::Truck,  123, 0, 0, false },
        { PieceKind::Car,    124, 3, 4, false },
        { PieceKind::Car,    125, 1, 3, true  },
        { PieceKind::Car,    126, 0, 5, false },
    }},
    // L14
    Level{ BOARD_WIDTH, BOARD_HEIGHT, {
        { PieceKind::RedCar, REDCARID, 1, 2, false },
        { PieceKind::Truck,  131, 3, 0, true  },
        { PieceKind::Truck,  132, 5, 1, true  },
        { PieceKind::Truck,  133, 0, 0, false },
        { PieceKind::Car,    134, 0, 3, true  },
        { PieceKind::Car,    135, 2, 4, false },
        { PieceKind::Car,    136, 4, 5, false },
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