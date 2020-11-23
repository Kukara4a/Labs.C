#include "Maze.h"
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

bool MCell::right()
{
	return m_right;
}

bool MCell::down()
{
	return m_down;
}

MCell::MCell(){}

Maze::Maze(int n, int m)
{
	m_m = m;
	m_n = n;
	m_field = new MCell[n * m];
}

Maze::~Maze()
{
	for (int i = 0; i < m_m*m_n; i++)
		delete &m_field[i];
	delete[] m_field;
}

const MCell& Maze::cell(int i, int j) const
{
	return m_field[i * m_n + j];
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2)
{
	if (i1 == i2)	
		return m_field[i1 * m_n + min(j1, j2)].right();
	else
		return m_field[min(i1, i2) * m_n + j1].down();
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2)
{
	if (i1 == i2)
		m_field[i1 * m_n + min(j1, j2)].m_right = true;	
	else
		m_field[min(i1, i2) * m_n + j1].m_down = true;	
	return true;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2)
{
	if (i1 == i2)
		m_field[i1 * m_n + min(j1, j2)].m_right = false;
	else
		m_field[min(i1, i2) * m_n + j1].m_down = false;
	return true;
}

void Maze::printMaze()
{
	map<int, char> mp = { {1000, '0'}, {100, '0'}, {10, '0'}, {1, '0'},
						  {1100, char(218)}, {1010, char(196)}, {0, '0'}, {11, char(217)},
						  {101, char(179)}, {111, char(180)}, {1001, char(192)}, {1011, char(193)},
						  {110, char(191)}, {1101, char(195)}, {1110, char(194)}, {1111, char(197)} };

	for (int i = 0; i < m_m; i++)
	{
		for (int j = 0; j < m_n; j++)
		{
			int cellСode = 0;
			if (m_field[i * m_n + j].right())
				cellСode = cellСode + 1000;
			if (m_field[i * m_n + j].down())
				cellСode = cellСode + 100;
			if (j - 1 >= 0 && m_field[i * m_n + j - 1].right())
				cellСode = cellСode + 10;
			if (i - 1 >= 0 && m_field[(i - 1) * m_n + j].down())
				cellСode = cellСode + 1;
			cout << mp[cellСode];
		}
		cout << endl;
	}
}
