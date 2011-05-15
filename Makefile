all: bin/cppmines.exe bin/cppmines-tests.exe

bin/cppmines.exe: obj/main.o obj/minesweeper/core/cell.o obj/minesweeper/core/field.o obj/minesweeper/generator/generator-field.o obj/minesweeper/generator/swapper.o obj/minesweeper/solver/searcher.o obj/minesweeper/solver/solver-cell.o obj/minesweeper/solver/solver-field.o obj/minesweeper/solver/suspect.o
	mkdir -p bin
	g++ -Wall -o $@ obj/main.o obj/minesweeper/core/cell.o obj/minesweeper/core/field.o obj/minesweeper/generator/generator-field.o obj/minesweeper/generator/swapper.o obj/minesweeper/solver/searcher.o obj/minesweeper/solver/solver-cell.o obj/minesweeper/solver/solver-field.o obj/minesweeper/solver/suspect.o

bin/cppmines-tests.exe: obj/minesweeper/core/cell.o obj/minesweeper/core/field.o obj/minesweeper/generator/generator-field.o obj/minesweeper/generator/swapper.o obj/minesweeper/solver/searcher.o obj/minesweeper/solver/solver-cell.o obj/minesweeper/solver/solver-field.o obj/minesweeper/solver/suspect.o obj/tests/combination-test.o obj/tests/core-test.o obj/tests/generator-test.o obj/tests/main.o obj/tests/solver-test.o obj/tests/test.o
	mkdir -p bin
	g++ -Wall -o $@ obj/minesweeper/core/cell.o obj/minesweeper/core/field.o obj/minesweeper/generator/generator-field.o obj/minesweeper/generator/swapper.o obj/minesweeper/solver/searcher.o obj/minesweeper/solver/solver-cell.o obj/minesweeper/solver/solver-field.o obj/minesweeper/solver/suspect.o obj/tests/combination-test.o obj/tests/core-test.o obj/tests/generator-test.o obj/tests/main.o obj/tests/solver-test.o obj/tests/test.o

obj/main.o: main.cpp minesweeper.h minesweeper/core.h minesweeper/core/cell.h minesweeper/core/common.h minesweeper/core/field.h minesweeper/generator.h minesweeper/generator/../core/common.h minesweeper/generator/../solver/../core/cell.h minesweeper/generator/../solver/../core/common.h minesweeper/generator/../solver/../core/field.h minesweeper/generator/../solver/bipartite.h minesweeper/generator/../solver/common.h minesweeper/generator/../solver/result.h minesweeper/generator/../solver/searcher.h minesweeper/generator/../solver/solver-cell.h minesweeper/generator/../solver/solver-field.h minesweeper/generator/common.h minesweeper/generator/generator-cell.h minesweeper/generator/generator-field.h minesweeper/generator/record-state.h minesweeper/solver.h minesweeper/solver/../core/cell.h minesweeper/solver/../core/common.h minesweeper/solver/../core/field.h minesweeper/solver/bipartite.h minesweeper/solver/common.h minesweeper/solver/result.h minesweeper/solver/searcher.h minesweeper/solver/solver-cell.h minesweeper/solver/solver-field.h
	mkdir -p obj
	g++ -c -fast -Wall -o $@ main.cpp

obj/minesweeper/core/cell.o: minesweeper/core/cell.cpp minesweeper/core/cell.h minesweeper/core/common.h minesweeper/core/field.h
	mkdir -p obj/minesweeper/core
	g++ -c -fast -Wall -o $@ minesweeper/core/cell.cpp

obj/minesweeper/core/field.o: minesweeper/core/field.cpp minesweeper/core/cell.h minesweeper/core/common.h minesweeper/core/field.h
	mkdir -p obj/minesweeper/core
	g++ -c -fast -Wall -o $@ minesweeper/core/field.cpp

obj/minesweeper/generator/generator-field.o: minesweeper/generator/generator-field.cpp minesweeper/generator/../core/common.h minesweeper/generator/../solver/../core/cell.h minesweeper/generator/../solver/../core/common.h minesweeper/generator/../solver/../core/field.h minesweeper/generator/../solver/bipartite.h minesweeper/generator/../solver/common.h minesweeper/generator/../solver/result.h minesweeper/generator/../solver/searcher.h minesweeper/generator/../solver/solver-cell.h minesweeper/generator/../solver/solver-field.h minesweeper/generator/common.h minesweeper/generator/generator-cell.h minesweeper/generator/generator-field.h minesweeper/generator/record-state.h minesweeper/generator/swapper.h
	mkdir -p obj/minesweeper/generator
	g++ -c -fast -Wall -o $@ minesweeper/generator/generator-field.cpp

