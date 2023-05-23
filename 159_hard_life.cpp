#include <iostream>
#include <vector>
#include <unordered_set>

struct Cell {
    int x;
    int y;
    
    Cell(int x, int y) : x(x), y(y) {}
    
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

struct CellHash {
    std::size_t operator()(const Cell& cell) const {
        std::size_t xHash = std::hash<int>{}(cell.x);
        std::size_t yHash = std::hash<int>{}(cell.y);
        return xHash ^ (yHash << 1);
    }
};

std::vector<Cell> getGliderCells(int x, int y) {
    return {
        Cell(x, y),
        Cell(x + 1, y),
        Cell(x + 2, y),
        Cell(x + 2, y + 1),
        Cell(x + 1, y + 2)
    };
}

std::vector<Cell> getNextGeneration(const std::vector<Cell>& cells) {
    std::unordered_set<Cell, CellHash> cellSet;
    std::unordered_set<Cell, CellHash> newCells;

    for (const Cell& cell : cells) {
        cellSet.insert(cell);
    }

    for (const Cell& cell : cells) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = cell.x + dx;
                int ny = cell.y + dy;
                int neighborCount = 0;

                for (int nx2 = nx - 1; nx2 <= nx + 1; ++nx2) {
                    for (int ny2 = ny - 1; ny2 <= ny + 1; ++ny2) {
                        if (nx2 != nx || ny2 != ny) {
                            if (cellSet.count(Cell(nx2, ny2)) > 0) {
                                ++neighborCount;
                            }
                        }
                    }
                }

                if (cellSet.count(Cell(nx, ny)) > 0) {
                    if (neighborCount == 2 || neighborCount == 3) {
                        newCells.insert(Cell(nx, ny));
                    }
                } else {
                    if (neighborCount == 3) {
                        newCells.insert(Cell(nx, ny));
                    }
                }
            }
        }
    }

    return std::vector<Cell>(newCells.begin(), newCells.end());
}

int main() {
    int gliderX, gliderY;
    std::cin >> gliderX >> gliderY;

    std::vector<Cell> glider = getGliderCells(gliderX, gliderY);
    std::vector<Cell> cells = glider;

    int generation = 0;
    std::unordered_set<Cell, CellHash> prevCellSet;

    while (generation < 5 || cells != std::vector<Cell>(prevCellSet.begin(), prevCellSet.end())) {
        prevCellSet.clear();

        for (const Cell& cell : cells) {
            prevCellSet.insert(cell);
        }

        cells = getNextGeneration(cells);
        ++generation;
    }

    std::cout << generation << " " << cells.size() << std::endl;

    return 0;
}
