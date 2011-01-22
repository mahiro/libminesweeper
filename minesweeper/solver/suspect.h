#ifndef _MINESWEEPER_SOLVER_SUSPECT_H_
#define _MINESWEEPER_SOLVER_SUSPECT_H_

#include "common.h"

namespace minesweeper {
	namespace solver {
		using namespace minesweeper::core;
		
		class SuspectState {
			private:
				const Searcher & searcher;
				const int offset;
				mutable int positives;
				mutable int negatives;
				
				void incrSuspectAround(const Cell & cell) const;
				void decrSuspectAround(const Cell & cell) const;
				void setResultSingle(const Cell & inputCell, bool forRed) const;
				void setResultDouble(const Cell & redCell, const Cell & blueCell, bool forRed) const;
				
				void collectOutput(CellSet & outputCells, const CellSet & inputCells,
						const CellSet & otherInputCells, bool forPositives) const;
				
			public:
				explicit SuspectState(const Searcher & _searcher, int _offset) :
						searcher(_searcher), offset(_offset),
						positives(0), negatives(0) {}
				
				virtual ~SuspectState() {}
				
				bool suspectSingle(const Cell & targetCell) const;
				bool suspectDouble(const Cell & redCell, const Cell & blueCell) const;
				bool suspectMultiple(const CellSet & redCells, const CellSet & blueCells) const;
		};
	}
}

#endif
