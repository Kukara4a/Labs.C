#pragma once
#include "MCell.h"
class Maze
{
private:
	MCell* m_field;
	int m_n;
	int m_m;
public:
	int getN() const;
	int getM() const;
	Maze(int n, int m);
	~Maze();
	const MCell& cell(int i, int j) const;
	bool hasConnection(int i1, int j1, int i2, int j2);
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze();
};
