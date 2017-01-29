#ifndef _MINESWEEPER_GENERATOR_COMMON_H_
#define _MINESWEEPER_GENERATOR_COMMON_H_

#include "../core/common.h"
#include "../solver/common.h"

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

#endif
