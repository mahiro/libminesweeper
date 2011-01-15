#include "solver-cell.h"

namespace minesweeper {
	namespace solver {
		bool SolverCell::uncover() const {
			if (Cell::uncover()) {
				if (!hasFlag() && !hasMine()) {
					dynamic_cast<const SolverField &>(field).addFrontierCell(*this);
					dynamic_cast<const SolverField &>(field).removeUnknownCell(*this);
				}
				
				for (AdjIter adj = begin(); adj != end(); adj++) {
					dynamic_cast<const SolverCell &>(**adj).decrUnknowns();
				}
				
				return true;
			} else {
				return false;
			}
		}
		
		bool SolverCell::cover() const {
			if (Cell::cover()) {
				if (!hasFlag() && !hasMine()) {
					dynamic_cast<const SolverField &>(field).removeFrontierCell(*this);
					dynamic_cast<const SolverField &>(field).addUnknownCell(*this);
				}
				
				for (AdjIter adj = begin(); adj != end(); adj++) {
					dynamic_cast<const SolverCell &>(**adj).incrUnknowns();
				}
				
				return true;
			} else {
				return false;
			}
		}
		
		bool SolverCell::setFlag() const {
			if (Cell::setFlag()) {
				if (isCovered()) {
					dynamic_cast<const SolverField &>(field).removeUnknownCell(*this);
				}
				
				for (AdjIter adj = begin(); adj != end(); adj++) {
					dynamic_cast<const SolverCell &>(**adj).decrUnknowns();
				}
				
				return true;
			} else {
				return false;
			}
		}
		
		bool SolverCell::unsetFlag() const {
			if (Cell::unsetFlag()) {
				if (isCovered()) {
					dynamic_cast<const SolverField &>(field).addUnknownCell(*this);
				}
				
				for (AdjIter adj = begin(); adj != end(); adj++) {
					dynamic_cast<const SolverCell &>(**adj).incrUnknowns();
				}
				
				return true;
			} else {
				return false;
			}
		}
	}
}
