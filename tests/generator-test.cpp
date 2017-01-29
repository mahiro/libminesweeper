#include "../minesweeper.h"
#include "test.h"
#include "generator-test.h"

using namespace minesweeper::core;
using namespace minesweeper::generator;

void testGenerate() {
    int sizes[] = {5, 15, 25, 35, 45};
    int rates[] = {5, 15, 25, 50, 90};
    
    for (std::size_t i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int n = sizes[i];
        
        for (std::size_t j = 0; j < sizeof(rates) / sizeof(rates[0]); j++) {
            int rate = rates[j];
            
            int width = n;
            int height = n;
            int numMines = (int) (width * height * rate / 100);
            
            GeneratorField field(width, height);
            
            const Cell & startCell = field.getCell(width / 2, height / 2);
            field.setupSolvable(startCell, numMines, 3, 3);
            
            field.resetCells();
            
            field.solve(startCell, 5, 4);
            assertTrue(field.getPending() == 0 || field.getRest() == 0);
            
            field.clearCells();
            
            const Cell & startCell2 = field.getCell(0, 0);
            field.setupSolvable(startCell2, numMines, 3, 3);
            
            field.resetCells();
            
            field.solve(startCell2, 5, 4);
            assertTrue(field.getPending() == 0 || field.getRest() == 0);
        }
    }
}
