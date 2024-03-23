#include "cell.h"

Cell::Cell(bool alive) : alive(alive) {

}

bool Cell::isAlive() {
    return alive;
}

void Cell::reborn() {
    alive = true;
}

void Cell::die() {
    alive = false;
}
