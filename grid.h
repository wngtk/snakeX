#ifndef GRID_H
#define GRID_H

#include "cell.h"

#include <cstdlib>
#include <vector>

class Grid {
public:

    Grid(int size) : _grid(size) {
        srand(0);
        for (int row = 0; row < size; row++) {
            for (int i = 0; i < size; i++) {
                double probability = rand() * 1.0 / RAND_MAX;
                Cell cell;
                if (probability < 0.2) {
                    cell.reborn();
                }
                _grid[row].push_back(Cell(false));
            }
        }
    }

    auto size() { return _grid.size(); }

    std::vector<Cell>& operator[](int row) { return _grid[row]; }

    int live_neighour(int row, int col) {
        int locs[][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0 , -1},          { 0, 1},
            {1 , -1}, { 1, 0}, { 1, 1},
        };
        int n = 0;
        for (int i = 0; i < sizeof(locs)/sizeof(locs[0]); i++) {
            int r = row + locs[i][0];
            int c = col + locs[i][1];

            if (r >= 0 && c >= 0 && r < size() && c < size() && _grid[r][c].isAlive()) {
                n++;
            }
        }

        return n;
    }

    void clear() {
        for (int row = 0; row < size(); row++) {
            for (int i = 0; i < size(); i++) {
                (*this)[row][i].die();
            }
        }
    }

private:
    std::vector<std::vector<Cell>> _grid;
};

#endif // GRID_H
