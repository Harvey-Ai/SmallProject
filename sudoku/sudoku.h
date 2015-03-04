#include <vector>
using namespace std;


class sudoku
{
	private:
		int m_size;
		int m_fixedNum;
		vector< vector<int> > m_board;

	public:
		sudoku(int s = 9, int fn = 25);
		~sudoku();

		void genBoard();
		void sodokuCheck(vector<vector<int> > &board);
		void setVal(int row, int col, int val);
};
