#include "solver-field.h"
#include "solver-cell.h"

namespace minesweeper {
	namespace solver {
		using namespace minesweeper::core;
		
		const Cell * SolverField::createCell(int x, int y) const {
			return new SolverCell(*this, x, y);
		}
		
		void SolverField::clearCells() const {
			Field::clearCells();
			clearUnknowns();
		}
		
		void SolverField::clearUnknowns() const {
			unknownCells.clear();
			frontierCells.clear();
			
			for (FieldIter it = begin(); it != end(); it++) {
				const SolverCell & cell = dynamic_cast<const SolverCell &>(**it);
				
				for (AdjIter adj = cell.begin(); adj != cell.end(); adj++) {
					cell.incrUnknowns();
					addUnknownCell(cell);
				}
			}
		}
		
		void SolverField::addFrontierCell(const SolverCell & cell) const {
			if (cell.countUnknowns() > 0) {
				if (!cell.isCovered() && !cell.hasMine()) {
					frontierCells.insert(&cell);
					cell.setFrontier();
				}
			}
		}
		
		void SolverField::removeFrontierCell(const SolverCell & cell) const {
			frontierCells.erase(&cell);
			cell.unsetFrontier();
		}
		
		void SolverField::addUnknownCell(const SolverCell & cell) const {
			if (cell.isUnknown()) {
				unknownCells.insert(&cell);
			}
		}
		
		void SolverField::removeUnknownCell(const SolverCell & cell) const {
			unknownCells.erase(&cell);
		}
		
		int SolverField::countUnknownCells() const {
			return unknownCells.size();
		}
		
		int SolverField::countFrontierCells() const {
			return frontierCells.size();
		}
		
		const CellSet & SolverField::getUnknownCells() const {
			return unknownCells;
		}
		
		const CellSet & SolverField::getFrontierCells() const {
			return frontierCells;
		}
		
		void SolverField::handleResult(const Searcher & searcher) const {
			const CellSet & redCells = searcher.getOutputRedCells();
			
			for (CellSetIter it = redCells.begin(); it != redCells.end(); it++) {
				(*it)->setFlag();
			}
			
			const CellSet & blueCells = searcher.getOutputBlueCells();
			
			for (CellSetIter it = blueCells.begin(); it != blueCells.end(); it++) {
				(*it)->uncover();
			}
		}
		
		void SolverField::solve(const Cell & startCell, int forwardDepth, int backwardDepth, bool fast) const {
			startCell.uncover();
			solve(forwardDepth, backwardDepth, fast);
		}
		
		void SolverField::solve(int forwardDepth, int backwardDepth, bool fast) const {
			int prevUnknowns = countUnknownCells();
			
			for (;;) {
				Searcher searcher(*this);
				
				for (int depth = 1; depth <= forwardDepth; depth++) {
					if (searcher.searchForward(depth)) {
						break;
					}
				}
				
//				if (!searcher.hasResult()) {
//					for (int depth = 0; depth <= backwardDepth; depth++) {
//						if (searcher.searchBackward(depth, fast)) {
//							break;
//						}
//					}
//				}
				
				if (searcher.hasResult()) {
					handleResult(searcher);
					
					int unknowns = countUnknownCells();
					
					if (unknowns < prevUnknowns) {
						prevUnknowns = unknowns;
						continue;
					}
				}
				
				break;
			}
		}
	}
}
