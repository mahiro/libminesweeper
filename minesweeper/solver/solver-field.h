#ifndef _MINESWEEPER_SOLVER_FIELD_H_
#define _MINESWEEPER_SOLVER_FIELD_H_

#include "common.h"
#include "searcher.h"
#include "result.h"

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
				virtual void handleResult(const Result & result) const;
				
			public:
				explicit SolverField(int _width, int _height, bool _init = true) :
						Field(_width, _height, false) {
					if (_init) {
						constructCells();
						clearUnknowns();
					}
				}
				
				virtual const Cell * createCell(int x, int y) const;
				virtual void clearCells() const;
				int countUnknownCells() const;
				int countFrontierCells() const;
				const CellSet & getUnknownCells() const;
				const CellSet & getFrontierCells() const;
				
				void solve(const Cell & startCell, int forwardDepth,
						int backwardDepth, bool fast = true) const;
				
				void solve(int forwardDepth, int backwardDepth,
						bool fast = true) const;
				
		};
	}
}

#endif
