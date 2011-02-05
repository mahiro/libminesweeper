#ifndef _MINESWEEPER_GENERATOR_SWAPPER_H_
#define _MINESWEEPER_GENERATOR_SWAPPER_H_

#include "common.h"
#include "record-state.h"

#include <cstdlib>

namespace minesweeper {
	namespace generator {
		using namespace minesweeper::core;
		using namespace minesweeper::solver;
		
		class Swapper {
			private:
				const GeneratorField & field;
				const Cell & startCell;
				
				mutable const Cell * fromCell;
				mutable const Cell * toCell;
				
				RecordState affectedRecord;
				
			public:
				explicit Swapper(const GeneratorField & _field, const Cell & _startCell) :
						field(_field), startCell(_startCell) {
					std::srand(std::time(0));
				}
				
				const Cell & getFromCell() const {
					return *fromCell;
				}
				
				const Cell & getToCell() const {
					return *toCell;
				}
				
				const RecordState & getAffectedRecord() const {
					return affectedRecord;
				}
				
				bool findSwappable() const;
				
		};
	}
}

#endif
