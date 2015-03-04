#include "sudoku.h"

sudoku::sudoku(int s, int fn)
{
	m_size = s, m_fixedNum = fn;
	m_board.resize(m_size());
	for(int i = 0;i < m_size;i++)
		m_board[i].resize(m_size);
}

sudoku::~sudoku()
{
}

void sudoku::genBoard()
{
	for(int i = 0;i < 9;i++)
		for(int j = 0;j < 9;j++)
		{
		
		}
}
