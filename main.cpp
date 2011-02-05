#include "minesweeper.h"
#include <iostream>

int main() {
	using namespace minesweeper::core;
	using namespace minesweeper::solver;
	
	SolverField field(15, 15);
	const Cell & startCell = field.getCell(5, 5);
	
	field.setupRandom(45, startCell, 1);
	startCell.dig();
	std::cout << field << std::endl;
	
	return 0;
}
