# This library is free and distributed under
# Mozilla Public License Version 2.0.


CXX:=g++
#CXX:=x86_64-w64-mingw32-g++
DEBUG_FLAG:= -g -O3
RELESE_FLAG:= -std=c++11 -I./src
CURRENT_FLAGS:= $(RELESE_FLAG)
#CURRENT_FLAGS += -Wfatal-errors -pthread # Isaac's additions
LDFLAGS:= -L$(brew --prefix)/opt/llvm/lib -Wl,-rpath,$(brew --prefix)/opt/llvm/lib
CPPFLAGS:=-I/usr/local/opt/llvm/include
CURRENT_FLAGS += $(LDFLAGS) $(CPPFLAGS)
CURRENT_FLAGS += -g -pthread -DNDEBUG -Wall -Wconversion -Wfatal-errors -Wextra
# -O3 // makes the error "Illegal instruction: 4" instead of "Segmentation fault: 11"
BIN:=./bin

LIBS:= # empty
G_LIBS:= -lGL -lGLU -lglut -lGLEW -lSDL -lSDL2main -lSDL2

all:
	@echo "***********************************************"
	@echo Run one of the following commandline examples:
	@echo ""
	@echo make ex_so1
	@echo make ex_so_rastrigin
	@echo make ex_so_bind
	@echo make ex_init_solutions
	@echo make ex_mo1
	@echo make ex_mo_dtlz2
	@echo make ex_iga_colors
	@echo "***********************************************"

IsaacExample:
	$(CXX) $(CURRENT_FLAGS) examples/IsaacExample.cpp -o $(BIN)/IsaacExample $(LIBS)
	@echo "-----------------------------------------------"
	$(BIN)/IsaacExample

ex_so1:
	$(CXX) $(CURRENT_FLAGS) examples/so-1/example_so1.cpp -o $(BIN)/example_so1 $(LIBS)
	@echo "-----------------------------------------------"
	$(BIN)/example_so1

ex_so_rastrigin:
	$(CXX) $(CURRENT_FLAGS) examples/so-rastrigin/so-rastrigin.cpp -o $(BIN)/example_so-rastrigin $(LIBS)
	@echo "-----------------------------------------------"
	$(BIN)/example_so-rastrigin

ex_so_bind:
	$(CXX) $(CURRENT_FLAGS) examples/so-bind/example_bind.cpp -o $(BIN)/example_bind $(LIBS)
	@echo "-----------------------------------------------"
	$(BIN)/example_bind

ex_init_solutions:
	$(CXX) $(CURRENT_FLAGS) examples/so-init-solutions/example_so-init-solutions.cpp -o $(BIN)/example_so-init-solutions $(LIBS)
	@echo "-----------------------------------------------"
	$(BIN)/example_so-init-solutions

ex_mo1:
	$(CXX) $(CURRENT_FLAGS) examples/mo-1/example_mo1.cpp -o $(BIN)/example_mo1 $(LIBS)
	@echo "-----------------------------------------------"
	$(BIN)/example_mo1

ex_mo_dtlz2:
	$(CXX) $(CURRENT_FLAGS) examples/mo-dtlz2/mo-dtlz2.cpp -o $(BIN)/example_mo-dtlz2 $(LIBS)
	@echo "-----------------------------------------------"
	$(BIN)/example_mo-dtlz2

ex_iga_colors:
	$(CXX) $(CURRENT_FLAGS) examples/iga-colors/iga-colors.cpp -o $(BIN)/iga-colors $(LIBS) $(G_LIBS)
	@echo "-----------------------------------------------"
	$(BIN)/iga-colors

clean:
	rm ./bin/example_*
