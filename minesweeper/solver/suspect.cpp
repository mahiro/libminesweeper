#include "suspect.h"
#include "searcher.h"
#include "solver-field.h"
#include "solver-cell.h"

namespace minesweeper {
	namespace solver {
		bool SuspectState::suspectSingle(const Cell & targetCell) const {
			if (targetCell.getRest() == 0) {
				setResultSingle(targetCell, false);
			} else if (targetCell.getRest() == dynamic_cast<const SolverCell &>(targetCell).countUnknowns()) {
				setResultSingle(targetCell, true);
			}
			
			return searcher.hasResult();
		}
		
		bool SuspectState::suspectDouble(const Cell & redCell, const Cell & blueCell) const {
			incrSuspectAround(redCell);
			decrSuspectAround(blueCell);
			
			int diff = redCell.getRest() - blueCell.getRest();
			
			if (diff == positives) {
				setResultDouble(redCell, blueCell, true);
			} else if (diff == negatives) {
				setResultDouble(blueCell, redCell, false);
			}
			
			decrSuspectAround(redCell);
			incrSuspectAround(blueCell);
			
			return searcher.hasResult();
		}
		
//		void SuspectState::suspectMultiple(const CellSet & redCells, const CellSet & blueCells) const {
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
		
		void SuspectState::setResultSingle(const Cell & inputCell, bool forRed) const {
			const Result & result = searcher.setResultFound(false);
			result.getInput().getRedOrBlueCells(forRed).insert(&inputCell);
			
			CellSet & outputCells = result.getOutput().getRedOrBlueCells(forRed);
			
			for (AdjIter adj = inputCell.begin(); adj != inputCell.end(); adj++) {
				if ((*adj)->isUnknown()) {
					outputCells.insert(*adj);
				}
			}
		}
		
		void SuspectState::setResultDouble(const Cell & redCell, const Cell & blueCell, bool forRed) const {
			const Result & result = searcher.setResultFound(false);
			
			CellSet & redCells = result.getInputRedCells();
			redCells.insert(&redCell);
			
			CellSet & blueCells = result.getInputBlueCells();
			blueCells.insert(&blueCell);
			
			const BipartiteCells & output = result.getOutput();
			collectOutput(output.getRedCells(), redCells, blueCells, forRed);
			collectOutput(output.getBlueCells(), blueCells, redCells, !forRed);
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
