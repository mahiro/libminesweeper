#ifndef _MINESWEEPER_SOLVER_COMMON_H_
#define _MINESWEEPER_SOLVER_COMMON_H_

#include "../core/field.h"
#include "../core/cell.h"
#include <set>

namespace minesweeper {
    namespace solver {
        using namespace minesweeper::core;
        
        class SolverField;
        class SolverCell;
        class BipartiteCells;
        class Searcher;
        class SuspectState;
        class Result;
        
        template <typename T>
        class CombinationGenerator;
        
        typedef std::set<const Cell *> CellSet;
        typedef std::set<const Cell *>::const_iterator CellSetIter;
    }
}

#endif
