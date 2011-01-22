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
		
		bool SuspectState::suspectMultiple(const CellSet & redCells, const CellSet & blueCells) const {
			incrSuspectAround(redCells);
			decrSuspectAround(blueCells);
			
			int diff = sumRest(redCells) - sumRest(blueCells);
			
			if (diff == positives) {
				setResultMultiple(redCells, blueCells, true);
			} else if (diff == negatives) {
				setResultMultiple(blueCells, redCells, false);
			}
			
			decrSuspectAround(redCells);
			incrSuspectAround(blueCells);
			
			return searcher.hasResult();
		}
		
		int SuspectState::sumRest(const CellSet & cells) const {
			int sum = 0;
			
			for (CellSetIter it = cells.begin(); it != cells.end(); it++) {
				sum += (*it)->getRest();
			}
			
			return sum;
		}
		
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
		
		void SuspectState::incrSuspectAround(const CellSet & cells) const {
			for (CellSetIter it = cells.begin(); it != cells.end(); it++) {
				incrSuspectAround(**it);
			}
		}
		
		void SuspectState::decrSuspectAround(const CellSet & cells) const {
			for (CellSetIter it = cells.begin(); it != cells.end(); it++) {
				decrSuspectAround(**it);
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
			bool forPositives = forRed;
			collectOutput(output.getRedCells(), redCells, blueCells, forPositives);
			collectOutput(output.getBlueCells(), blueCells, redCells, !forPositives);
		}
		
		void SuspectState::setResultMultiple(const CellSet & redCells, const CellSet & blueCells, bool forRed) const {
			const Result & result = searcher.setResultFound(false);
			
			for (CellSetIter it = redCells.begin(); it != redCells.end(); it++) {
				result.getInputRedCells().insert(*it);
			}
			
			for (CellSetIter it = blueCells.begin(); it != blueCells.end(); it++) {
				result.getInputBlueCells().insert(*it);
			}
			
			const BipartiteCells & output = result.getOutput();
			bool forPositives = forRed;
			collectOutput(output.getRedCells(), redCells, blueCells, forPositives);
			collectOutput(output.getBlueCells(), blueCells, redCells, !forPositives);
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
