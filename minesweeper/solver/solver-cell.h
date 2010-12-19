#ifndef _MINESWEEPER_SOLVER_CELL_H_
#define _MINESWEEPER_SOLVER_CELL_H_

#include "common.h"

namespace minesweeper {
	namespace solver {
		using namespace minesweeper::core;
		
		class SolverCell : public Cell {
			private:
				
			public:
				explicit SolverCell(const Field & _field, int _x, int _y) :
					Cell(_field, _x, _y) {}
				
				virtual ~SolverCell() {}
		};
	}
}

#endif
