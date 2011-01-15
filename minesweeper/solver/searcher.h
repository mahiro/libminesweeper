#ifndef _MINESWEEPER_SOLVER_SEARCHER_H_
#define _MINESWEEPER_SOLVER_SEARCHER_H_

#include "common.h"
#include "bipartite.h"

namespace minesweeper {
	namespace solver {
		using namespace minesweeper::core;
		
		class Searcher {
			private:
				const SolverField & field;
				mutable BipartiteCells * input;
				mutable BipartiteCells * output;
				const bool backward;
				mutable bool found;
				
//				bool traverseForward(const CellSet & currentCells,
//						const BipartiteCells & input,
//						const BipartiteCells & marking,
//						bool forRed, int depthLeft) const;
//				
//				bool traverseForwardInternal(const CellSet & currentCells,
//						const BipartiteCells & input,
//						const BipartiteCells & marking,
//						bool nextForRed, int depthLeft) const;
//				
//				bool traverseBackwardFast(int depthLeft) const;
//				bool traverseBackward(int depthLeft) const;
				
			public:
				explicit Searcher(const SolverField & _field) :
						field(_field),
						input(0), output(0),
						backward(false), found(false) {}
				
				bool searchForward(int depth) const;
//				bool searchBackward(int depth, bool fast = true) const;
				bool searchBySinglePoint() const;
				bool searchByDoublePoints() const;
//				bool searchByMultiplePoints(int depth) const;
				bool searchBySinglePoint(const Cell & targetCell) const;
				bool searchByDoublePoints(const Cell & targetCell) const;
				
//				bool searchByMultiplePoints(const Cell & targetCell,
//						int depth) const;
				
				virtual ~Searcher() {
					if (input) {
						delete input;
					}
					
					if (output) {
						delete output;
					}
				}
				
				bool hasResult() const {
					return found;
				}
				
				void setResultFound() const {
					if (!found) {
						input = new BipartiteCells();
						output = new BipartiteCells();
						found = true;
					}
				}
				
				void resetResult() const {
					if (found) {
						delete input;
						delete output;
						found = false;
					}
				}
				
//				const BipartiteCells & getInput() const {
//					return &const_cast<const BipartiteCells *>(input);
//				}
//				
//				const BipartiteCells & getOutput() const {
//					return &const_cast<const BipartiteCells *>(output);
//				}
				
				CellSet & getInputRedCells() const {
					return input->getRedCells();
				}
				
				CellSet & getInputBlueCells() const {
					return input->getBlueCells();
				}
				
				CellSet & getOutputRedCells() const {
					return output->getRedCells();
				}
				
				CellSet & getOutputBlueCells() const {
					return output->getBlueCells();
				}
				
		};
	}
}

#endif
