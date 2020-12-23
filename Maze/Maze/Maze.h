#pragma once
#include "MCell.h"

class Maze
{
public:
	int getN() const { return m_n; }
	int getM() const { return m_m; }
	Maze(int n, int m) : m_n(n), m_m(m) { m_field = new MCell[n * m]; }
	~Maze();
	const MCell& cell(int i, int j) const { return m_field[i * m_n + j]; }
	bool hasConnection(int i1, int j1, int i2, int j2) const;
	bool makeConnection(int i1, int j1, int i2, int j2) const;
	bool removeConnection(int i1, int j1, int i2, int j2) const;
	void printMaze() const;
private:
	MCell* m_field = nullptr;
	const int const m_n = 0;
	const int const m_m = 0;
};
