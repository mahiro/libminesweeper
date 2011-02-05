#include "swapper.h"
#include "generator-field.h"
#include "generator-cell.h"

#include <vector>
#include <cstdlib>

namespace minesweeper {
	namespace generator {
		using namespace minesweeper::core;
		using namespace minesweeper::solver;
		
		bool Swapper::findSwappable() const {
			// Find a cell from which to move a mine
			std::vector<const Cell *> fromCandidates;
			
			const CellSet & frontierCells = field.getFrontierCells();
			
			for (CellSetIter it = frontierCells.begin(); it != frontierCells.end(); it++) {
				for (AdjIter adj = (*it)->begin(); adj != (*it)->end(); adj++) {
					if ((*adj)->isUnknown() && (*adj)->hasMine()) {
						fromCandidates.push_back(*adj);
					}
				}
			}
			
			if (fromCandidates.empty()) {
				for (FieldIter it = field.begin(); it != field.end(); it++) {
					fromCandidates.push_back(*it);
				}
				
				if (fromCandidates.empty()) {
					return false;
				}
			}
			
			fromCell = fromCandidates[std::rand() % fromCandidates.size()];
			
			// Find a cell to which to move a mine
			std::vector<const Cell *> toCandidates;
			int maxDist = 0;
			
			const CellSet & unknownCells = field.getUnknownCells();
			
			for (CellSetIter it = unknownCells.begin(); it != unknownCells.end(); it++) {
				if ((*it)->hasMine()) {
					continue;
				}
				
				int dist = fromCell->getDist(**it);
				
				if (maxDist < dist) {
					maxDist = dist;
					toCandidates.clear();
				}
				
				toCandidates.push_back(*it);
			}
			
			if (toCandidates.empty()) {
				return false;
			}
			
			toCell = toCandidates[std::rand() % toCandidates.size()];
			
			// Find all affected records
			for (AdjIter adj = fromCell->begin(); adj != fromCell->end(); adj++) {
				int number = dynamic_cast<const GeneratorCell *>(*adj)->recordState.getNumber();
				affectedRecord.record(number);
			}
			
			for (AdjIter adj = toCell->begin(); adj != toCell->end(); adj++) {
				int number = dynamic_cast<const GeneratorCell *>(*adj)->recordState.getNumber();
				affectedRecord.record(number);
			}
			
			return true;
		}
	}
}
