#ifndef _MINESWEEPER_GENERATOR_H_
#define _MINESWEEPER_GENERATOR_H_

#include "solver.h"

namespace minesweeper {
    namespace generator {
        using namespace minesweeper::core;
        using namespace minesweeper::solver;
        
        class GeneratorField;
        class GeneratorCell;
        
        class RecordState;
        class Swapper;
    }
}

#include "generator-field.h"
#include "generator-cell.h"

#endif
