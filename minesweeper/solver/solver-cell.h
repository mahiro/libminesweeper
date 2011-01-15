#ifndef _MINESWEEPER_SOLVER_CELL_H_
#define _MINESWEEPER_SOLVER_CELL_H_

#include "common.h"
#include "solver-field.h"

namespace minesweeper {
	namespace solver {
		using namespace minesweeper::core;
		
		class SolverCell : public Cell {
			friend class SolverField;
			friend class SuspectState;
			
			private:
				mutable int numUnknowns;
				mutable int suspect;
				
				void incrUnknowns() const {
					if (numUnknowns++ == 0) {
						dynamic_cast<const SolverField &>(field).addFrontierCell(*this);
					}
				}
				
				void decrUnknowns() const {
					if (--numUnknowns == 0) {
						dynamic_cast<const SolverField &>(field).removeFrontierCell(*this);
					}
				}
				
			public:
				enum State {
					FRONTIER = 0x10
				};
				
				explicit SolverCell(const Field & _field, int _x, int _y) :
					Cell(_field, _x, _y),
					numUnknowns(0),
					suspect(0) {}
				
				virtual ~SolverCell() {}
				
				// Getters
				bool isFrontier() const {
					return state & FRONTIER;
				}
				
				int countUnknowns() const {
					return numUnknowns;
				}
				
				// Setters
				virtual bool setFrontier() const {
					if (isFrontier()) {
						return false;
					}
					
					state |= FRONTIER;
					return true;
				}
				
				virtual bool unsetFrontier() const {
					if (!isFrontier()) {
						return false;
					}
					
					state &= ~FRONTIER;
					return true;
				}
				
				virtual bool uncover() const;
				virtual bool cover() const;
				virtual bool setFlag() const;
				virtual bool unsetFlag() const;
				
		};
	}
}

#endif
