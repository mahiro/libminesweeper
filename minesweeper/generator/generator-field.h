#ifndef _MINESWEEPER_GENERATOR_FIELD_H_
#define _MINESWEEPER_GENERATOR_FIELD_H_

#include "common.h"
#include "../solver/solver-field.h"
#include "record-state.h"

#include <stack>

namespace minesweeper {
	namespace generator {
		using namespace minesweeper::core;
		using namespace minesweeper::solver;
		
		class GeneratorField : public SolverField {
			friend class GeneratorCell;
			
			private:
				mutable std::stack<const Result *> recordStack;
				const RecordState flagRecord;
				const RecordState backwardRecord;
				mutable int retry;
				
				void undoRecord() const;
				void disposeRecordStack() const;
				
				int min(int a, int b) const {
					return a > b ? b : a;
				}
				
			protected:
				virtual void handleResult(const Searcher & searcher) const;
				
			public:
				explicit GeneratorField(int _width, int _height, bool _init = true) :
						SolverField(_width, _height, false) {
					if (_init) {
						constructCells();
						clearUnknowns();
					}
				}
				
				virtual ~GeneratorField() {
					disposeRecordStack();
				}
				
				virtual void clearCells() const {
					SolverField::clearCells();
					flagRecord.clear();
					backwardRecord.clear();
					disposeRecordStack();
				}
				
				virtual void resetCells() const {
					SolverField::resetCells();
					disposeRecordStack();
				}
				
				virtual const Cell * createCell(int x, int y) const;
				
				void setupSolvable(const Cell & startCell, int numMines, int maxForwardDepth, int maxBackwardDepth) const;
				void makeSolvable(const Cell & startCell, int maxForwardDepth, int maxBackwardDepth) const;
				
		};
	}
}

#endif
