#include "generator-field.h"
#include "generator-cell.h"

#include "swapper.h"

namespace minesweeper {
	namespace generator {
		using namespace minesweeper::core;
		using namespace minesweeper::solver;
		
		const Cell * GeneratorField::createCell(int x, int y) const {
			return new GeneratorCell(*this, x, y);
		}
		
		void GeneratorField::disposeRecordStack() const {
			while (!recordStack.empty()) {
				const Result * result = recordStack.top();
				recordStack.pop();
				delete result;
			}
		}
		
		void GeneratorField::setupSolvable(const Cell & startCell, int numMines, int maxForwardDepth, int maxBackwardDepth) const {
			clearCells();
			setupRandom(startCell, numMines, 1);
			makeSolvable(startCell, maxForwardDepth, maxBackwardDepth);
		}
		
		void GeneratorField::makeSolvable(const Cell & startCell, int maxForwardDepth, int maxBackwardDepth) const {
			int forwardDepth = std::min(4, maxForwardDepth);
			int backwardDepth = std::min(3, maxBackwardDepth);
			bool fast = true;
			
			int prevSolve = countUnknownCells();
			int prevRevert = countUnknownCells();
			
			for (retry = 0; ; retry++) {
				if (retry == 4) {
					forwardDepth = std::min(3, maxForwardDepth);
					backwardDepth = std::min(2, maxBackwardDepth);
				}
				
				solve(startCell, forwardDepth, backwardDepth, fast);
				
				int currSolve = countUnknownCells();
				
				if (countUnknownCells() <= 0) {
					// Completed
					return;
				}
				
				if (currSolve >= prevSolve && flagRecord.isRecorded()) {
					while (countUnknownCells() <= prevRevert && flagRecord.isRecorded()) {
						undoRecord();
					}
				}
				
				if (backwardRecord.isRecorded()) {
					while (backwardRecord.isRecorded()) {
						undoRecord();
					}
				}
				
				for (;;) {
					Swapper swapper(*this, startCell);
					
					if (swapper.findSwappable()) {
						const Cell & fromCell = swapper.getFromCell();
						const Cell & toCell = swapper.getToCell();
						
						if (swapper.getAffectedRecord().isRecorded()) {
							while (recordStack.size() > static_cast<std::size_t>(swapper.getAffectedRecord().getNumber())) {
								undoRecord();
							}
						}
						
						fromCell.unsetMine();
						toCell.setMine();
						break;
					} else if (recordStack.empty()) {
						// ERROR?
						return;
					} else {
						if (flagRecord.isRecorded()) {
							undoRecord();
						}
					}
				}
				
				prevSolve = currSolve;
				prevRevert = countUnknownCells();
			}
		}
		
		void GeneratorField::handleResult(const Searcher & searcher) const {
			SolverField::handleResult(searcher);
			
			if (searcher.hasResult()) {
				const Result * pResult = searcher.detachResult();
				
				int currentNumber = recordStack.size();
				recordStack.push(pResult);
				
				const CellSet & redCells = pResult->getInputRedCells();
				
				for (CellSetIter it = redCells.begin(); it != redCells.end(); it++) {
					dynamic_cast<const GeneratorCell *>(*it)->recordState.record(currentNumber);
				}
				
				const CellSet & blueCells = pResult->getInputBlueCells();
				
				for (CellSetIter it = blueCells.begin(); it != blueCells.end(); it++) {
					dynamic_cast<const GeneratorCell *>(*it)->recordState.record(currentNumber);
				}
				
				if (!pResult->getOutputRedCells().empty()) {
					flagRecord.record(currentNumber);
				}
				
				if (pResult->isBackward()) {
					backwardRecord.record(currentNumber);
				}
			}
		}
		
		void GeneratorField::undoRecord() const {
			const Result * pResult = recordStack.top();
			recordStack.pop();
			
			int currentNumber = recordStack.size();
			
			const CellSet & outputRedCells = pResult->getOutputRedCells();
			
			for (CellSetIter it = outputRedCells.begin(); it != outputRedCells.end(); it++) {
				(*it)->unsetFlag();
			}
			
			const CellSet & outputBlueCells = pResult->getOutputBlueCells();
			
			for (CellSetIter it = outputBlueCells.begin(); it != outputBlueCells.end(); it++) {
				(*it)->cover();
			}
			
			const CellSet & inputRedCells = pResult->getInputRedCells();
			
			for (CellSetIter it = inputRedCells.begin(); it != inputRedCells.end(); it++) {
				dynamic_cast<const GeneratorCell *>(*it)->recordState.unrecord(currentNumber);
			}
			
			const CellSet & inputBlueCells = pResult->getInputBlueCells();
			
			for (CellSetIter it = inputBlueCells.begin(); it != inputBlueCells.end(); it++) {
				dynamic_cast<const GeneratorCell *>(*it)->recordState.unrecord(currentNumber);
			}
			
			if (!pResult->getOutputRedCells().empty()) {
				flagRecord.unrecord(currentNumber);
			}
			
			if (!pResult->isBackward()) {
				backwardRecord.unrecord(currentNumber);
			}
			
			delete pResult;
		}
	}
}