obj/minesweeper/generator/swapper.o: minesweeper/generator/swapper.cpp minesweeper/generator/../core/common.h minesweeper/generator/../solver/../core/cell.h minesweeper/generator/../solver/../core/common.h minesweeper/generator/../solver/../core/field.h minesweeper/generator/../solver/bipartite.h minesweeper/generator/../solver/common.h minesweeper/generator/../solver/result.h minesweeper/generator/../solver/searcher.h minesweeper/generator/../solver/solver-cell.h minesweeper/generator/../solver/solver-field.h minesweeper/generator/common.h minesweeper/generator/generator-cell.h minesweeper/generator/generator-field.h minesweeper/generator/record-state.h minesweeper/generator/swapper.h
	mkdir -p obj/minesweeper/generator
	g++ -c -fast -Wall -o $@ minesweeper/generator/swapper.cpp

obj/minesweeper/solver/searcher.o: minesweeper/solver/searcher.cpp minesweeper/solver/../core/cell.h minesweeper/solver/../core/common.h minesweeper/solver/../core/field.h minesweeper/solver/bipartite.h minesweeper/solver/combination.h minesweeper/solver/common.h minesweeper/solver/result.h minesweeper/solver/searcher.h minesweeper/solver/solver-cell.h minesweeper/solver/solver-field.h minesweeper/solver/suspect.h
	mkdir -p obj/minesweeper/solver
	g++ -c -fast -Wall -o $@ minesweeper/solver/searcher.cpp

obj/minesweeper/solver/solver-cell.o: minesweeper/solver/solver-cell.cpp minesweeper/solver/../core/cell.h minesweeper/solver/../core/common.h minesweeper/solver/../core/field.h minesweeper/solver/bipartite.h minesweeper/solver/common.h minesweeper/solver/result.h minesweeper/solver/searcher.h minesweeper/solver/solver-cell.h minesweeper/solver/solver-field.h
	mkdir -p obj/minesweeper/solver
	g++ -c -fast -Wall -o $@ minesweeper/solver/solver-cell.cpp

obj/minesweeper/solver/solver-field.o: minesweeper/solver/solver-field.cpp minesweeper/solver/../core/cell.h minesweeper/solver/../core/common.h minesweeper/solver/../core/field.h minesweeper/solver/bipartite.h minesweeper/solver/common.h minesweeper/solver/result.h minesweeper/solver/searcher.h minesweeper/solver/solver-cell.h minesweeper/solver/solver-field.h
	mkdir -p obj/minesweeper/solver
	g++ -c -fast -Wall -o $@ minesweeper/solver/solver-field.cpp

obj/minesweeper/solver/suspect.o: minesweeper/solver/suspect.cpp minesweeper/solver/../core/cell.h minesweeper/solver/../core/common.h minesweeper/solver/../core/field.h minesweeper/solver/bipartite.h minesweeper/solver/common.h minesweeper/solver/result.h minesweeper/solver/searcher.h minesweeper/solver/solver-cell.h minesweeper/solver/solver-field.h minesweeper/solver/suspect.h
	mkdir -p obj/minesweeper/solver
	g++ -c -fast -Wall -o $@ minesweeper/solver/suspect.cpp

obj/tests/combination-test.o: tests/combination-test.cpp tests/../minesweeper.h tests/../minesweeper/core.h tests/../minesweeper/core/cell.h tests/../minesweeper/core/common.h tests/../minesweeper/core/field.h tests/../minesweeper/generator.h tests/../minesweeper/generator/../core/common.h tests/../minesweeper/generator/../solver/../core/cell.h tests/../minesweeper/generator/../solver/../core/common.h tests/../minesweeper/generator/../solver/../core/field.h tests/../minesweeper/generator/../solver/bipartite.h tests/../minesweeper/generator/../solver/common.h tests/../minesweeper/generator/../solver/result.h tests/../minesweeper/generator/../solver/searcher.h tests/../minesweeper/generator/../solver/solver-cell.h tests/../minesweeper/generator/../solver/solver-field.h tests/../minesweeper/generator/common.h tests/../minesweeper/generator/generator-cell.h tests/../minesweeper/generator/generator-field.h tests/../minesweeper/generator/record-state.h tests/../minesweeper/solver.h tests/../minesweeper/solver/../core/cell.h tests/../minesweeper/solver/../core/common.h tests/../minesweeper/solver/../core/field.h tests/../minesweeper/solver/bipartite.h tests/../minesweeper/solver/combination.h tests/../minesweeper/solver/common.h tests/../minesweeper/solver/result.h tests/../minesweeper/solver/searcher.h tests/../minesweeper/solver/solver-cell.h tests/../minesweeper/solver/solver-field.h tests/combination-test.h tests/test.h
	mkdir -p obj/tests
	g++ -c -fast -Wall -o $@ tests/combination-test.cpp

