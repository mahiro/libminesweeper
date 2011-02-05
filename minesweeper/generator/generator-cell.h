#ifndef _MINESWEEPER_GENERATOR_CELL_H_
#define _MINESWEEPER_GENERATOR_CELL_H_

#include "common.h"
#include "../solver/solver-cell.h"
#include "generator-field.h"
#include "record-state.h"

namespace minesweeper {
	namespace generator {
		using namespace minesweeper::core;
		using namespace minesweeper::solver;
		
		class GeneratorCell : public SolverCell {
			friend class GeneratorField;
			friend class Swapper;
			
			private:
				const RecordState recordState;
				
			protected:
				virtual void clear() const {
					SolverCell::clear();
					recordState.clear();
				}
				
				virtual void reset() const {
					SolverCell::reset();
					recordState.clear();
				}
				
			public:
				explicit GeneratorCell(const Field & _field, int _x, int _y) :
					SolverCell(_field, _x, _y) {}
				
				virtual ~GeneratorCell() {}
				
		};
	}
}

#endif
