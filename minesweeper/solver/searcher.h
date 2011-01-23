#ifndef _MINESWEEPER_SOLVER_SEARCHER_H_
#define _MINESWEEPER_SOLVER_SEARCHER_H_

#include "common.h"
#include "bipartite.h"
#include "result.h"

namespace minesweeper {
	namespace solver {
		using namespace minesweeper::core;
		
		class Searcher {
			private:
				const SolverField & field;
				mutable Result * result;
				
				bool traverseForward(const CellSet & currentCells,
						const BipartiteCells & input,
						const BipartiteCells & marking,
						bool forRed, int depthLeft) const;
				
				bool traverseForwardInternal(const CellSet & currentCells,
						const BipartiteCells & input,
						const BipartiteCells & marking,
						bool nextForRed, int depthLeft) const;
				
				bool traverseBackwardFast(int depthLeft) const;
				bool traverseBackward(int depthLeft) const;
				
			public:
				explicit Searcher(const SolverField & _field) :
						field(_field), result(0) {}
				
				virtual ~Searcher() {
					if (result) {
						delete result;
					}
				}
				
				bool searchForward(int depth) const;
				bool searchBackward(int depth, bool fast = true) const;
				bool searchSingle() const;
				bool searchDouble() const;
				bool searchMultiple(int depth) const;
				bool searchSingle(const Cell & targetCell) const;
				bool searchDouble(const Cell & targetCell) const;
				bool searchMultiple(const Cell & targetCell, int depth) const;
				
				const SolverField & getField() const {
					return field;
				}
				
				bool hasResult() const {
					return result != 0;
				}
				
				const Result & setResultFound(bool backward) const {
					if (!result) {
						result = new Result(field, backward);
					}
					
					return *result;
				}
				
				const Result & getResult() const {
					return *result;
				}
				
				void resetResult() const {
					if (result) {
						delete result;
						result = 0;
					}
				}
				
		};
	}
}

#endif
