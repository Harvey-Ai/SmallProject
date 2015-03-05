#include <iostream>
#include "sudoku.h"
using namespace std;

int main()
{
	int rowSize = 9;
	sudoku *sudokuInstance = new sudoku(rowSize);
	sudokuInstance->genBoard();

	cout << "Initial board is: " << "check = " << sudokuInstance->sudokuCheck() << endl;
	for(int i = 0;i < rowSize;i++)
	{
		cout << "|";
		for(int j = 0;j < rowSize;j++)
		{
			int val;
			if (sudokuInstance->getVal(i, j, val))
				cout << " " << val << " |";
			else
				cout  << "  " << " |";
		}
		cout << endl;
		for(int j = 0;j < rowSize;j++)
			cout << "----";
		cout << endl;
	}

	sudokuInstance->autoSolve();
	cout << endl << "Solution is: " << "check = " << sudokuInstance->sudokuCheck() << endl;
	for(int i = 0;i < rowSize;i++)
	{
		cout << "|";
		for(int j = 0;j < rowSize;j++)
		{
			int val;
			if (sudokuInstance->getVal(i, j, val))
				cout << " " << val << " |";
			else
				cout  << "  " << " |";
		}
		cout << endl;
		for(int j = 0;j < rowSize;j++)
			cout << "----";
		cout << endl;
	}
	
	return 0;
}

