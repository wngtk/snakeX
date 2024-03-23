#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell(bool alive = false);
    bool isAlive();

    void reborn();

    void die();

private:
    bool alive = false;

};

#endif // CELL_H