obj/tests/core-test.o: tests/core-test.cpp tests/../minesweeper.h tests/../minesweeper/core.h tests/../minesweeper/core/cell.h tests/../minesweeper/core/common.h tests/../minesweeper/core/field.h tests/../minesweeper/generator.h tests/../minesweeper/generator/../core/common.h tests/../minesweeper/generator/../solver/../core/cell.h tests/../minesweeper/generator/../solver/../core/common.h tests/../minesweeper/generator/../solver/../core/field.h tests/../minesweeper/generator/../solver/bipartite.h tests/../minesweeper/generator/../solver/common.h tests/../minesweeper/generator/../solver/result.h tests/../minesweeper/generator/../solver/searcher.h tests/../minesweeper/generator/../solver/solver-cell.h tests/../minesweeper/generator/../solver/solver-field.h tests/../minesweeper/generator/common.h tests/../minesweeper/generator/generator-cell.h tests/../minesweeper/generator/generator-field.h tests/../minesweeper/generator/record-state.h tests/../minesweeper/solver.h tests/../minesweeper/solver/../core/cell.h tests/../minesweeper/solver/../core/common.h tests/../minesweeper/solver/../core/field.h tests/../minesweeper/solver/bipartite.h tests/../minesweeper/solver/common.h tests/../minesweeper/solver/result.h tests/../minesweeper/solver/searcher.h tests/../minesweeper/solver/solver-cell.h tests/../minesweeper/solver/solver-field.h tests/core-test.h tests/test.h
	mkdir -p obj/tests
	g++ -c -fast -Wall -o $@ tests/core-test.cpp

obj/tests/generator-test.o: tests/generator-test.cpp tests/../minesweeper.h tests/../minesweeper/core.h tests/../minesweeper/core/cell.h tests/../minesweeper/core/common.h tests/../minesweeper/core/field.h tests/../minesweeper/generator.h tests/../minesweeper/generator/../core/common.h tests/../minesweeper/generator/../solver/../core/cell.h tests/../minesweeper/generator/../solver/../core/common.h tests/../minesweeper/generator/../solver/../core/field.h tests/../minesweeper/generator/../solver/bipartite.h tests/../minesweeper/generator/../solver/common.h tests/../minesweeper/generator/../solver/result.h tests/../minesweeper/generator/../solver/searcher.h tests/../minesweeper/generator/../solver/solver-cell.h tests/../minesweeper/generator/../solver/solver-field.h tests/../minesweeper/generator/common.h tests/../minesweeper/generator/generator-cell.h tests/../minesweeper/generator/generator-field.h tests/../minesweeper/generator/record-state.h tests/../minesweeper/solver.h tests/../minesweeper/solver/../core/cell.h tests/../minesweeper/solver/../core/common.h tests/../minesweeper/solver/../core/field.h tests/../minesweeper/solver/bipartite.h tests/../minesweeper/solver/common.h tests/../minesweeper/solver/result.h tests/../minesweeper/solver/searcher.h tests/../minesweeper/solver/solver-cell.h tests/../minesweeper/solver/solver-field.h tests/generator-test.h tests/test.h
	mkdir -p obj/tests
	g++ -c -fast -Wall -o $@ tests/generator-test.cpp

