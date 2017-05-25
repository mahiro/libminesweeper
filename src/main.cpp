#include "minesweeper.h"
#include <iostream>

int main(int argc, char * argv[]) {
    using namespace minesweeper::core;
    using namespace minesweeper::solver;
    using namespace minesweeper::generator;
    
    int w = 15;
    int h = 15;
    GeneratorField field(w, h);
    const Cell & startCell = field.getCell((w + 1) / 2, (h + 1) / 2);
    
    field.setupSolvable(startCell, 45, 4, 4);
    field.resetCells();
    startCell.dig();
    std::cout << field << std::endl;
    
    return 0;
}
