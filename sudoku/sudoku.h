#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <vector>
using namespace std;


class sudoku
{
	private:
		int m_size;						// board size
		double m_dfFactor;				// diffcult factor, bigger factor means more diffcult
		vector< vector<int> > m_board;
		vector< vector<bool> > m_fixed;

	public:
		sudoku(int s = 9);
		~sudoku();

		void genBoard(double dfFactor = 0.2);
		int getSize();
		bool sudokuCheck();
		bool setVal(int row, int col, int val);
		bool getVal(int row, int col, int &val);
		int autoSolve();
};

#endif
