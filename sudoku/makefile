
sudokuTest: sudoku.o sudokuTest.o sudokuSolver.o
	g++ -o $@ $^

sudokuTest.o: sudokuTest.cpp
	g++ -g -c sudokuTest.cpp -o sudokuTest.o

sudokuSolver.o: sudokuSolver.h sudokuSolver.cpp
	g++ -g -c sudokuSolver.cpp -o sudokuSolver.o

sudoku.o: sudoku.cpp sudoku.h
	g++ -g -c sudoku.cpp -o sudoku.o

.PNHONY:clean
clean:
	-rm *.o
	-rm sudokuTest