obj/tests/main.o: tests/main.cpp tests/../minesweeper.h tests/../minesweeper/core.h tests/../minesweeper/core/cell.h tests/../minesweeper/core/common.h tests/../minesweeper/core/field.h tests/../minesweeper/generator.h tests/../minesweeper/generator/../core/common.h tests/../minesweeper/generator/../solver/../core/cell.h tests/../minesweeper/generator/../solver/../core/common.h tests/../minesweeper/generator/../solver/../core/field.h tests/../minesweeper/generator/../solver/bipartite.h tests/../minesweeper/generator/../solver/common.h tests/../minesweeper/generator/../solver/result.h tests/../minesweeper/generator/../solver/searcher.h tests/../minesweeper/generator/../solver/solver-cell.h tests/../minesweeper/generator/../solver/solver-field.h tests/../minesweeper/generator/common.h tests/../minesweeper/generator/generator-cell.h tests/../minesweeper/generator/generator-field.h tests/../minesweeper/generator/record-state.h tests/../minesweeper/solver.h tests/../minesweeper/solver/../core/cell.h tests/../minesweeper/solver/../core/common.h tests/../minesweeper/solver/../core/field.h tests/../minesweeper/solver/bipartite.h tests/../minesweeper/solver/common.h tests/../minesweeper/solver/result.h tests/../minesweeper/solver/searcher.h tests/../minesweeper/solver/solver-cell.h tests/../minesweeper/solver/solver-field.h tests/combination-test.h tests/core-test.h tests/generator-test.h tests/solver-test.h tests/test.h
	mkdir -p obj/tests
	g++ -c -fast -Wall -o $@ tests/main.cpp

obj/tests/solver-test.o: tests/solver-test.cpp tests/../minesweeper.h tests/../minesweeper/core.h tests/../minesweeper/core/cell.h tests/../minesweeper/core/common.h tests/../minesweeper/core/field.h tests/../minesweeper/generator.h tests/../minesweeper/generator/../core/common.h tests/../minesweeper/generator/../solver/../core/cell.h tests/../minesweeper/generator/../solver/../core/common.h tests/../minesweeper/generator/../solver/../core/field.h tests/../minesweeper/generator/../solver/bipartite.h tests/../minesweeper/generator/../solver/common.h tests/../minesweeper/generator/../solver/result.h tests/../minesweeper/generator/../solver/searcher.h tests/../minesweeper/generator/../solver/solver-cell.h tests/../minesweeper/generator/../solver/solver-field.h tests/../minesweeper/generator/common.h tests/../minesweeper/generator/generator-cell.h tests/../minesweeper/generator/generator-field.h tests/../minesweeper/generator/record-state.h tests/../minesweeper/solver.h tests/../minesweeper/solver/../core/cell.h tests/../minesweeper/solver/../core/common.h tests/../minesweeper/solver/../core/field.h tests/../minesweeper/solver/bipartite.h tests/../minesweeper/solver/common.h tests/../minesweeper/solver/result.h tests/../minesweeper/solver/searcher.h tests/../minesweeper/solver/solver-cell.h tests/../minesweeper/solver/solver-field.h tests/solver-test.h tests/test.h
	mkdir -p obj/tests
	g++ -c -fast -Wall -o $@ tests/solver-test.cpp

obj/tests/test.o: tests/test.cpp tests/../minesweeper.h tests/../minesweeper/core.h tests/../minesweeper/core/cell.h tests/../minesweeper/core/common.h tests/../minesweeper/core/field.h tests/../minesweeper/generator.h tests/../minesweeper/generator/../core/common.h tests/../minesweeper/generator/../solver/../core/cell.h tests/../minesweeper/generator/../solver/../core/common.h tests/../minesweeper/generator/../solver/../core/field.h tests/../minesweeper/generator/../solver/bipartite.h tests/../minesweeper/generator/../solver/common.h tests/../minesweeper/generator/../solver/result.h tests/../minesweeper/generator/../solver/searcher.h tests/../minesweeper/generator/../solver/solver-cell.h tests/../minesweeper/generator/../solver/solver-field.h tests/../minesweeper/generator/common.h tests/../minesweeper/generator/generator-cell.h tests/../minesweeper/generator/generator-field.h tests/../minesweeper/generator/record-state.h tests/../minesweeper/solver.h tests/../minesweeper/solver/../core/cell.h tests/../minesweeper/solver/../core/common.h tests/../minesweeper/solver/../core/field.h tests/../minesweeper/solver/bipartite.h tests/../minesweeper/solver/common.h tests/../minesweeper/solver/result.h tests/../minesweeper/solver/searcher.h tests/../minesweeper/solver/solver-cell.h tests/../minesweeper/solver/solver-field.h tests/test.h
	mkdir -p obj/tests
	g++ -c -fast -Wall -o $@ tests/test.cpp

run: bin/cppmines.exe
	bin/cppmines.exe

test: bin/cppmines-tests.exe
	bin/cppmines-tests.exe

clean:
	rm -rf bin obj
