#ifndef _MINESWEEPER_SOLVER_FIELD_H_
#define _MINESWEEPER_SOLVER_FIELD_H_

#include "common.h"

namespace minesweeper {
	namespace solver {
		using namespace minesweeper::core;
		
		class SolverField : public Field {
			private:
				
			public:
				explicit SolverField(int _width, int _height, bool _init = true) :
						Field(_width, _height, false) {
					if (_init) {
						constructCells();
					}
				}
				
				virtual const Cell * createCell(int x, int y) const;
		};
	}
}

#endif
