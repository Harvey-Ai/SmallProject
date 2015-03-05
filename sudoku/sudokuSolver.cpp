#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
#include "sudokuSolver.h"
using namespace std;

sudokuSolver::sudokuSolver(vector<vector<int> > &board)
{
	m_board.clear();
	if (board.size() == 0)
		return;
	if (board.size() != board[0].size())
		return;
	for(int i = 1;i < board.size();i++)
		if (board[i].size() != board[0].size())
			return;

	m_board = board;
}

sudokuSolver::~sudokuSolver()
{
}

void sudokuSolver::getCand()
{
	m_cand.clear();
	vector<bool> candVal(m_board.size() + 1, 1);
	for(int i = 0;i < m_board.size();i++)
		for(int j = 0;j < m_board[i].size();j++)
		{
			if (m_board[i][j] == 0)
				m_cand[make_pair(i, j)] = candVal;
		}

	// row
	for(int i = 0;i < m_board.size();i++)
	{
		for(int k = 0;k < candVal.size();k++)
			candVal[k] = 1;
		set<pair<int, int> >candPos;
		for(int j = 0;j < m_board[i].size();j++)
		{
			if (m_board[i][j])
				candVal[m_board[i][j]] = 0;
			else
				candPos.insert(make_pair(i, j));
		}
		for(set<pair<int, int> >::iterator it = candPos.begin();it != candPos.end();it++)
			for(int k = 0;k < candVal.size();k++)
				m_cand[*it][k] = m_cand[*it][k] && candVal[k];
	}

	// col
	for(int j = 0;j < m_board[0].size();j++)
	{
		for(int k = 0;k < candVal.size();k++)
			candVal[k] = 1;
		set<pair<int, int> >candPos;
		for(int i = 0;i < m_board.size();i++)
		{
			if (m_board[i][j])
				candVal[m_board[i][j]] = 0;
			else
				candPos.insert(make_pair(i, j));
		}
		for(set<pair<int, int> >::iterator it = candPos.begin();it != candPos.end();it++)
			for(int k = 0;k < candVal.size();k++)
				m_cand[*it][k] = m_cand[*it][k] && candVal[k];
	}

	// block
	int blockSize = sqrt(m_board.size());
	for(int i = 0;i < m_board.size();i += blockSize)
		for(int j = 0;j < m_board.size();j += blockSize)
		{
			for(int k = 0;k < candVal.size();k++)
				candVal[k] = 1;
			set<pair<int, int> >candPos;
			for(int row = i;row < i + blockSize;row++)
				for(int col = j;col < j + blockSize;col++)
				{
					if (m_board[row][col])
						candVal[m_board[row][col]] = 0;
					else
						candPos.insert(make_pair(row, col));
				}
					
			for(set<pair<int, int> >::iterator it = candPos.begin();it != candPos.end();it++)
				for(int k = 0;k < candVal.size();k++)
					m_cand[*it][k] = m_cand[*it][k] && candVal[k];
		}
}

bool sudokuSolver::check()
{
	for(int i = 0;i < m_board.size();i++)
		for(int j = 0;j < m_board.size();j++)
			if (m_board[i][j] == 0)
				return false;
	// check block
	int blockSize = sqrt(m_board.size());
	for(int i = 0;i < m_board.size();i += blockSize)
		for(int j = 0;j < m_board.size(); j += blockSize)
		{
			vector<bool> used(m_board.size() + 1, false);
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
	for(int i = 0;i < m_board.size();i++)
	{
		vector<bool> used(m_board.size() + 1, false);
		for(int j = 0;j < m_board.size();j++)
			if (used[m_board[i][j]])
				return false;
			else
				used[m_board[i][j]] = true;
	}

	// check column
	for(int j = 0;j < m_board.size();j++)
	{
		vector<bool> used(m_board.size() + 1, false);
		for(int i = 0;i < m_board.size();i++)
			if (used[m_board[i][j]])
				return false;
			else
				used[m_board[i][j]] = true;
	}

	return true;
}

bool sudokuSolver::solveHelper(map<pair<int, int>, vector<bool> >::iterator it)
{
	if (it == m_cand.end())
	{
		if (check())
			return true;
		else
			return false;
	}

	map<pair<int, int>, vector<bool> >::iterator nextIt = it;
	nextIt++;
	for(int i = 0;i < (it->second).size();i++)
		if ((it->second)[i])
		{
			m_board[it->first.first][it->first.second] = i;
			if (solveHelper(nextIt))
				return true;
		}
	return false;
}

int sudokuSolver::solve()
{
	getCand();
	if (solveHelper(m_cand.begin()))
		return 0;
	else
		return -1;
}

int sudokuSolver::output(vector<vector<int> > &output)
{
	output = m_board;
	return 0;
}

