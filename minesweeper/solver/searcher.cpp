#include "searcher.h"
#include "solver-field.h"
#include "solver-cell.h"
#include "suspect.h"

namespace minesweeper {
	namespace solver {
		bool Searcher::searchForward(int depth) const {
			if (depth == 0) {
				return false;
			} else if (depth == 1) {
				return searchBySinglePoint();
			} else if (depth == 2) {
				return searchByDoublePoints();
//			} else {
//				return searchByMultiplePoints(depth);
			}
			
			return false;
		}
		
//		bool Searcher::searchBackward(int depth, bool fast = true) const {
//			if (fast) {
//				return traverseBackwardFast(depth);
//			} else {
//				return traverseBackward(depth);
//			}
//		}
		
		bool Searcher::searchBySinglePoint() const {
			const CellSet & frontierCells = field.getFrontierCells();
			
			for (CellSetIter it = frontierCells.begin(); it != frontierCells.end(); it++) {
				SuspectState state(*this, 0);
				
				if (state.suspectCell(**it)) {
					return true;
				}
			}
			
			return false;
		}
		
		bool Searcher::searchByDoublePoints() const {
			const CellSet & frontierCells = field.getFrontierCells();
			
			for (CellSetIter it = frontierCells.begin(); it != frontierCells.end(); it++) {
				const Cell & targetCell = **it;
				
				for (AdjIter adj = targetCell.begin(2); adj != targetCell.end(); adj++) {
					const Cell & otherCell = **adj;
					
					if (dynamic_cast<const SolverCell &>(otherCell).isFrontier()
							&& &targetCell < &otherCell /*eliminate redundancy of the flipped cases*/) {
						int targetID = targetCell.getX() + targetCell.getY() * field.getWidth();
						int otherID = otherCell.getX() + otherCell.getY() * field.getWidth();
						
						if (targetID < otherID) {
							SuspectState state(*this, 0);
							
							if (state.suspectCells(targetCell, otherCell)) {
								return true;
							}
						}
					}
				}
			}
			
			return false;
		}
		
//		bool Searcher::searchByMultiplePoints(int depth) const {
//			const CellSet & frontierCells = field.getFrontierCells();
//			BipartiteCells marking(CellSet(), CellSet());
//			
//			for (CellSetIter it = frontierCells.begin(); it != frontierCells.end(); it++) {
//				const CellSet currentCells, inputCells;
//				currentCells.insert(*it);
//				inputCells.insert(*it);
//				const BipartiteCells input(inputCells, CellSet());
//				
//				if (traverseForward(currentCells, input, marking, true, depth - 1)) {
//					return true;
//				}
//			}
//			
//			return false;
//		}
		
		bool Searcher::searchBySinglePoint(const Cell & targetCell) const {
			if (!dynamic_cast<const SolverCell &>(targetCell).isFrontier()) {
				return false;
			}
			
			SuspectState state(*this, 0);
			return state.suspectCell(targetCell);
		}
		
