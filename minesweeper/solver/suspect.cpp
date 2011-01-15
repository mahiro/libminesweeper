#include "suspect.h"
#include "searcher.h"
#include "solver-field.h"
#include "solver-cell.h"

namespace minesweeper {
	namespace solver {
		bool SuspectState::suspectCell(const Cell & targetCell) const {
			if (targetCell.getRest() == 0) {
				searcher.setResultFound();
				searcher.getInputBlueCells().insert(&targetCell);
				
				CellSet & blueCells = searcher.getOutputBlueCells();
				
				for (AdjIter adj = targetCell.begin(); adj != targetCell.end(); adj++) {
					if ((*adj)->isUnknown()) {
						blueCells.insert(*adj);
					}
				}
			} else if (targetCell.getRest() == dynamic_cast<const SolverCell *>(&targetCell)->countUnknowns()) {
				searcher.setResultFound();
				searcher.getInputRedCells().insert(&targetCell);
				
				CellSet & redCells = searcher.getOutputRedCells();
				
				for (AdjIter adj = targetCell.begin(); adj != targetCell.end(); adj++) {
					if ((*adj)->isUnknown()) {
						redCells.insert(*adj);
					}
				}
			}
			
			return searcher.hasResult();
		}
		
		bool SuspectState::suspectCells(const Cell & redCell, const Cell & blueCell) const {
			incrSuspectAround(redCell);
			decrSuspectAround(blueCell);
			
			int diff = redCell.getRest() - blueCell.getRest();
			
			if (diff == positives) {
				createResult(redCell, blueCell, true);
			} else if (diff == negatives) {
				createResult(blueCell, redCell, false);
			}
			
			decrSuspectAround(redCell);
			incrSuspectAround(blueCell);
			
			return searcher.hasResult();
		}
		
//		void SuspectState::suspectCells(const CellSet & redCells, const CellSet & blueCells) const {
//			
//		}
		
		void SuspectState::incrSuspectAround(const Cell & cell) const {
			for (AdjIter adj = cell.begin(); adj != cell.end(); adj++) {
				if ((*adj)->isUnknown()) {
					int suspect = ++dynamic_cast<const SolverCell *>(*adj)->suspect;
					
					if (suspect > offset) {
						positives++;
					} else {
						negatives++;
					}
				}
			}
		}
		
		void SuspectState::decrSuspectAround(const Cell & cell) const {
			for (AdjIter adj = cell.begin(); adj != cell.end(); adj++) {
				if ((*adj)->isUnknown()) {
					int suspect = --dynamic_cast<const SolverCell *>(*adj)->suspect;
					
					if (suspect < offset) {
						negatives--;
					} else {
						positives--;
					}
				}
			}
		}
		
		void SuspectState::createResult(const Cell & redCell, const Cell & blueCell, bool forPositives) const {
			searcher.setResultFound();
			
			CellSet & redCells = searcher.getInputRedCells();
			CellSet & blueCells = searcher.getInputBlueCells();
			
			redCells.insert(&redCell);
			blueCells.insert(&blueCell);
			
			collectOutput(searcher.getOutputRedCells(), redCells, blueCells, forPositives);
			collectOutput(searcher.getOutputBlueCells(), blueCells, redCells, !forPositives);
		}
		
		void SuspectState::collectOutput(CellSet & outputCells,
				const CellSet & inputCells, const CellSet & otherInputCells, bool forPositives) const {
			for (CellSetIter it = inputCells.begin(); it != inputCells.end(); it++) {
				const Cell & cell = **it;
				
				for (AdjIter adj = cell.begin(); adj != cell.end(); adj++) {
					if ((*adj)->isUnknown() && otherInputCells.find(*adj) == otherInputCells.end()) {
						if (forPositives) {
							if (dynamic_cast<const SolverCell *>(*adj)->suspect > offset) {
								outputCells.insert(*adj);
							}
						} else {
							if (dynamic_cast<const SolverCell *>(*adj)->suspect < offset) {
								outputCells.insert(*adj);
							}
						}
					}
				}
			}
		}
	}
}
