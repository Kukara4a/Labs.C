#pragma once
#include "MCell.h"
#include <algorithm>

class Maze
{
public:
	int getN() const { return m_n; }
	int getM() const { return m_m; }
	Maze(int n, int m) : m_n(n), m_m(m) { m_field = new MCell[n * m]; }
	~Maze() { free(m_field); }
	bool cellInMaze(int i, int j) const { return i >= 0 && i < m_m && j >= 0 && j < m_n; }
	bool cellsIsNeighbors(int i1, int j1, int i2, int j2) const								// соседи имеется ввиду только слева, справа, 
	{ return (abs(i1 - i2) == 1 && (j1 == j2)) || (abs(j1 - j2) == 1 && (i1 == i2)); }		// сверху или снизу (не диагональные)
	const MCell& cell(int i, int j) const { return m_field[i * m_n + j]; }
	bool hasConnection(int i1, int j1, int i2, int j2) const;
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze() const;
private:
	MCell* m_field = nullptr;
	const int m_n = 0;
	const int m_m = 0;
};