		bool Searcher::searchByDoublePoints(const Cell & targetCell) const {
			if (!dynamic_cast<const SolverCell &>(targetCell).isFrontier()) {
				return false;
			}
			
			for (AdjIter adj = targetCell.begin(2); adj != targetCell.end(); adj++) {
				const Cell & otherCell = **adj;
				
				if (dynamic_cast<const SolverCell &>(otherCell).isFrontier()) {
					SuspectState state(*this, 0);
					
					if (state.suspectCells(targetCell, otherCell)) {
						return true;
					}
				}
			}
			
			return false;
		}
		
//		bool Searcher::searchByMultiplePoints(const Cell & targetCell, int depth) const {
//			if (!dynamic_cast<const SolverCell &>(targetCell).isFrontier()) {
//				return false;
//			}
//			
//			const CellSet currentCells, markingCells;
//			currentCells.insert(targetCell);
//			markingCells.insert(targetCell);
//			
//			BipartiteCells input(CellSet(), CellSet());
//			BipartiteCells marking(markingCells, CellSet());
//			
//			return traverseForward(currentCells, input, marking, true, depth - 1);
//		}
//		
//		bool Searcher::traverseForward(const CellSet & currentCells,
//				const BipartiteCells & input, const BipartiteCells & marking,
//				bool forRed, int depthLeft) const {
//			const CellSet & inputCells = input.getRedOrBlueCells(forRed);
//			
//			for (CellSetIter it = currentCells.begin(); it != currentCells.end(); it++) {
//				inputCells.insert(*it);
//			}
//			
//			bool ret = false;
//			
//			if (depthLeft <= 0) {
//				SuspectState state(*this, 0);
//				ret = state.suspectCells(input.getRedCells(), input.getBlueCells());
//			} else {
//				bool nextForRed = !forRed;
//				ret = traverseForwardInternal(currentCells, input, marking, nextForRed, depthLeft);
//			}
//			
//			for (CellSetIter it = currentCells.begin(); it != currentCells.end(); it++) {
//				inputCells.remote(*it);
//			}
//			
//			return ret;
//		}
//		
//		bool Searcher::traverseForwardInternal(const CellSet & currentCells,
//				const BipartiteCells & input, const BipartiteCells & marking,
//				bool nextForRed, int depthLeft) const {
//			for (CellSetIter it = currentCells.begin(); it != currentCells.end(); it++) {
//				const Cell & currentCell = **it;
//				CellSet nextCandidates;
//				const CellSet & markingCells = marking.getRedOrBlueCells(nextForRed);
//				
//				for (AdjIter adj = currentCell.begin(2); adj != currentCell.end(); adj++) {
//					const CellSet & inputCells = input.getRedOrBlueCells(nextForRed);
//					
//					if ((*adj)->isFrontier() &&
//							markingCells.find(*adj) == markingCells.end() &&
//							inputCells.find(*adj) == inputCells.end()) {
//						nextCandidates.insert(*adj);
//					}
//				}
//				
//				if (nextCandidates.empty()) {
//					continue;
//				}
//				
//				bool ret = false;
//				
//				for (CellSetIter it2 = nextCandidates.begin(); it2 != nextCandidates.end(); it2++) {
//					markingCells.insert(*it2);
//				}
//				
//				CombinationGenerator cg(nextCandidates, 1, depthLeft);
//				
//				for (CombinationIter cit = cg.begin(); cit != cg.end(); cit++) {
//					const CellSet & nextCells = *cit;
//					
//					if (traverseForward(nextCells, input, marking, nextForRed, depthLeft - nextCells.size())) {
//						ret = true;
//						break;
//					}
//				}
//				
//				for (CellSetIter it2 = nextCandidates.begin(); it2 != nextCandidates.end(); it2++) {
//					markingCells.remove(*it2);
//				}
//				
//				if (ret) {
//					return ret;
//				}
//			}
//			
//			return false;
//		}
//		
//		bool Searcher::traverseBackwardFast(int depthLeft) const {
//			if (depthLeft == 0) {
//				SuspectState state(*this, 1);
//				return state.suspectCells(CellSet(), CellSet(), *this);
//			} else {
//				if (getRest() > 4 * depthLeft && getPending() > 4 * depthLeft) {
//					return false;
//				}
//				
//				const CellSet & frontierCells = field.getFrontierCells();
//				CombinationGenerator cg(frontierCells, depthLeft, depthLeft);
//				
//				for (CombinationIter cit = cg.begin(); cit != cg.end(); cit++) {
//					const CellSet & redCells = *cit;
//					SuspectState state(*this, 1);
//					
//					if (state.suspectCells(redCells, CellSet(), this)) {
//						return true;
//					}
//				}
//			}
//			
//			return false;
//		}
//		
//		bool Searcher::traverseBackward(int depthLeft) const {
//			if (depthLeft == 0) {
//				SuspectState state(*this, 1);
//				return state.suspectCells(CellSet(), CellSet(), *this);
//			} else {
//				const CellSet & frontierCells = field.getFrontierCells();
//				CombinationGenerator cg(frontierCells, 1, depthLeft);
//				
//				for (CombinationIter cit = cg.begin(); cit != cg.end(); cit++) {
//					const CellSet & redCells = *cit;
//					
//					if (redCells.size() == depthLeft) {
//						SuspectState state(*this, 1);
//						
//						if (state.suspectCells(redCells, CellSet(), *this)) {
//							return true;
//						}
//					} else {
//						CellSet nextCandidates;
//						bool ret = false;
//						
//						for (CellSetIter it = redCells.begin(); it != redCells.end(); it++) {
//							const Cell & redCell = **it;
//							
//							for (AdjIter adj = redCell.begin(2); adj != redCell.end(); adj++) {
//								if ((*adj)->isFrontier() &&
//										redCells.find(*adj) == redCells.end()) {
//									nextCandidates.insert(*adj);
//								}
//							}
//						}
//						
//						int depth = depthLeft - redCells.size();
//						CombinationGenerator cg2(nextCandidates, depth, depth);
//						
//						for (CombinationIter cit2 = cg2.begin(); cit2 != cg2.end(); cit2++) {
//							SuspectState state(*this, 1);
//							
//							if (state.suspectCells(redCells, blueCells, *this)) {
//								ret = true;
//								break;
//							}
//						}
//						
//						if (ret) {
//							return ret;
//						}
//					}
//				}
//				
//			}
//			
//			return false;
//		}
	}
}
