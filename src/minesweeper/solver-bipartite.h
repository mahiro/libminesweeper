#ifndef _MINESWEEPER_SOLVER_BIPARTITE_H_
#define _MINESWEEPER_SOLVER_BIPARTITE_H_

#include "solver.h"

namespace minesweeper {
    namespace solver {
        using namespace minesweeper::core;
        
        class BipartiteCells {
            private:
                mutable CellSet redCells;
                mutable CellSet blueCells;
                
            public:
                explicit BipartiteCells() : redCells(), blueCells() {}
                
                explicit BipartiteCells(const CellSet & _redCells, const CellSet & _blueCells) :
                    redCells(_redCells), blueCells(_blueCells) {}
                
                CellSet & getRedCells() const {
                    return redCells;
                }
                
                CellSet & getBlueCells() const {
                    return blueCells;
                }
                
                CellSet & getRedOrBlueCells(bool forRed) const {
                    return forRed ? redCells : blueCells;
                }
                
        };
    }
}

#endif
