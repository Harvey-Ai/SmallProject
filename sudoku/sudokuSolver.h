#ifndef _SUDOKU_h_
#define _SUDOKU_H_

#include <vector>
#include <map>
using namespace std;

class sudokuSolver
{
	private:
		vector<vector<int> > m_board;
		map<pair<int, int>, vector<bool> > m_cand;

		void getCand();
		bool check();
		bool solveHelper(map<pair<int, int>, vector<bool> >::iterator it);

	public:
		sudokuSolver(vector<vector<int> > &board);
		~sudokuSolver();
		int solve();
		int output(vector<vector<int> > &output);
};

#endif
