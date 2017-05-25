#ifndef _MINESWEEPER_SOLVER_H_
#define _MINESWEEPER_SOLVER_H_

#include "core.h"
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

#include "solver-field.h"
#include "solver-cell.h"

#endif
