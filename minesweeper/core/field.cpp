#include "field.h"
#include "cell.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace minesweeper {
	namespace core {
		/**********************************************************************
		 * Field
		 **********************************************************************/
		const Cell * Field::createCell(int x, int y) const {
			return new Cell(*this, x, y);
		}
		
		void Field::constructCells() {
			cells = new const Cell **[height];
			
			for (int y = 0; y < height; y++) {
				cells[y] = new const Cell *[width];
				
				for (int x = 0; x < width; x++) {
					cells[y][x] = createCell(x, y);
				}
			}
		}
		
		void Field::destructCells() {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					delete cells[y][x];
				}
				
				delete cells[y];
			}
			
			delete cells;
		}
		
		void Field::clearCells() const {
			for (FieldIter it = begin(); it != end(); it++) {
				(*it)->clear();
			}
			
			number = rest = 0;
			pending = width * height;
		}
		
		void Field::resetCells() const {
			for (FieldIter it = begin(); it != end(); it++) {
				(*it)->reset();
			}
		}
		
		void Field::setupRandomMines(int numMines, const Cell & startCell, int dist) const {
			const Cell ** cells = new const Cell *[width * height];
			
			// Collect eligible cells
			int cnt = 0;
			
			for (FieldIter it = begin(); it != end(); it++) {
				if ((*it)->getDist(startCell) > dist) {
					cells[cnt++] = *it;
				}
			}
			
			// Shuffle by Durstenfeld's algorithm
			srand((unsigned int) time(NULL));
			
			for (int i = cnt - 1; i > 0; i--) {
				int j = rand() % (i + 1);
				
				if (i != j) {
					const Cell *tmp = cells[i];
					cells[i] = cells[j];
					cells[j] = tmp;
				}
			}
			
			// Set mines
			for (int i = 0; i < cnt && i < numMines; i++) {
				cells[i]->setMine();
			}
			
			delete cells;
		}
		
		FieldIter Field::begin() const {
			return ++FieldIter(*this);
		}
		
		const FieldIter & Field::end() const {
			return endIter;
		}
		
		void Field::print() const {
			print(std::cout);
		}
		
		void Field::print(std::ostream & out) const {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					const Cell & cell = getCell(x, y);
					
					if (cell.isCovered()) {
						if (cell.hasFlag()) {
							out << "F ";
						} else {
							out << "- ";
						}
					} else if (cell.hasMine()) {
						out << "* ";
					} else {
						if (cell.getNumber() == 0) {
							out << ". ";
						} else {
							out << cell.getNumber() << " ";
						}
					}
				}
				
				out << "  ";
				
				for (int x = 0; x < width; x++) {
					const Cell & cell = getCell(x, y);
					
					if (cell.hasMine()) {
						out << "* ";
					} else {
						if (cell.getNumber() == 0) {
							out << ". ";
						} else {
							out << cell.getNumber() << " ";
						}
					}
				}
				
				out << std::endl;
			}
		}
		
		/**********************************************************************
		 * FieldIter
		 **********************************************************************/
		const FieldIter & FieldIter::operator ++() const {
			if (ptr == 0) {
				if (!(field.getWidth() == 0 || field.getHeight() == 0)) {
					ptr = &field.getCell(0, 0);
				}
				
				return *this;
			}
			
			int x = ptr->getX();
			int y = ptr->getY();
			
			if (++x >= field.getWidth()) {
				x = 0;
				
				if (++y >= field.getHeight()) {
					ptr = 0;
					return *this;
				}
			}
			
			ptr = &field.getCell(x, y);
			return *this;
		}
		
		const FieldIter & FieldIter::operator --() const {
			if (ptr == 0) {
				if (!(field.getWidth() == 0 || field.getHeight() == 0)) {
					ptr = &field.getCell(field.getWidth() - 1, field.getHeight() - 1);
				}
				
				return *this;
			}
			
			int x = ptr->getX();
			int y = ptr->getY();
			
			if (--x < 0) {
				x = field.getWidth() - 1;
				
				if (--y < 0) {
					ptr = 0;
					return *this;
				}
			}
			
			ptr = &field.getCell(x, y);
			return *this;
		}
		
		const FieldIter FieldIter::operator +(int n) const {
			if (n < 0) {
				return *this - (-n);
			}
			
			const FieldIter tmp = *this;
			
			while (n--) {
				++tmp;
			}
			
			return tmp;
		}
		
		const FieldIter FieldIter::operator -(int n) const {
			if (n < 0) {
				return *this + (-n);
			}
			
			const FieldIter tmp = *this;
			
			while (n--) {
				--tmp;
			}
			
			return tmp;
		}
		
	}
}
