#include "solver-field.h"
#include "solver-cell.h"

namespace minesweeper {
	namespace solver {
		using namespace minesweeper::core;
		
		const Cell * SolverField::createCell(int x, int y) const {
			return new SolverCell(*this, x, y);
		}
	}
}
