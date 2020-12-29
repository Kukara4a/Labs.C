#include "Maze.h"
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

bool Maze::hasConnection(int i1, int j1, int i2, int j2) const
{
	if (!cellInMaze(i1, j1) || !cellInMaze(i2, j2) || !cellsIsNeighbors(i1, j1, i2, j2))
		return false;
	if (i1 == i2)
		return m_field[i1 * m_n + min(j1, j2)].right();
	else 
		return m_field[min(i1, i2) * m_n + j1].down();
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2)
{
	if (!cellInMaze(i1, j1) || !cellInMaze(i2, j2) || !cellsIsNeighbors(i1, j1, i2, j2) || hasConnection(i1, j1, i2, j2))
		return false;
	if (i1 == i2)
		m_field[i1 * m_n + min(j1, j2)].m_right = true;
	else
		m_field[min(i1, i2) * m_n + j1].m_down = true;
	return true;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2)
{
	if (!hasConnection(i1, j1, i2, j2))
		return false;
	if (i1 == i2)
		m_field[i1 * m_n + min(j1, j2)].m_right = false;
	else
		m_field[min(i1, i2) * m_n + j1].m_down = false;
	return true;
}

void Maze::printMaze() const
{
	static map<int, char> mp = { {1000, '0'}, {100, '0'}, {10, '0'}, {1, '0'},
						  {1100, char(218)}, {1010, char(196)}, {0, '0'}, {11, char(217)},
						  {101, char(179)}, {111, char(180)}, {1001, char(192)}, {1011, char(193)},
						  {110, char(191)}, {1101, char(195)}, {1110, char(194)}, {1111, char(197)} };

	for (int i = 0; i < m_m; i++)
	{
		for (int j = 0; j < m_n; j++)
		{
			int cellCode = 0;
			if (m_field[i * m_n + j].right())
				cellCode = cellCode + 1000;							// 4 единицы - 4 стороны, 1000 - имеет связь справа, 
			if (m_field[i * m_n + j].down())						// 0100 - связь снизу, 0010 - связь слева, 0001 - связь сверху
				cellCode = cellCode + 100;							
			if (j - 1 >= 0 && m_field[i * m_n + j - 1].right())
				cellCode = cellCode + 10;
			if (i - 1 >= 0 && m_field[(i - 1) * m_n + j].down())
				cellCode = cellCode + 1;
			cout << mp[cellCode];
		}
		cout << endl;
	}
}
