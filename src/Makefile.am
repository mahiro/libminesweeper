lib_LTLIBRARIES = libminesweeper.la
libminesweeper_la_LDFLAGS = -version-info 0:0:0
libminesweeper_la_SOURCES = \
minesweeper/core-cell.cpp \
minesweeper/core-field.cpp \
minesweeper/solver-searcher.cpp \
minesweeper/solver-cell.cpp \
minesweeper/solver-field.cpp \
minesweeper/solver-suspect.cpp \
minesweeper/generator-field.cpp \
minesweeper/generator-swapper.cpp

include_HEADERS = minesweeper.h

otherincludedir = $(includedir)/minesweeper
otherinclude_HEADERS = \
minesweeper/core-cell.h \
minesweeper/core-field.h \
minesweeper/core.h \
minesweeper/generator-cell.h \
minesweeper/generator-field.h \
minesweeper/generator-record.h \
minesweeper/generator-swapper.h \
minesweeper/generator.h \
minesweeper/solver-bipartite.h \
minesweeper/solver-cell.h \
minesweeper/solver-combination.h \
minesweeper/solver-field.h \
minesweeper/solver-result.h \
minesweeper/solver-searcher.h \
minesweeper/solver-suspect.h \
minesweeper/solver.h

#bin_PROGRAMS = minesweeper-example
noinst_PROGRAMS = minesweeper-example
minesweeper_example_LDFLAGS = -lminesweeper
minesweeper_example_SOURCES = main.cpp
