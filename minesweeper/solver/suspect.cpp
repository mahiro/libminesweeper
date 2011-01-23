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
			
			if (positives > 0 || negatives < 0) {
				int diff = redCell.getRest() - blueCell.getRest();
				
				if (diff == positives) {
					setResultDouble(redCell, blueCell, true);
				} else if (diff == negatives) {
					setResultDouble(blueCell, redCell, false);
				}
			}
			
			decrSuspectAround(redCell);
			incrSuspectAround(blueCell);
			
			return searcher.hasResult();
		}
		
		bool SuspectState::suspectMultiple(const CellSet & redCells, const CellSet & blueCells, bool backward) const {
			incrSuspectAround(redCells);
			decrSuspectAround(blueCells);
			
			int negativesAdjusted = negatives -
					(backward ? searcher.getField().countUnknownCells() : 0);
			
			if (positives > 0 || negativesAdjusted < 0) {
				int diff = sumRest(redCells) - sumRest(blueCells) -
						(backward ? searcher.getField().getRest() : 0);
				
				if (diff == positives) {
					setResultMultiple(redCells, blueCells, true, backward);
				} else if (diff == negativesAdjusted) {
					setResultMultiple(blueCells, redCells, false, backward);
				}
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
		
		void SuspectState::setResultMultiple(const CellSet & redCells, const CellSet & blueCells, bool forRed, bool backward) const {
			const Result & result = searcher.setResultFound(backward);
			
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
			
			if (backward) {
				const SolverField & field = searcher.getField();
				const CellSet & unknownCells = field.getUnknownCells();
				
				CellSet excludedCells;
				collectUnknownsAround(excludedCells, redCells);
				collectUnknownsAround(excludedCells, blueCells);
				
				bool fieldForRed = !forRed;
				CellSet & outputCells = output.getRedOrBlueCells(fieldForRed);
				
				for (CellSetIter it = unknownCells.begin(); it != unknownCells.end(); it++) {
					if (dynamic_cast<const SolverCell *>(*it)->suspect < offset
							&& (*it)->hasMine() == fieldForRed && excludedCells.find(*it) == excludedCells.end()
							&& redCells.find(*it) == redCells.end() && blueCells.find(*it) == blueCells.end()) {
						outputCells.insert(*it);
					}
				}
			}
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
		
		void SuspectState::collectUnknownsAround(CellSet & outputCells, const CellSet & inputCells) const {
			for (CellSetIter it = inputCells.begin(); it != inputCells.end(); it++) {
				for (AdjIter adj = (*it)->begin(); adj != (*it)->end(); adj++) {
					if ((*adj)->isUnknown()) {
						outputCells.insert(*adj);
					}
				}
			}
		}
	}
}
