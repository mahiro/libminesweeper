#ifndef _MINESWEEPER_SOLVER_FIELD_H_
#define _MINESWEEPER_SOLVER_FIELD_H_

#include "solver.h"
#include "solver-searcher.h"
#include "solver-result.h"

#include <iostream>

namespace minesweeper {
    namespace solver {
        using namespace minesweeper::core;
        
        class SolverField : public Field {
            friend class SolverCell;
            
            private:
                mutable CellSet unknownCells;
                mutable CellSet frontierCells;
                
                void addFrontierCell(const SolverCell & cell) const;
                void removeFrontierCell(const SolverCell & cell) const;
                void addUnknownCell(const SolverCell & cell) const;
                void removeUnknownCell(const SolverCell & cell) const;
                
            protected:
                virtual void clearUnknowns() const;
                virtual void handleResult(const Searcher & searcher) const;
                
            public:
                explicit SolverField(int _width, int _height, bool _init = true) :
                        Field(_width, _height, false) {
                    if (_init) {
                        constructCells();
                        clearUnknowns();
                    }
                }
                
                virtual ~SolverField() {}
                
                virtual void clearCells() const {
                    Field::clearCells();
                    clearUnknowns();
                }
                
                virtual void resetCells() const {
                    Field::resetCells();
                }
                
                virtual const Cell * createCell(int x, int y) const;
                int countUnknownCells() const;
                int countFrontierCells() const;
                const CellSet & getUnknownCells() const;
                const CellSet & getFrontierCells() const;
                
                void solve(const Cell & startCell, int forwardDepth,
                        int backwardDepth, bool fast = true) const;
                
                void solve(int forwardDepth, int backwardDepth,
                        bool fast = true) const;
                
                
        };
        
        std::ostream & operator << (std::ostream & out, const CellSet & cells);
        std::ostream & operator << (std::ostream & out, const Result & result);
    }
}

#endif
