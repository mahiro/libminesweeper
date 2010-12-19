#include "minesweeper.h"
#include <iostream>

int main() {
	using namespace minesweeper::core;
	Field field(15, 15);
	const Cell & startCell = field.getCell(5, 5);
	
	field.setupRandomMines(45, startCell, 1);
	startCell.dig();
	field.print();
	
	return 0;
}
