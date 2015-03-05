#include "sudoku.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "sudokuSolver.h"

sudoku::sudoku(int s)
{
	m_size = s;
	if (s <= 0 || (int(sqrt(s)) * int(sqrt(s)) != m_size))
		m_size = 9;

	m_board.resize(m_size);
	for(int i = 0;i < m_size;i++)
		m_board[i].resize(m_size);
	for(int i = 0;i < m_size;i++)
		for(int j = 0;j < m_size;j++)
			m_board[i][j] = 0;

	m_fixed.resize(m_size);
	for(int i = 0;i < m_size;i++)
		m_fixed[i].resize(m_size);
	for(int i = 0;i < m_size;i++)
		for(int j = 0;j < m_size;j++)
			m_fixed[i][j] = false;
}

sudoku::~sudoku()
{
}


int sudoku::getSize()
{
	return m_size;
}

void sudoku::genBoard(double dfFactor)
{
	m_dfFactor = dfFactor;
	int blockSize = sqrt(m_size);
	for(int i = 0;i < m_size;i += blockSize)
	{
		int startVal = i / blockSize ;
		for(int k = i;k < i + blockSize;k++)
		{
			for(int j = 0;j < m_size;j++)
			{
				m_board[k][j] = (startVal + j) % m_size + 1;
				m_fixed[k][j] = true;
			}
			startVal += blockSize;
		}
	}

	srand(time(NULL));
	
	int swapNum = 2 * m_size * (m_size - 1);
	while(swapNum > 0)
	{
		int index1 = rand() % m_size;
		int index2 = rand() % m_size;
		if (index1 / blockSize == index2 / blockSize)
		{
			swap(m_board[index1], m_board[index2]);
			swapNum--;
		}

		index1 = rand() % m_size;
		index2 = rand() % m_size;
		if (index1 / blockSize == index2 / blockSize)
		{
			for(int i = 0;i < m_size;i++)
				swap(m_board[i][index1], m_board[i][index2]);
			swapNum--;
		}
	}

	// pick rmNum number out
	int rmNum = m_size * m_size * m_dfFactor;
	for(int i = 0;i < rmNum;i++)
	{
		int row = rand() % m_size, col = rand() % m_size;
		if(m_board[row][col] != 0)
		{
			m_board[row][col] = 0;
			m_fixed[row][col] = false;
		}
		else
			i--;
	}
}



bool sudoku::sudokuCheck()
{
	for(int i = 0;i < m_size;i++)
		for(int j = 0;j < m_size;j++)
			if (m_board[i][j] == 0)
				return false;
	// check block
	int blockSize = sqrt(m_size);
	for(int i = 0;i < m_size;i += blockSize)
		for(int j = 0;j < m_size; j += blockSize)
		{
			vector<bool> used(m_size + 1, false);
			for(int i1 = i;i1 < i + blockSize;i1++)
				for(int j1 = j;j1 < j + blockSize;j1++)
				{
					if (used[m_board[i1][j1]])
						return false;
					else
						used[m_board[i1][j1]] = true;
				}
		}
	
	// check row
	for(int i = 0;i < m_size;i++)
	{
		vector<bool> used(m_size + 1, false);
		for(int j = 0;j < m_size;j++)
			if (used[m_board[i][j]])
				return false;
			else
				used[m_board[i][j]] = true;
	}

	// check column
	for(int j = 0;j < m_size;j++)
	{
		vector<bool> used(m_size + 1, false);
		for(int i = 0;i < m_size;i++)
			if (used[m_board[i][j]])
				return false;
			else
				used[m_board[i][j]] = true;
	}

	return true;
}

int sudoku::autoSolve()
{
	sudokuSolver *solver = new sudokuSolver(m_board);
	solver->solve();
	solver->output(m_board);
}

bool sudoku::setVal(int row, int col, int val)
{
	if (row < 0 || row >= m_size || col < 0 || col >= m_size || m_fixed[row][col])
		return false;
	else
	{
		m_board[row][col] = val;
		return true;
	}
}


bool sudoku::getVal(int row, int col, int &val)
{
	if (row < 0 || row >= m_size || col < 0 || col >= m_size || m_board[row][col] == 0)
		return false;
	else
	{
		val = m_board[row][col];
		return true;
	}

}
